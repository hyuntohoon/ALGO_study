
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;

#define For(i,a,b) for(int i=a;i<b;i++)
#define outside(x,y,R,C) (min(x,y) < 0 || x >=R || y >= C)
#define FAST (cin.tie(0)->sync_with_stdio(0))
#define nx(x,i) ("0121"[i] - '1' + x)
#define ny(y,i) ("1210"[i] - '1' + y)
#define endl '\n'
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()



// #define DEBUG

struct Fish {
	int dir; ii pos;
};

Fish fishes[17];
int eated[17];
int fishnumber[4][4];

int sharkx, sharky, sdir;

int fishnx(int x, int dir) {
	return "00122210"[dir] - '1' + x;
}

int fishny(int y, int dir) {
	return "10001222"[dir] - '1' + y;
}

int nextdir(int x, int y, int dir) {
	For(i, 0, 8) {
		int nextdir = (dir + i) % 8;
		int nx = fishnx(x, nextdir), ny = fishny(y, nextdir);
		if (outside(nx, ny, 4, 4)) continue;
		if (sharkx == nx && sharky == ny) continue;
		return nextdir;
	}
	return -1;
}

void fishmove() {
	For(i, 1, 17) {
		Fish& now = fishes[i];
		if (eated[i]) continue;
		int ndir = nextdir(now.pos.first, now.pos.second, now.dir);
		if (ndir == -1) continue;
		now.dir = ndir;

		// 물고기 이동
		int nx = fishnx(now.pos.first, ndir), ny = fishny(now.pos.second, ndir);
		int next = fishnumber[nx][ny];
		swap(fishnumber[now.pos.first][now.pos.second], fishnumber[nx][ny]);
		if (next == 0) {
			now.pos.first = nx; now.pos.second = ny;
		}
		else {
			swap(now.pos, fishes[next].pos);
		}

#ifdef DEBUG

		cout << "==MOVING " << i << "==" << endl;
		For(i, 0, 4) {
			For(j, 0, 4) {
				if (i == sharkx && j == sharky) {
					cout << 'S';
				}
				else cout << fishnumber[i][j];
				cout << ' ';
			}
			cout << '\t';
			For(j, 0, 4) {
				if (i == sharkx && j == sharky) {
					cout << sdir;
				}
				else cout << fishes[fishnumber[i][j]].dir;
				cout << ' ';
			}
			cout << endl;
		}
		cout << endl;

#endif
	}
}

int res = 0;

void dfs(int sum) {

#ifdef DEBUG

	cout << "==DEBUG==" << endl;
	cout << sum << endl;
	For(i, 0, 4) {
		For(j, 0, 4) {
			if (i == sharkx && j == sharky) {
				cout << 'S';
			}
			else cout << fishnumber[i][j];
			cout << ' ';
		}
		cout << endl;
	}
	cout << endl;

#endif

	// 이전 상태 저장
	Fish beforefishes[17];
	copy(fishes, fishes + 17, beforefishes);

	int beforefishnumber[4][4];
	copy(&fishnumber[0][0], &fishnumber[0][0] + 16, &beforefishnumber[0][0]);

	int beforesharkx = sharkx, beforesharky = sharky, beforesdir = sdir;

	// 물고기 이동
	fishmove();
#ifdef DEBUG

	cout << "==MOVED==" << endl;
	For(i, 0, 4) {
		For(j, 0, 4) {
			if (i == sharkx && j == sharky) {
				cout << 'S';
			}
			else cout << fishnumber[i][j];
			cout << ' ';
		}
		cout << endl;
	}
	cout << endl;

#endif

	bool flag = false;
	For(i, 0, 4) {
		int nx = fishnx(sharkx, sdir), ny = fishny(sharky, sdir);
		if (outside(nx, ny, 4, 4)) break;
		sharkx = nx; sharky = ny;
		if (fishnumber[nx][ny] != 0) {
			flag = true;
			// 먹은 물고기 번호, 원래 상어 방향 기억
			int eat = fishnumber[nx][ny];
			int bsdir = sdir;
			// 물고기 먹고 방향 전환
			fishnumber[nx][ny] = 0;
			sdir = fishes[eat].dir;
			eated[eat] = 1;
			// dfs
			dfs(sum + eat);
			// 다시 원래 상태로
			fishnumber[nx][ny] = eat;
			sdir = bsdir;
			eated[eat] = 0;
		}
	}
	// 물고기를 먹은 적이 없다면, 답을 갱신한다.
	if (!flag) {
		res = max(res, sum);
	}

	// 이전 상태로 되돌린다.
	copy(beforefishes, beforefishes + 17, fishes);
	copy(&beforefishnumber[0][0], &beforefishnumber[0][0] + 16, &fishnumber[0][0]);
	sharkx = beforesharkx; sharky = beforesharky; sdir = beforesdir;

#ifdef DEBUG

	cout << "==back==" << endl;

#endif

}

int main() {
	FAST;

	For(i, 0, 4) For(j, 0, 4) {
		int id, dir; cin >> id >> dir;
		fishnumber[i][j] = id; fishes[id] = { dir - 1, {i,j} };
	}

	int eat = fishnumber[0][0];
	eated[eat] = 1;

	sharkx = sharky = 0;
	sdir = fishes[fishnumber[0][0]].dir;
	fishnumber[0][0] = 0;

	dfs(eat);

	cout << res;

}