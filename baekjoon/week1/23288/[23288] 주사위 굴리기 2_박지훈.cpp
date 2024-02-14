#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

using namespace std;
int top = 1;
int rightSide = 3;
int leftSide = 4;
int front = 5;
int back = 2;
int bottom = 6;
int N, M, K;
int board[21][21];
int nowD;
int dx[4] = { 1,-1,0,0 };
int dy[4] = { 0,0,1,-1 };
int result;

void backMove(int x, int y) {
	if (nowD == 0 && x + 1 == M) nowD = 2;
	if (nowD == 1 && y + 1 == N) nowD = 3;
	if (nowD == 2 && x - 1 == -1) nowD = 0;
	if (nowD == 3 && y - 1 == -1) nowD = 1;
}
void move(int d) { // 회전 및 이동
	if (d == 0) {//동
		int temp = top;
		top = leftSide;
		leftSide = bottom;
		bottom = rightSide;
		rightSide = temp;
	}
	if (d == 1) {//남
		int temp = top;
		top = back;
		back = bottom;
		bottom = front;
		front = temp;
	}
	if (d== 2) {//서
		int temp = top;
		top = rightSide;
		rightSide = bottom;
		bottom = leftSide;
		leftSide = temp;
	}
	if(d == 3){
		int temp = top;
		top = front;
		front = bottom;
		bottom = back;
		back = temp;
	}
}
void compareBoard(int x, int y) {
	if (board[y][x] < bottom) {
		if (nowD == 0) {
			nowD = 1; return;
		}
		if (nowD == 1) {
			nowD = 2; return;
		}
		if (nowD == 2) {
			nowD = 3; return;
		}
		if (nowD == 3) {
			nowD = 0; return;
		}
	}
	if (board[y][x] > bottom) {
		//rotate(2);
		if (nowD == 0) {
			nowD = 3; return;
		}
		if (nowD == 1) {
			nowD = 0; return;
		}
		if (nowD == 2) {
			nowD = 1; return;
		}

		if (nowD == 3) {
			nowD = 2; return;
		}
	}
	
}
int bfs(int a, int b) {
	queue <pair<int, int>> Q;
	Q.push(make_pair(a, b));
	int sum = 0;
	bool visit[21][21];
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 21; j++) {
			visit[i][j] = 0;
		}
	}

	visit[b][a] = 1;
	sum += board[b][a];
	while (!Q.empty()) {//여기 문제
		int x = Q.front().first;
		int y = Q.front().second;
		Q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx >= 0 && ny >= 0 && nx < M && ny < N) {
				if (board[ny][nx] == board[y][x] && visit[ny][nx] == 0) {
					sum += board[ny][nx];
					visit[ny][nx] = 1;
					Q.push(make_pair(nx, ny));
				}
			}
		}
	}
	return sum;
}
void boardCheck() {
	int sx = 0;
	int sy = 0;
	while (K--) {
		backMove(sx, sy);
		move(nowD);
		if (nowD == 0) sx++;
		if (nowD == 1) sy++;
		if (nowD == 2) sx--;
		if (nowD == 3) sy--;

		compareBoard(sx, sy);
		result += bfs(sx, sy);
	}
}
int main() {

	cin >> N >> M >> K;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> board[i][j];
		}
	}
	boardCheck();
	cout << result;

}