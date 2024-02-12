
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


int ladder[33][11];
int N, M, H;

int res = 1e9;

bool check() {
	For(i, 1, N + 1) {
		int now = i;
		For(j, 1, H + 1) {
			if (ladder[j][now]) now++;
			else if (ladder[j][now - 1]) now--;
		}
		if (now != i) return false;
	}
	return true;
}

void dfs(int pos, int cnt) {

	int x = pos / (N - 1) + 1, y = pos % (N - 1) + 1;

	if (check()) {
		res = min(res, cnt);
	}

	if (cnt >= min(res, 3)) return;
	if (x > H) return;

	dfs(pos + 1, cnt);
	if (!(ladder[x][y - 1] || ladder[x][y] || ladder[x][y + 1])) {
		ladder[x][y] = 1;
		dfs(pos + 1, cnt + 1);
		ladder[x][y] = 0;
	}

}

int main() {
	FAST;

	cin >> N >> M >> H;

	For(i, 0, M) {
		int a, b; cin >> a >> b;
		ladder[a][b] = 1;
	}

	dfs(0, 0);

	if (res == 1e9) res = -1;
	cout << res;

}