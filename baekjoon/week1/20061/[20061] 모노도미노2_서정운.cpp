#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;

#define For(i,a,b) for(int i=a;i<b;i++)
#define outside(x,y,R,C) (min(x,y) < 0 || x >=R || y >= C)
#define FAST (cin.tie(0)->sync_with_stdio(0))
#define nx(x,i) (&quot;0121&quot;[i] - &apos;1&apos; + x)
#define ny(y,i) (&quot;1210&quot;[i] - &apos;1&apos; + y)
#define endl '\n'
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()

// front가 위, back이 아래
deque<int> green, blue;

void push(deque<int>& dq, int n) {

	// 블록이 없다면, 바로 넣고 나간다.
	if (dq.empty()) {
		dq.push_back(n); return;
	}

	// 충돌이 있을 때까지 내려간다.
	// 충돌이 생긴다면, 그 이전 칸에 넣는다.
	For(i, 0, dq.size()) {
		if (dq[i] & n) {
			if (i == 0) {
				dq.push_front(n); return;
			}
			else {
				dq[i - 1] |= n; return;
			}
		}
	}

	// 충돌이 없다면, 마지막 칸에 넣는다.
	dq.back() |= n;
}

int scoring(deque<int>& dq) {
	auto iter = remove_if(all(dq), [](int n) {return n == 15; });
	int res = dq.end() - iter;
	dq.erase(iter, dq.end());
	return res;
}

int main() {
	FAST;

	int N; cin >> N;

	int score = 0;

	For(i, 0, N) {
		int t, x, y; cin >> t >> x >> y;

		int g, b; g = b = 0;

		g = 1 << y; b = 1 << x;
		if (t == 2) g |= 2 << y;
		if (t == 3) b |= 2 << x;

		bool flag;

		push(green, g);
		if (t == 3) push(green, g);

		push(blue, b);
		if (t == 2) push(blue, b);

		score += scoring(green);
		score += scoring(blue);

		while (green.size() > 4) green.pop_back();
		while (blue.size() > 4) blue.pop_back();

// #define DEBUG
#ifdef DEBUG

		cout << "===green===" << endl;
		For(i, 0, green.size()) {
			For(j, 0, 4) {
				if (green[i] & 1 << j) cout << 1;
				else cout << 0;
			}
			cout << endl;
		}

		cout << "===blue===" << endl;
		For(i, 0, blue.size()) {
			For(j, 0, 4) {
				if (blue[i] & 1 << j) cout << 1;
				else cout << 0;
			}
			cout << endl;
		}
		cout << endl;

#endif

	}

	int res = 0;

	while (green.size()) {
		int now = green.front(); green.pop_front();
		while (now) {
			if (now & 1) res++; now >>= 1;
		}
	}

	while (blue.size()) {
		int now = blue.front(); blue.pop_front();
		while (now) {
			if (now & 1) res++; now >>= 1;
		}
	}

	cout << score << ' ' << res;

}