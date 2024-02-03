#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

#define FAST cin.tie(0)->sync_with_stdio(0);
#define endl '\n'
#define INPUT freopen("input.txt", "rt", stdin)

using ll = long long;
using ii = pair<int, int>;
using pll = pair<ll, ll>;

#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
#define For(i,a,b) for(int i=a;i<b;i++)
#define outside(x,y,R,C) (min(x,y) < 1 || R < x || C < y)
#define zoutside(x,y,R,C) (min(x,y) < 0 || R <= x || C <= y)
//#define nx(x,i) x + "1102"[i] - '1'
//#define ny(y,i) y + "0211"[i] - '1'

// 각각 물고기 상태, 복제한 물고기, 다음 물고기 상태를 저장함.
// 각 배열은 x, y, dir 상태이며, 각 상태의 물고기 개수를 저장한다.
int fishes[4][4][8], fishcopy[4][4][8], fishnext[4][4][8];
// 상어의 위치.
int sx, sy;
// 현재 피냄새 값
int scent[4][4];

// 0~4 내인지 확인하는 함수
// inline을 붙여주면, 컴파일러의 판단에 따라 해당 함수의 구현을, 함수의 호출부에 직접 insert한다.
inline int out(int x, int y) {
	return min(x, y) < 0 || max(x, y) >= 4;
}

// 물고기의 다음 위치
// 좌, 좌상, 상, 우상, 우, 우하, 하, 좌하
inline int fishnx(int x, int i) {
	return "10001222"[i] - '1' + x;
}

inline int fishny(int y, int i) {
	return "00122210"[i] - '1' + y;
}

// 물고기의 다음 방향을 찾는 함수
// 이동 불가 시 -1 반환
int nextdir(int x, int y, int dir) {
	// 반시계 회전
	for (int i = 8; i > 0; i--) {
		int ndir = (dir + i) % 8;
		int xx = fishnx(x, ndir), yy = fishny(y, ndir);
		if (out(xx, yy) || (xx == sx && yy == sy)) continue;
		if (scent[xx][yy]) continue;
		return ndir;
	}
	return -1;
}

// 상어의 다음 위치
// 상좌하우
inline int sharknx(int x, int i) {
	return "0121"[i] - '1' + x;
}

inline int sharkny(int y, int i) {
	return "1012"[i] - '1' + y;
}

/////////// 상어의 이동 구현에서 가장 시간을 많이 끔
/////////// 같은 칸을 지나지 않게 해서 예제 5, 6을 통과 못 했었음
/////////// 같은 칸도 지날 수 있게 한 뒤 바로 통과

// 상어의 이동 구현
// mx는 이동 시 먹을 수 있는 최대 물고기 값, now는 현재까지 먹은 물고기 값
int mx = -1, now = 0;
// 방문 여부. 같은 공간 방문 시 물고기 개수 갱신에 참고하기 위해 사용
int vst[4][4];
// buf는 현재 이동 방향을 잠시 저장하고, mv에 물고기를 최대로 먹을 수 있는 이동방향이 저장됨
void dfs(int dep, int x, int y, vector<int>& buf, vector<int>& mv) {
	if (dep == 3) {
        // 현재 최댓값보다 많이 먹을 수 있으면 바로 저장
		if (now > mx) {
			mv = buf; mx = now;
		}
        // 현재 최댓값과 같다면, 사전순으로 더 빠른 걸 저장
		else if (now == mx) {
			mv = min(mv, buf);
		}
		return;
	}
	For(i, 0, 4) {
		int nx = sharknx(x, i), ny = sharkny(y, i);
		if (out(nx, ny)) continue;
		if(!vst[nx][ny]) For(k, 0, 8) now += fishnext[nx][ny][k]; // 이미 방문했다면, 개수 갱신 x
		vst[nx][ny]++;
		buf.push_back(i);
		dfs(dep + 1, nx, ny, buf, mv);
		buf.pop_back();
		vst[nx][ny]--;
		if (!vst[nx][ny]) For(k, 0, 8) now -= fishnext[nx][ny][k]; // 아직 방문한 칸이라면, 개수 갱신 x
	}
}

// 디버깅 출력용
// 어디서도 쓰이지 않으면 컴파일 시 포함하지 않는다고 알고 있음 아마도
void DEBUG() {
	For(i, 0, 4) {
		For(j, 0, 4) {
			int sum = 0;
			For(k, 0, 8) sum += fishes[i][j][k];
			cout << sum << ' ';
		}
		cout << '\t';
		For(j, 0, 4) {
			cout << scent[i][j] << ' ';
		}
		cout << endl;
	}
	cout << sx << ' ' << sy;
	cout << endl;
}

int main() {
	FAST;

	int N, S; cin >> N >> S;

	For(i, 0, N) {
		int x, y, d; cin >> x >> y >> d;
		fishes[x - 1][y - 1][d - 1]++;
	}

	cin >> sx >> sy;
	sx--; sy--;

	For(i, 0, S) {

		// step 1, 2
		For(i, 0, 4) For(j, 0, 4) {
			for (int dir = 0; dir < 8; dir++) {
				// step 1
                // 복사된 물고기 저장
				fishcopy[i][j][dir] = fishes[i][j][dir];

				// step 2
                // 물고기 없으면 건너뜀
				if (fishes[i][j][dir] == 0) continue;
                // 다음 방향 찾음
				int ndir = nextdir(i, j, dir);
                // 없으면 그냥 저장
				if (ndir == -1) {
					fishnext[i][j][dir] += fishes[i][j][dir];
				}
                // 있으면 그 방향의 칸에 저장
				else {
					fishnext[fishnx(i, ndir)][fishny(j, ndir)][ndir] += fishes[i][j][dir];
				}
			}
		}

		// step 3
        // 상어의 이동 방향 구하기
		vector<int> buffer, movement; mx = -1; now = 0;
		dfs(0, sx, sy, buffer, movement);

        // 상어의 이동 방향을 따라가면서 물고기와 냄새 갱신
		int nsx = sx, nsy = sy;
		for (int i : movement) {
			nsx = sharknx(sx, i); nsy = sharkny(sy, i);
			For(k, 0, 8) if (fishnext[nsx][nsy][k]) {
				scent[nsx][nsy] = 3; fishnext[nsx][nsy][k] = 0;
			}
			sx = nsx; sy = nsy;
		}

		// step 4
        // 냄새 기간 갱신
		For(i, 0, 4) For(j, 0, 4) if (scent[i][j]) scent[i][j]--;

		// step 5
        // 물고기 복사
		For(i, 0, 4) For(j, 0, 4) For(k, 0, 8) {
			fishnext[i][j][k] += fishcopy[i][j][k];
		}

        // 다음 상태와 현재 상태를 스왑(현재 상태에 다음 상태를 적용)
		swap(fishes, fishnext);
        // 다음 상태를 0으로 초기화
		memset(fishnext, 0, sizeof fishnext);

	}

	int res = 0;
	For(i, 0, 4) For(j, 0, 4) For(k, 0, 8) {
		res += fishes[i][j][k];
	}

	cout << res;

}