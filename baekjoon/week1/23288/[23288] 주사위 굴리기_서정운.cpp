
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

class Dice {
private:
	int arr[4][3] = {
		{0,2,0},
		{4,1,3},
		{0,5,0},
		{0,6,0},
	};
	void left() {
		swap(arr[1][0], arr[1][1]);
		swap(arr[1][1], arr[1][2]);
		swap(arr[1][2], arr[3][1]);
	}
	void right() {
		swap(arr[1][2], arr[3][1]);
		swap(arr[1][1], arr[1][2]);
		swap(arr[1][0], arr[1][1]);
	}
	void up() {
		For(i, 0, 3) {
			swap(arr[i][1], arr[i + 1][1]);
		}
	}
	void down() {
		For(i, 0, 3) {
			swap(arr[3 - i][1], arr[2 - i][1]);
		}
	}

public:
	int bottom() {
		return arr[3][1];
	}
	void roll(int dir) {
		if (dir == 0) up();
		else if (dir == 1) right();
		else if (dir == 2) down();
		else left();
	}
};

int m[22][22];
int N, M, K;

// 북동남서/상우하좌
int dnx(int x, int i) {
	return "0121"[i] - '1' + x;
}

int dny(int y, int i) {
	return "1210"[i] - '1' + y;
}

int vst[22][22];
int bfs(int sx, int sy) {
	memset(vst, 0, sizeof vst); vst[sx][sy] = 1;
	queue<ii> q; q.push({ sx,sy });

	int cnt = 0;
	while (q.size()) {
		ii now = q.front(); q.pop(); cnt++;
		For(i, 0, 4) {
			int nx = nx(now.first, i), ny = ny(now.second, i);
			if (outside(nx, ny, N, M) || vst[nx][ny]) continue;
			if (m[now.first][now.second] != m[nx][ny]) continue;
			vst[nx][ny] = 1; q.push({ nx,ny });
		}
	}
	return cnt;
}

int main() {
	FAST;

	Dice dice;

	cin >> N >> M >> K;

	For(i, 0, N) For(j, 0, M) cin >> m[i][j];

	int dir = 1;
	int x = 0, y = 0;
	int score = 0;

	while (K--) {

		// 1.
		int nx = dnx(x, dir), ny = dny(y, dir);
		if (outside(nx, ny, N, M)) {
			dir = (dir + 2) % 4;
			nx = dnx(x, dir); ny = dny(y, dir);
		}
		x = nx; y = ny;
		dice.roll(dir);

		// 2.
		int B = m[x][y];
		int C = bfs(x, y);
		score += B * C;

		// 3.
		int A = dice.bottom();
		if (A > B) dir = (dir + 1) % 4;
		if (A < B) dir = (dir + 3) % 4;
	}

	cout << score;

}