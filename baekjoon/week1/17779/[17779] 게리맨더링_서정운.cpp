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

int m[22][22];
int vst[22][22];
int N;

int res = 1e9;

bool available(int x, int y, int l, int r) {
	return 0 <= y - l && y + r < N && x + l + r < N;
}

void bfs(int sx, int sy, int& n, int v) {
	queue<ii> q; q.push({ sx, sy });
	vst[sx][sy] = v;
	while (q.size()) {
		ii now = q.front(); q.pop();
		n += m[now.first][now.second];
		For(i, 0, 4) {
			int nx = nx(now.first, i), ny = ny(now.second, i);
			if (outside(nx, ny, N, N) || vst[nx][ny]) continue;
			vst[nx][ny] = v; q.push({ nx,ny });
		}
	}
}

void check(int sx, int sy, int l, int r) {
	memset(vst, 0, sizeof vst);
	int x = sx, y = sy;

	int a, b, c, d, e;
	a = b = c = d = e = 0;

	// 상
	For(i, 1, N) {
		if (x - i < 0) break;
		vst[x - i][y] = 1; a += m[x - i][y];
	}

	For(i, 0, l) {
		x++; y--;
		e += m[x][y]; vst[x][y] = 5;
	}

	// 좌
	For(i, 1, N) {
		if (y - i < 0) break;
		vst[x][y - i] = 3; c += m[x][y - i];
	}

	For(i, 0, r) {
		x++; y++;
		e += m[x][y]; vst[x][y] = 5;
	}
	
	// 하
	For(i, 1, N) {
		if (x + i >= N) break;
		vst[x + i][y] = 4; d += m[x + i][y];
	}

	For(i, 0, l) {
		x--; y++;
		e += m[x][y]; vst[x][y] = 5;
	}

	// 우
	For(i, 1, N) {
		if (y + i >= N) break;
		vst[x][y + i] = 2; b += m[x][y + i];
	}

	For(i, 0, r) {
		x--; y--;
		e += m[x][y]; vst[x][y] = 5;
	}

	if (!vst[0][0]) bfs(0, 0, a, 1);
	if (!vst[0][N - 1]) bfs(0, N - 1, b, 2);
	if (!vst[N - 1][0]) bfs(N - 1, 0, c, 3);
	if (!vst[N - 1][N - 1]) bfs(N - 1, N - 1, d, 4);

	For(i, 0, N) For(j, 0, N) {
		if (!vst[i][j]) {
			e += m[i][j]; vst[i][j] = 5;
		}
	}

// #define DEBUG
#ifdef DEBUG
	//if (res > max({ a,b,c,d,e }) - min({ a,b,c,d,e })) {
		cout << "===DEBUG=== "  << endl;
		cout << max({ a,b,c,d,e }) - min({ a,b,c,d,e }) << endl;
		cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << endl;
		For(i, 0, N) {
			For(j, 0, N) {
				cout << vst[i][j] << ' ';
			}
			cout << endl;
		}
		cout << endl;
		// }
#endif

	res = min(res, max({ a,b,c,d,e }) - min({ a,b,c,d,e }));
}

void solve(int sx, int sy) {
	// size
	// d1, d2는 무조건 1 이상이어야 함
	For(i, 1, N) For(j, 1, N) {
		if (available(sx, sy, i, j)) check(sx, sy, i, j);
		else break;
	}
}

int main() {
	FAST;

	cin >> N;

	For(i, 0, N) {
		For(j, 0, N) {
			cin >> m[i][j];
		}
	}

	For(i, 0, N) {
		For(j, 0, N) {
			solve(i, j);
		}
	}

	cout << res;

}