#include <iostream>
#include <algorithm>
#include <vector>
#define endl '\n'

using namespace std;

int M, S;
int fishNow[5][5][8];
int fishNext[5][5][8];
int fishCopy[5][5][8];
int fishSmell[5][5];
int visitFish[5][5];
int shark[2];

int dx[8] = { -1,-1,0,1,1,1,0,-1 };
int dy[8] = { 0,-1,-1,-1,0,1,1,1 };
int sdx[4] = { 0,-1,0,1 };
int sdy[4] = { -1,0,1,0 };
void input() {
	cin >> M >> S;
	for (int i = 0; i < M; i++) {
		int x, y, d;
		cin >> y >> x >> d;
		d--;
		fishNow[y][x][d]++;
	}
	int x, y;
	cin >> y >> x;
	shark[0] = x;
	shark[1] = y;
}
//냄새 갱신 메서드
void renewSmell(int bestMoveD) {
	int sharkBestMoveX = shark[0] + sdx[bestMoveD];
	int sharkBestMoveY = shark[1] + sdy[bestMoveD];
	if (sharkBestMoveX < 1 || sharkBestMoveY < 1 || sharkBestMoveX >5 || sharkBestMoveY>5) {
		return;
	}
	for (int i = 0; i < 8; i++) {
		if (fishNow[sharkBestMoveY][sharkBestMoveX][i] != 0) {
			for (int d = 0; d < 8; d++) {
				fishNow[sharkBestMoveY][sharkBestMoveX][d] = 0;
				fishSmell[sharkBestMoveY][sharkBestMoveX] = 3;
			}
		}
	}
	shark[0] = sharkBestMoveX;
	shark[1] = sharkBestMoveY;
}
// 상어 범위 메서드
bool sharkCheckRange(int x, int y) {
	if (x >= 1 && y >= 1 && x < 5 && y < 5) return true;

	return false;
}
//물고기 범위 메서드
bool checkRange(int x, int y) {
	if (x >= 1 && y >= 1 && x < 5 && y < 5) {

		if (x == shark[0] && y == shark[1]) return false;
		if (fishSmell[y][x] == 0)return true;

	}
	return false;
}
//물고기 먹는 메서드
int eatFish(int x, int y) {
	int eatFishSum = 0;
	bool flag = 1;
	for (int i = 0; i < 8; i++) {
		if (fishNow[y][x][i] != 0 && visitFish[y][x] == 0) {
			eatFishSum += fishNow[y][x][i];
			flag = 0;
		}
	}
	if (!flag) visitFish[y][x] = 1;
	return eatFishSum;
}
//방문 기록 초기화 => 앞 뒤 앞 방지
void visitFishClear() {
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			visitFish[i][j] = 0;
		}
	}
}
void move() {
	while (S--) {
		for (int i = 1; i < 5; i++) { // 복사
			for (int j = 1; j < 5; j++) {
				for (int d = 0; d < 8; d++) {
					fishCopy[i][j][d] = fishNow[i][j][d];
				}
			}
		}
		for (int i = 1; i < 5; i++) { // 이동
			for (int j = 1; j < 5; j++) {
				for (int d = 0; d < 8; d++) {
					int fishD = d;
					int fishNum = fishNow[i][j][d];
					int x = j;
					int y = i;
					if (fishNum == 0) continue;
					for (int a = 0; a < 8; a++) {
						int nd = (d - a + 8) % 8;
						int nx = x + dx[nd];
						int ny = y + dy[nd];
						if (checkRange(nx, ny)) { // 이동완료
							fishNext[ny][nx][nd] += fishNow[y][x][fishD];
							fishNow[y][x][fishD] = 0;
							break;
						}
						else {
							if (a == 7) { // 아예 못 움직였을 때
								fishNext[y][x][d] += fishNow[y][x][fishD];
								fishNow[y][x][fishD] = 0;
							}
						}
					}


				}
			}
		}
		for (int i = 1; i < 5; i++) { // fishNow를 fishNext로 변환
			for (int j = 1; j < 5; j++) {
				for (int d = 0; d < 8; d++) {
					fishNow[i][j][d] = fishNext[i][j][d];
					fishNext[i][j][d] = 0;
				}
			}
		}
		int bestMoveF;
		int bestMoveS;
		int bestMoveT;
		bool flag = true;
		int maxEat = 0;
		for (int i = 0; i < 4; i++) { // 상어 이동 4의 3중 for문
			for (int j = 0; j < 4; j++) {
				for (int k = 0; k < 4; k++) {
					int sharkX = shark[0];
					int sharkY = shark[1];;
					int sharkFirstX = sharkX + sdx[i];
					int sharkFirstY = sharkY + sdy[i];
					int sharkSecondX = sharkFirstX + sdx[j];
					int sharkSecondY = sharkFirstY + sdy[j];
					int sharkThirdX = sharkSecondX + sdx[k];
					int sharkThirdY = sharkSecondY + sdy[k];
					int eatFishSum = 0;
					if (sharkCheckRange(sharkFirstX, sharkFirstY) && sharkCheckRange(sharkSecondX, sharkSecondY) && sharkCheckRange(sharkThirdX, sharkThirdY)) {
						eatFishSum += eatFish(sharkFirstX, sharkFirstY);
						eatFishSum += eatFish(sharkSecondX, sharkSecondY);
						eatFishSum += eatFish(sharkThirdX, sharkThirdY);
						if (flag) {
							bestMoveF = i;
							bestMoveS = j;
							bestMoveT = k;
							maxEat = eatFishSum;
							flag = false;
						}
						if (maxEat < eatFishSum) {
							bestMoveF = i;
							bestMoveS = j;
							bestMoveT = k;
							maxEat = eatFishSum;
						}
						visitFishClear();
					}
				}
			}
		}
		// 냄새 및 물고기 상태 갱신
		renewSmell(bestMoveF);
		renewSmell(bestMoveS);
		renewSmell(bestMoveT);
		// 냄새 제거 
		for (int i = 1; i < 5; i++) {
			for (int j = 1; j < 5; j++) {
				if (fishSmell[i][j] != 0) fishSmell[i][j]--;
			}
		}
		//fishCopy 완료
		for (int i = 1; i < 5; i++) {
			for (int j = 1; j < 5; j++) {
				for (int d = 0; d < 8; d++) {
					fishNow[i][j][d] += fishCopy[i][j][d];
					fishCopy[i][j][d] = 0;
				}
			}
		}
	}
	int fishSumResult = 0;
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			for (int d = 0; d < 8; d++) {
				fishSumResult += fishNow[i][j][d];
			}
		}
	}

	cout << fishSumResult << endl;
}
void run() {
	input();
	move();
}
int main() {
	run();
}