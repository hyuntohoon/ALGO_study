#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;

#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
constexpr inline auto nx = [](int x, int i) {return "0121"[i] - '1' + x; };
constexpr inline auto ny = [](int y, int i) {return "1210"[i] - '1' + y; };
constexpr inline auto outside = [](int x, int y, int R, int C) {return (min(x, y) < 0 || x >= R || y >= C); };
constexpr inline auto FAST = []() {cin.tie(0)->sync_with_stdio(0); };

constexpr bool DEBUG = 1;
#define debug if constexpr (DEBUG) cout


int cloud[51][51], nextcloud[51][51];

int board[51][51];
int RC;

int d[2][8] = {
	{0,-1,-1,-1,0,1,1,1},
	{-1,-1,0,1,1,1,0,-1}
};

void movecloud(int dir, int dist) {
	dist %= RC;
	For(i, 0, RC) {
		For(j, 0, RC) {
			int ii = (i + d[0][dir] * dist + RC) % RC;
			int jj = (j + d[1][dir] * dist + RC) % RC;
			nextcloud[ii][jj] = cloud[i][j];
		}
	}
	swap(cloud, nextcloud);
	memset(nextcloud, 0, sizeof nextcloud);
}

void rain() {
	For(i, 0, RC) {
		For(j, 0, RC) {
			board[i][j] += cloud[i][j];
		}
	}
}

int nxx(int x, int i) {
	return "0202"[i] - '1' + x;
}

int nyy(int y, int i) {
	return "0022"[i] - '1' + y;
}

void watercopy() {
	For(i, 0, RC) {
		For(j, 0, RC) {
			if (cloud[i][j] == 0) continue;
			For(k, 0, 4) {
				int x = nxx(i, k), y = nyy(j, k);
				if (outside(x, y, RC, RC)) continue;
				if (board[x][y]) board[i][j]++;
			}
		}
	}
}

void makecloud() {
	For(i, 0, RC) For(j, 0, RC) {
		if (cloud[i][j]) continue;
		if (board[i][j] >= 2) {
			board[i][j] -= 2; nextcloud[i][j] = 1;
		}
	}
	swap(cloud, nextcloud);
	memset(nextcloud, 0, sizeof nextcloud);
}

int main() {
	FAST();

	int N, M; cin >> N >> M;
	RC = N;

	For(i, 0, N) {
		For(j, 0, N) {
			cin >> board[i][j];
		}
	}

	queue<ii> q;
	For(i, 0, M) {
		int d, s; cin >> d >> s;
		q.push({ d - 1,s });
	}

	cloud[N - 1][0] = cloud[N - 1][1] = cloud[N - 2][0] = cloud[N - 2][1] = 1;

	while (M--) {
		auto [d, s] = q.front(); q.pop();
		movecloud(d, s);
		rain();
		watercopy();
		makecloud();
	}

	int res = 0;
	For(i, 0, RC) For(j, 0, RC) res += board[i][j];
	cout << res;

}