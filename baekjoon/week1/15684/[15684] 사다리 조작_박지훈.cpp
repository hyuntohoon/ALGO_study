#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;
int N, M, H;
int arr[32][12];
int result[32];
int flag = -1;
void climbLadder(int nowX, int nowY, int nowI) {
	while (true) {
		if (nowY == H+1) {
			break;
		}
		if (arr[nowY][nowX] != 0) nowX = arr[nowY][nowX];
		nowY++;
	}
	result[nowI] = nowX;
}
void go(int end, int cnt,int x,int y) {
	if (flag != -1) return;
	if (end == cnt) {

		for (int i = 1; i <= N; i++) {
			climbLadder(i, 1, i);
			
		}
		for (int i = 1; i <= N; i++) {
			if (result[i] != i) break;
			if (i == N) {
				flag = end;
			}
		}
		return;
	}
	for (int i = y; i <= H; i++) {
		for (int j = x; j < N; j++) {
			if (arr[i][j] == 0 && arr[i][j + 1] == 0) {
				arr[i][j] = j + 1;
				arr[i][j + 1] = j;
				go(end, cnt + 1, j, i);
				arr[i][j] = 0;
				arr[i][j + 1] = 0;
			}
		}
		x = 1;
	}
}
int main() {
	cin >> N >> M >> H;
	for (int i = 0; i < M; i++) {
		int tempX, tempY;
		cin >> tempY >> tempX;
		arr[tempY][tempX] = tempX + 1;
		arr[tempY][tempX + 1] = tempX;
	}
	for (int i = 1; i <= N; i++) {
		climbLadder(i, 1, i);
		for (int i = 1; i <= N; i++) {
			if (result[i] != i) break;
			if (i == N) {
				flag = 0;
			}
		}
	}

	if (flag == -1) {
		go(1, 0, 1, 1);
		go(2, 0, 1, 1);
		go(3, 0, 1, 1);
	}
	if (flag != -1) cout << flag << endl;
	else cout << -1 << endl;
}