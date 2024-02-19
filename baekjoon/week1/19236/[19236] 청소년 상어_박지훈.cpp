#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>

#define FOR(i,n) for(int i=0;i<n;i++)
using namespace std;
//int fishD[16];
int *tempFishD;
int **board;
int *startFishD;
int sharkD;
int sharkX;
int sharkY;
int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,-1,-1,-1,0,1,1,1 };
int sharkSum;
int result = -1;

bool rangeCheck(int x, int y) {
	if (x >= 0 && y >= 0 && x < 4 && y < 4) return true;
	return false;
}

void startShark(){
	sharkD = startFishD[board[0][0]];
	sharkSum += board[0][0]+1;
	board[0][0] = -1;
}
int** fishMove(int sharkNowX, int sharkNowY, int **nowBoard, int *nowFishD) {
	int nowFishNum = 0;
	tempFishD = nowFishD;
	while (true) {
		if (nowFishNum == 16) return nowBoard;
		bool flag = 0;
		FOR(i, 4) {
			if (flag) break;
			FOR(j, 4) {
				if (flag) break;
				if (nowFishNum == nowBoard[i][j]) {
					flag = 1;
					int x = i;
					int y = j;
					for (int d = 0; d < 8; d++) {
						int nd = (tempFishD[nowFishNum] + d) % 8;
						int nx = x + dx[nd];
						int ny = y + dy[nd];
						if (rangeCheck(nx, ny)) {
							if (nx == sharkNowX && ny == sharkNowY) continue;
							swap(nowBoard[x][y], nowBoard[nx][ny]);
							tempFishD[nowBoard[nx][ny]] = nd;
							break;
						}
					}
					nowFishNum++;
				}
			}
		}
		if (!flag) nowFishNum++;
	}
	return nowBoard;
}
void run(int sharkNowX, int sharkNowY, int nowSharkD, int sharkNowSum, int **nowBoard, int *fishD) {
	cout <<"nowS"<< sharkNowX << " " << sharkNowY <<" "<<nowSharkD <<endl;
	FOR(i, 4) {
		FOR(j, 4) {
			if (i == sharkNowX && j == sharkNowY) cout << nowSharkD*-1 << " ";
			else cout << nowBoard[i][j] + 1 << " ";
		}
		cout << endl;
	}
	cout <<"D"<< endl;
	FOR(i, 4) {
		FOR(j, 4) {
			if (i == sharkNowX && j == sharkNowY) cout << nowSharkD * -1 << " ";
			else cout << fishD[nowBoard[i][j]] << " ";
		}
		cout << endl;
	}
	cout << endl;
	int **movedFishBoard = fishMove(sharkNowX, sharkNowY, nowBoard, fishD);
	cout << "moved" << endl;
	FOR(i, 4) {
		FOR(j, 4) {
			if (i == sharkNowX && j == sharkNowY) cout << nowSharkD * -1 << " ";
			else cout << movedFishBoard[i][j] + 1 << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "D" << endl;
	FOR(i, 4) {
		FOR(j, 4) {
			if (i == sharkNowX && j == sharkNowY) cout << nowSharkD * -1 << " ";
			else cout << tempFishD[nowBoard[i][j]] << " ";
		}
		cout << endl;
	}
	cout << endl;

		int x = sharkNowX;
		int y = sharkNowY;
		bool flag = 0;
		for (int k = 1; k < 4; k++) {
			int nx = x + (dx[nowSharkD] * k);
			int ny = y + (dy[nowSharkD] * k);
			int **tempNowBoard;
			tempNowBoard = new int*[4];
			for (int i = 0; i < 4; i++) {
				tempNowBoard[i] = new int[4];
			}
			FOR(i, 4) {
				FOR(j, 4) {
					tempNowBoard[i][j] = movedFishBoard[i][j];
				}
			}
			if (rangeCheck(nx, ny) && tempNowBoard[nx][ny] != -1) { // 이동 가는한 곳이 연속적이라면 그 곳에도 물고기가 있어야만 하는지 중요
				int tempNum = tempNowBoard[nx][ny];
				cout << tempNowBoard[nx][ny] << " " << tempFishD[tempNowBoard[nx][ny]];
				int tempD = tempFishD[tempNowBoard[nx][ny]];
				tempNowBoard[nx][ny] = -1;
				flag = 1;
				run(nx, ny, tempD, (sharkNowSum + tempNum + 1), tempNowBoard, tempFishD);
			}
		}
		if (!flag) { // 상어 이동 불가능시 종료
			cout << "cout"<<sharkNowSum << endl;
			result = max(sharkNowSum, result);
			return;
		}
	

}
int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	board = new int*[4];
	for (int i = 0; i < 4; i++) {
		board[i] = new int[4];
	} 
	startFishD = new int[16];
	FOR(i, 4) {
		FOR(j, 4) {
			int tempFishNum;
			int startTempFishD;
			cin >>tempFishNum >> startTempFishD;
			board[i][j] = tempFishNum-1;
			startFishD[tempFishNum-1] = startTempFishD -1;
		}
	}
	startShark();
	run(sharkX, sharkY, sharkD, sharkSum, board, startFishD);
	cout << result << endl;
	FOR(i, 4) {
		FOR(j, 4) {
			cout << board[i][j]+1 << " ";
		}
		cout << endl;
	}
}