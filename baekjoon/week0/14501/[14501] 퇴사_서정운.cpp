#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;

#define For(i,a,b) for(int i=a;i<b;i++)
#define outside(x,y,R,C) (min(x,y) < 0 || x >=R || y <= C)
#define FAST cin.tie(0)->sync_with_stdio(0)
#define nx(x,i) ("1102"[i] - '1' + x)
#define ny(y,i) ("0211"[i] - '1' + y)
#define endl '\n'



int dp[22];

int main() {
	FAST;

	int N; cin >> N;

	For(i, 1, N + 1) {
		int a, b; cin >> a >> b;
		dp[i] = max(dp[i], dp[i - 1]);
		dp[i + a] = max(dp[i + a], dp[i] + b);
	}

	cout << max(dp[N + 1], dp[N]);

}