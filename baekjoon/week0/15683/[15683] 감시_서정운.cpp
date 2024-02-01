#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;

#define For(i,a,b) for(int i=a;i<b;i++)
#define outside(x,y,R,C) (min(x,y) < 0 || x >=R || y >= C)
#define FAST cin.tie(0)->sync_with_stdio(0)
#define nx(x,i) ("0121"[i] - '1' + x)
#define ny(y,i) ("1210"[i] - '1' + y)
#define endl '\n'


int m[11][11];
int chk[11][11];
int N, M;

void line(int x, int y, int dir, int draw) {
	while (true) {
		int nx = nx(x, dir), ny = ny(y, dir);
		if (outside(nx, ny, N, M) || m[nx][ny] == 6) return;
		x = nx; y = ny;
		if (draw) chk[x][y]++;
		if (!draw) chk[x][y]--;
	}
}
void one(int x, int y, int dir, int draw) {
	line(x, y, dir, draw);
}
void two(int x, int y, int dir, int draw) {
	line(x, y, dir, draw);
	line(x, y, (dir + 2) % 4, draw);
}
void three(int x, int y, int dir, int draw) {
	line(x, y, dir, draw);
	line(x, y, (dir + 1) % 4, draw);
}
void four(int x, int y, int dir, int draw) {
	line(x, y, dir, draw);
	line(x, y, (dir + 1) % 4, draw);
	line(x, y, (dir + 2) % 4, draw);
}
void five(int x, int y, int dir, int draw) {
	line(x, y, dir, draw);
	line(x, y, (dir + 1) % 4, draw);
	line(x, y, (dir + 2) % 4, draw);
	line(x, y, (dir + 3) % 4, draw);
}

void draw(int x, int y, int dir, int draw) {
	if (m[x][y] == 1) one(x, y, dir, draw);
	if (m[x][y] == 2) two(x, y, dir, draw);
	if (m[x][y] == 3) three(x, y, dir, draw);
	if (m[x][y] == 4) four(x, y, dir, draw);
	if (m[x][y] == 5) five(x, y, dir, draw);
}

int res = 1e9;

vector<ii> v;

int scan() {
	int cnt = 0;
	For(i, 0, N) For(j, 0, M) {
		cnt += chk[i][j] == 0;
	}
	return cnt;
}

void dfs(int idx) {
	if (idx == v.size()) {
		res = min(res, scan()); return;
	}
	For(i, 0, 4) {
		draw(v[idx].first, v[idx].second, i, 1);
		dfs(idx + 1);
		draw(v[idx].first, v[idx].second, i, 0);
	}
}

int main() {
	FAST;

	cin >> N >> M;

	For(i, 0, N) For(j, 0, M) {
		cin >> m[i][j];
		if (m[i][j] != 0 && m[i][j] != 6) {
			v.emplace_back(i, j);
		}
		if (m[i][j] != 0) chk[i][j]++;
	}

	dfs(0);

	cout << res;

}