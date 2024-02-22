#include <bits/stdc++.h>
using namespace std;

#define For(i,a,b) for(int i=a;i<b;i++)
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
using pii = pair<int, int>;

int gears[4][8];
int l[4], r[4];

void update(int nth, int dir) {
	l[nth] = (l[nth] - dir + 8) % 8;
	r[nth] = (r[nth] - dir + 8) % 8;
}

// 왼쪽으로 전파
void left(int nth, int dir) {
	if (nth < 0) return;
	if (gears[nth][r[nth]] != gears[nth+1][l[nth + 1]]) {
		left(nth - 1, dir * -1);
		update(nth, dir);
	}
}

// 오른쪽으로 전파
void right(int nth, int dir) {
	if (nth >= 4) return;
	if (gears[nth-1][r[nth - 1]] != gears[nth][l[nth]]) {
		right(nth + 1, dir * -1);
		update(nth, dir);
	}
}

int main() {

	For(i, 0, 4) {
		For(j, 0, 8) {
			char c; cin >> c;
			gears[i][j] = c - '0';
		}
		l[i] = 6; r[i] = 2;
	}

	int K; cin >> K;
	while (K--) {
		int nth, dir; cin >> nth >> dir;
		nth--;
		left(nth - 1, dir * -1);
		right(nth + 1, dir * -1);
		update(nth, dir);

// #define DEBUG
#ifdef DEBUG

		For(i, 0, 4) {
			cout << "l: " << l[i] << ", r: " << r[i] << endl;
		}
		cout << endl;

#endif

	}

	int res = 0;

	For(i, 0, 4) {
		int top = (l[i] + 2) % 8;
		if (gears[i][top]) res += 1 << i;
	}

	cout << res;

}