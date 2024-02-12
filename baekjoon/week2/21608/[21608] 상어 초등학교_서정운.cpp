
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

set<int> G[4444];

int m[22][22];

int main() {
	FAST;

	int N; cin >> N;

	vector<int> order;
	For(i, 0, N * N) {
		int n; cin >> n;
		order.push_back(n);
		For(j, 0, 4) {
			int m; cin >> m;
			G[n].insert(m);
		}
	}

	for (int t : order) {

		int x = -1, y = -1;
		int empty = -1, friends = 0;

		For(i, 0, N) {
			For(j, 0, N) {
				if (m[i][j]) continue;
				int blank = 0, cnt = 0;
				For(k, 0, 4) {
					int nx = nx(i, k), ny = ny(j, k);
					if (outside(nx, ny, N, N)) continue;
					blank += m[nx][ny] == 0;
					cnt += G[t].count(m[nx][ny]);
				}
				// 친구가 빈 칸보다 더 높은 우선순위를 가진다.
				if (cnt > friends) {
					friends = cnt; empty = blank;
					x = i; y = j; continue;
				}
				// 친구 수가 같으면, 빈 자리가 더 많은 곳으로 간다.
				else if (cnt == friends && blank > empty) {
					friends = cnt; empty = blank;
					x = i; y = j; continue;
				}
			}
		}

		m[x][y] = t;

	}

	int res = 0;
	For(i, 0, N) {
		For(j, 0, N) {
			int now = m[i][j];
			int cnt = 0;
			For(k, 0, 4) {
				int nx = nx(i, k), ny = ny(j, k);
				if (outside(nx, ny, N, N)) continue;
				cnt += G[now].count(m[nx][ny]);
			}
			if(cnt) res += pow(10, cnt - 1);
		}
	}

	cout << res;

}