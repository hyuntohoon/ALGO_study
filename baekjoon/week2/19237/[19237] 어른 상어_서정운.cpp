
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

/*

맨 처음에, 상어의 위치에 냄새를 남긴다.

상어가 한 마리만 남을 때까지,
냄새가 없는 칸으로 이동한다. 없다면, 자신의 냄새 칸으로 이동한다. 이동 방향은 각자의 우선 순위를 따른다.
이동 후, 같은 칸에 여러 상어가 있다면, 그 중 번호가 가장 작은 상어만 남긴다.
이전의 냄새의 기간을 갱신한다.
현재 칸에 냄새를 남긴다.

*/

int N, M, K;

int scent[22][22];
int scenttime[22][22];

struct Shark {
	int id, x, y, dir;
	int pri[5][4];
};

vector<Shark> sharks;

// 상하좌우
int snx(int x, int i) {
	return "0211"[i - 1] - '1' + x;
}

int sny(int y, int i) {
	return "1102"[i - 1] - '1' + y;
}

ii nextpos(int x, int y, int i) {
	return { snx(x, i), sny(y, i) };
}

int main() {
	FAST;

	cin >> N >> M >> K;

	// 지도
	For(i, 0, N) For(j, 0, N) {
		int n; cin >> n;
		if (n != 0) {
			sharks.push_back({ n, i, j });
		}
	}

	sort(all(sharks), [](Shark& l, Shark& r) {return l.id < r.id; });

	// 상어의 방향
	for(auto& s : sharks) {
		cin >> s.dir;
	}

	// 상어의 방향 우선순위
	for (auto& s : sharks) {
		For(i, 1, 5) {
			For(j, 0, 4) cin >> s.pri[i][j];
		}
	}

	// 맨 처음에, 상어의 위치에 냄새를 남긴다.
	for (auto& shark : sharks) {
		scent[shark.x][shark.y] = shark.id;
		scenttime[shark.x][shark.y] = K;
	}

	// 상어가 한 마리만 남을 때까지,
	int cnt = 0;
	while (sharks.size() > 1 && cnt <= 1000) {
		cnt++;

		// 냄새가 없는 칸으로 이동한다. 없다면, 자신의 냄새 칸으로 이동한다. 이동 방향은 각자의 우선 순위를 따른다.
		for (auto& s : sharks) {
			int ndir = -1;
			// 냄새가 없는 방향을 찾는다.
			for (int next : s.pri[s.dir]) {
				auto [nx, ny] = nextpos(s.x, s.y, next);
				if (outside(nx, ny, N, N)) continue;
				if (scent[nx][ny] == 0) {
					ndir = next; break;
				}
			}
			// 냄새가 없는 방향이 없다면,
			if (ndir == -1) {
				// 자신의 냄새가 있는 칸을 찾는다.
				for (int next : s.pri[s.dir]) {
					auto [nx, ny] = nextpos(s.x, s.y, next);
					if (outside(nx, ny, N, N)) continue;
					if (scent[nx][ny] == s.id) {
						ndir = next; break;
					}
				}
			}
			// 상어가 이동하지 못하는 경우는 없다.
			// 상어의 위치를 갱신한다.
			tie(s.x, s.y) = nextpos(s.x, s.y, ndir);
			// 상어가 보는 방향을 갱신한다.
			s.dir = ndir;
		}


		// 이동 후, 같은 칸에 여러 상어가 있다면, 그 중 번호가 가장 작은 상어만 남긴다.
		int vst[22][22] = { 0, };
		vector<Shark> next;
		for (auto& s : sharks) {
			if (vst[s.x][s.y]) continue;
			vst[s.x][s.y] = 1;
			next.push_back(s);
		}
		sharks = next;

		// 이전의 냄새의 기간을 갱신한다.
		For(i, 0, 20) For(j, 0, 20) {
			if (scent[i][j]) {
				if (--scenttime[i][j] == 0) scent[i][j] = 0;
			}
		}

		// 현재 칸에 냄새를 남긴다.
		for (auto& s : sharks) {
			scent[s.x][s.y] = s.id;
			scenttime[s.x][s.y] = K;
		}

	}

	if (cnt > 1000) cnt = -1;
	cout << cnt;

}