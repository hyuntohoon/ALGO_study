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
#define nx(x,i) x + "1102"[i] - '1'
#define ny(y,i) y + "0211"[i] - '1'

int A[111];
int N;

int mx = -1e9, mn = 1e9;

int calc[4]; // + - * /

void dfs(int dep, int now) {
	if (dep == N) {
		mx = max(mx, now); mn = min(mn, now);
		return;
	}
	For(i, 0, 4) {
		if (calc[i] == 0) continue;
		calc[i]--;

		if (i == 0) dfs(dep + 1, now + A[dep]);
		if (i == 1) dfs(dep + 1, now - A[dep]);
		if (i == 2) dfs(dep + 1, now * A[dep]);
		if (i == 3) dfs(dep + 1, now / A[dep]);

		calc[i]++;
	}
}

int main() {
	FAST;

	cin >> N;
	For(i, 0, N) cin >> A[i];
	For(i, 0, 4) cin >> calc[i];

	dfs(1, A[0]);

	cout << mx << ' ' << mn;

}