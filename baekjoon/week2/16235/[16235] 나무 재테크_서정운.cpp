
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


struct Tree {
	int x, y, z;
};

deque<Tree> trees;

int m[11][11];
int A[11][11];

int main() {
	FAST;

	int N, M, K; cin >> N >> M >> K;

	For(i, 0, N) {
		For(j, 0, N) {
			cin >> A[i][j];
			m[i][j] = 5;
		}
	}

	For(i, 0, M) {
		int a, b, c; cin >> a >> b >> c;
		trees.push_back({ a-1,b-1,c });
	}
	sort(all(trees), [](Tree& l, Tree& r) {return l.z < r.z; });

	For(i, 0, K) {
		deque<Tree> dead;
		for (int t = trees.size(); t--;) {
			Tree now = trees.front(); trees.pop_front();
			if (m[now.x][now.y] < now.z) {
				dead.push_back(now); continue;
			}
			m[now.x][now.y] -= now.z; now.z++;
			trees.push_back(now);
		}
		while (dead.size()) {
			Tree now = dead.front(); dead.pop_front();
			m[now.x][now.y] += now.z / 2;
		}
		vector<Tree> siblings;
		for (int t = trees.size(); t--;) {
			Tree now = trees.front(); trees.pop_front();
			if (now.z % 5 == 0) {
				For(i, 0, 8) {
					int nx = "00011222"[i] - '1' + now.x;
					int ny = "01202012"[i] - '1' + now.y;
					if (outside(nx, ny, N, N)) continue;
					siblings.push_back({ nx,ny,1 });
				}
			}
			trees.push_back(now);
		}
		for (auto& i : siblings) trees.push_front(i);
		For(i, 0, N) For(j, 0, N) m[i][j] += A[i][j];
	}

	cout << trees.size();

}