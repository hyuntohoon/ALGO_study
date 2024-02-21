#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

#define FOR(i,n) for(int i=0;i<n;i++)
using namespace std;

struct sharkSmell {
	int sharkNum, leftTime;
	sharkSmell() : sharkNum(0), leftTime(0) {}
	sharkSmell(int sharkNum, int leftTime) : sharkNum(sharkNum), leftTime(leftTime) {}
};

int dx[4] = { -1,1,0,0 };
int dy[4] = { 0,0,-1,1 };
int N, M, K;
vector<vector<vector<pair<int,int>>>> board(21, vector<vector<pair<int,int>>>(21, vector<pair<int,int>>(1,make_pair(0,-1)))); // first => 번호, second = 방향
vector<vector<vector<int>>> sharkPrio(402, vector<vector<int>>(4, vector<int>(4)));
vector<vector<sharkSmell>> sharkSmellBoard(21, vector<sharkSmell>(21));

void smellAdd() { // 냄새 저장
	FOR(i, N) {
		FOR(j, N) {
			int nowSharkNum = board[i][j][0].first;
			if (nowSharkNum != 0) {
				sharkSmellBoard[i][j].sharkNum = nowSharkNum;
				sharkSmellBoard[i][j].leftTime = K;
			}
		}
	}
}
struct willArrive {
	int x, y, nowSharkNum, nowDir;
	willArrive(int x, int y, int nowSharkNum, int nowDir) : x(x), y(y), nowSharkNum(nowSharkNum), nowDir(nowDir) {}
};
void sharkMove() {
	queue <willArrive> Q;
	FOR(i, N) {
		FOR(j, N) {
			int nowSharkNum = board[i][j][0].first;
			if (nowSharkNum != 0) {
				int x = i;
				int y = j;
				int d = board[i][j][0].second;
				bool flag = false;
				for (auto nowDir : sharkPrio[nowSharkNum][d]) {
					int nx = x + dx[nowDir];
					int ny = y + dy[nowDir];
					if (nx >= 0 && ny >= 0 && nx < N && ny < N && sharkSmellBoard[nx][ny].leftTime == 0) {
						flag = true;
						
						Q.push(willArrive(nx, ny, nowSharkNum, nowDir));
						board[x][y].erase(board[x][y].begin());
						if (board[x][y].size() == 0) board[x][y].push_back(make_pair(0, -1));
						break;
					}
				}
				if (!flag) {
					for (auto nowDir : sharkPrio[nowSharkNum][d]) {
						int nx = x + dx[nowDir];
						int ny = y + dy[nowDir];
						if (nx >= 0 && ny >= 0 && nx < N && ny < N && sharkSmellBoard[nx][ny].sharkNum == nowSharkNum) {
							Q.push(willArrive(nx, ny, nowSharkNum, nowDir));
							board[x][y].erase(board[x][y].begin());
							if (board[x][y].size() == 0) board[x][y].push_back(make_pair(0, -1));
							break;
						}
					}
				}
			}
		}
	}
	while (!Q.empty()) {
		int x = Q.front().x;
		int y = Q.front().y;
		int nowSharkNum = Q.front().nowSharkNum;
		int nowDir = Q.front().nowDir;
		Q.pop();
		if (board[x][y][0].first == 0) board[x][y].pop_back();
		board[x][y].push_back(make_pair(nowSharkNum, nowDir));
	}
	FOR(i, N) { // 냄새 감소
		FOR(j, N) {
			if (sharkSmellBoard[i][j].leftTime > 0) sharkSmellBoard[i][j].leftTime--;
		}
	}
}
bool isSharkAlone() {
	int sharkRemain = 0;
	FOR(i, N) {
		FOR(j, N) {
			if (board[i][j][0].first != 0) sharkRemain++;
		}
	}
	if (sharkRemain == 1) return true;
	return false;
}
void sharkFight() {
	FOR(i, N) {
		FOR(j, N) {
			sort(board[i][j].begin(), board[i][j].end());
			board[i][j].erase(board[i][j].begin() + 1, board[i][j].end());
		}
	}
}
int main() {

	cin >> N >> M >> K;
	FOR(i, N) { // 번호 입력
		FOR(j, N) {
			int temp;
			cin >> temp;
			if (temp != 0) board[i][j][0].first = temp;
		}
	}
	int startSharkDir[401];
	FOR(i, M) { // 방향 입력
		cin >> startSharkDir[i+1];
		startSharkDir[i + 1]--;
	}
	FOR(i, N) { // 번호 방향 설정
		FOR(j, N) {
			int nowSharkNum = board[i][j][0].first;
			board[i][j][0].second = startSharkDir[nowSharkNum];
		}
	}
	FOR(i, M) { // 우선순위 방향 저장
		FOR(j, 4) {
			int first, second, third, fourth;
			cin >> first >> second >> third >> fourth;

			sharkPrio[i+1][j][0] = first-1;
			sharkPrio[i+1][j][1] = second-1;
			sharkPrio[i+1][j][2] = third-1;
			sharkPrio[i+1][j][3] = fourth-1;
		}
	}
	smellAdd();
	int T = 1001;
	int nowTime = 0;
	while (T--) {
		if (isSharkAlone() ==true) {
			cout << nowTime << endl;
			return 0;
		}
		sharkMove();
		sharkFight();
		smellAdd();
		nowTime++;
	}

	cout << -1 << endl;
}