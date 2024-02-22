#include <bits/stdc++.h>
using namespace std;

#define For(i,a,b) for(int i=a;i<b;i++)
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
using pii = pair<int, int>;

int board[111][111];

bool out(int x, int y) {
	return min(x, y) < 0 || max(x, y) > 100;
}

int nx(int x, int i) {
	return "1012"[i] - '1' + x;
}

int ny(int y, int i) {
	return "2101"[i] - '1' + y;
}

pii curve(int nth, int sx, int sy, int dir) {
	if (nth == 0) {
		if (!out(sx, sy)) board[sx][sy] = 1;
		if (!out(nx(sx, dir), ny(sy, dir))) board[nx(sx, dir)][ny(sy, dir)] = 1;
		return { nx(sx, dir), ny(sy, dir) };
	}
	pii middle = curve(nth - 1, sx, sy, dir);
	int gx = middle.first - sx;
	int gy = middle.second - sy;
	pii next = {
		middle.first - gy, middle.second + gx
	};
	curve(nth - 1, next.first, next.second, (dir + 3) % 4);
	return next;
}

int main() {

	int N; cin >> N;

	For(i, 0, N) {
		int x, y, d, g; cin >> x >> y >> d >> g;
		curve(g, y, x, d);
	}

	int res = 0;
	For(i, 0, 100) For(j, 0, 100) {
		res += board[i][j] && board[i][j + 1] && board[i + 1][j] && board[i + 1][j + 1];
	}

	cout << res;

}