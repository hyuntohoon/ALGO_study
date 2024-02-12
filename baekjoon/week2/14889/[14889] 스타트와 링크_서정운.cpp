
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

int m[22][22];

int main() {
	FAST;

	int N; cin >> N;

	For(i, 0, N) {
		For(j, 0, N) {
			cin >> m[i][j];
		}
	}

	int res = 1e9;
	vector<int> v(N / 2); v.resize(N, 1);
	do {
		int l, r; l = r = 0;
		For(i, 0, N) For(j, i + 1, N) {
			if (v[i] != v[j]) continue;
			(v[i] ? l : r) += m[i][j] + m[j][i];
		}
		res = min(res, abs(l - r));
	} while (next_permutation(all(v)));

	cout << res;

}