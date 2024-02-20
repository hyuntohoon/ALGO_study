
#include <iostream>
#include <vector>
#include <queue>
#define FOR(i,n) for(int i=0;i<n;i++)
int dx[8] = { 0,-1,-1,-1,0,1,1,1 };
int dy[8] = { -1,-1,0,1,1,1,0,-1 };

int diaX[4] = { -1,-1,1,1 };
int diaY[4] = { -1, 1,-1,1 };
using namespace std;
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N; // 크기
	int M; // 이동횟수
	int board[51][51]; // 보드
	bool visitCloud[51][51];
	FOR(i, 51) {
		FOR(j, 51) {
			visitCloud[i][j] = 0;
		}
	}
	cin >> N >> M;
	FOR(i,N) {
		FOR(j, N) {
			cin >> board[i][j];
		}
	}
	queue <pair<int, int>> cloudMove;
	queue <pair<int, int>> cloud;
	FOR(i, M) {
		int d, s;
		cin >> d >> s;
		cloudMove.push(make_pair(d, s));
	}
	cloud.push(make_pair(N-1, 0));
	cloud.push(make_pair(N-1, 1));
	cloud.push(make_pair(N-2, 0));
	cloud.push(make_pair(N-2, 1));
	queue <pair<int,int >> copyWater;
	while (M--) {
		int nowD = cloudMove.front().first-1;
		int nowS = cloudMove.front().second;
		cloudMove.pop();
		queue<pair<int, int>> cloudVisitTemp;
		while (!cloud.empty()) {
			int x = cloud.front().first;
			int y = cloud.front().second;
			cloudVisitTemp.push(make_pair(x, y));
			cloud.pop();
			int nx = x + (dx[nowD] * nowS);
			int ny = y + (dy[nowD] * nowS);
			if (nx < 0) nx = N + nx%N;
			if (nx > N) nx = nx%N;
			if (ny < 0) ny = N + ny%N;
			if (ny > N) ny = ny%N ;
			if (nx == N) nx = 0;
			if (ny == N) ny = 0;
			board[nx][ny]++;
			copyWater.push(make_pair(nx, ny));
			visitCloud[nx][ny] = 1;
		}
		while (!copyWater.empty()) {
			int x = copyWater.front().first;
			int y = copyWater.front().second;
			copyWater.pop();
			int copyCnt = 0;
			FOR(i, 4) {
				int nx = x + diaX[i];
				int ny = y + diaY[i];
				if (nx >= 0 && ny >= 0 && nx < N && ny < N) {
					if (board[nx][ny] != 0)copyCnt++;
				}
			}
			board[x][y] += copyCnt;
		}
		FOR(i, N) {
			FOR(j, N) {
				if (board[i][j] > 1 && visitCloud[i][j] == 0) {
					board[i][j] -= 2;
					visitCloud[i][j] = 1;
					cloud.push(make_pair(i, j));
				}
				if (visitCloud[i][j]) visitCloud[i][j] = 0;
			}
		}
		/*while (!cloudVisitTemp.empty()) {
			int x = cloudVisitTemp.front().first;
			int y = cloudVisitTemp.front().second;
			cloudVisitTemp.pop();
			visitCloud[x][y] = 0;
		}*/
	}
	int result = 0;
	FOR(i, N) {
		FOR(j, N) {
			result += board[i][j];
		}
	}
	cout << result << endl;
}