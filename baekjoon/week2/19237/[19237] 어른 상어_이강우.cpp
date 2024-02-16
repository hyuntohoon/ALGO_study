//
// Created by newbi on 2024-02-15.
//
#include <iostream>
#include <vector>
#include <algorithm>
#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'

using namespace std;

int N, M, K, T;
int arr[21][21];
int smellNo[21][21];
int smell[21][21];
bool life[404];
pair<int, int> cord[404]; //상어 좌표 저장
int dir[404];    //상어 현재 방향 저장
int ddir[404][4][4];    //n번 상어의 m번 방향 바라볼 때 4개
int dx[] = { -1,1,0,0 };
int dy[] = { 0,0,-1,1 };  //위 아래 왼쪽 오른쪽

void fastIO() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
}
bool out(int x, int y) {
	return x <1 || x>N || y <1 || y >N;
}
void makeSmell() {
	For(i, 1, M + 1) {
		if (life[i]) {    //상어가 살아 있다면
			int x = cord[i].first;
			int y = cord[i].second;
			smellNo[x][y] = i;  //상어 인덱스
			smell[x][y] = K;    //K번 이동하면 사라짐
		}
	}
}
void print() {
	For(i, 1, N + 1) {
		For(j, 1, N + 1) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	For(i, 1, N + 1) {
		For(j, 1, N + 1) {
			cout << smell[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	For(i, 1, N + 1) {
		For(j, 1, N + 1) {
			cout << smellNo[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

}
void decrease() {
	For(i, 1, N + 1) {
		For(j, 1, N + 1) {
			if (smell[i][j]) {
				smell[i][j]--;  //1빼고
				if (!smell[i][j]) {   //0이 되었다면
					smellNo[i][j] = 0;  //인덱스 초기화
				}
			}
		}
	}
}
pair<int, int> getWay(int idx) {
	pair<int, int> ret;
	bool found = false;
	int x = cord[idx].first;
	int y = cord[idx].second;

	For(i, 0, 4) {
		int tmpdir = ddir[idx][dir[idx]][i];
		int qx = x + dx[tmpdir];  //상어의 인덱스,방향,우선순위
		int qy = y + dy[tmpdir];
		if (out(qx, qy)) continue;
		if (!smell[qx][qy]) {
			ret = { qx,qy };
			//cout <<tmpdir<<endl;
			dir[idx] = tmpdir;  //방향 업데이트
			found = true;
			break;
		}
	}
	if (!found) {
		For(i, 0, 4) {
			int tmpdir = ddir[idx][dir[idx]][i];

			int qx = x + dx[tmpdir];
			int qy = y + dy[tmpdir];
			if (out(qx, qy)) continue;
			if (smellNo[qx][qy] == idx) {
				ret = { qx,qy };
				//cout <<tmpdir<<endl;
				dir[idx] = tmpdir;  //방향 업데이트
				break;
			}
		}
	}
	return ret;
}
bool check() {
	int sharkCnt = 0;
	For(i, 1, M + 1) {
		if (life[i]) sharkCnt++;
	}
	return sharkCnt == 1;
}
void sharkMove() {
	while (true) {
        if (check()) {
            break;
        }
        if (T >= 1000) {
            T = -1;
            break;
        }
		For(i, 1, M + 1) {
			if (life[i]) {
				auto nxt = getWay(i);   //다음 좌표 받는다.
				arr[cord[i].first][cord[i].second] = 0; // 상어 떠남

				if (arr[nxt.first][nxt.second]) { //상어가 있을 경우
					if (arr[nxt.first][nxt.second] > i) {  //내가 먹을 수 있는 경우
						life[arr[nxt.first][nxt.second]] = false;
						cord[i].first = nxt.first;	//좌표 업데이트
						cord[i].second = nxt.second;
						arr[cord[i].first][cord[i].second] = i; //다음 걸로 업데이트
					}
					else {   //내가 먹히는 경우
						life[i] = false;

					}
				}
				else {   //상어가 없을 경우
					cord[i].first = nxt.first;
					cord[i].second = nxt.second;    //좌표 업데이트
					arr[cord[i].first][cord[i].second] = i; //맵에 업데이트
				}

			}
		}
		T++;    //시간 증가
		decrease();
		makeSmell();
		//print();


	}
}

int main() {
	fastIO();
	cin >> N >> M >> K;
	For(i, 1, N + 1) {
		For(j, 1, N + 1) {
			cin >> arr[i][j];
			if (arr[i][j] != 0) { //상어가 있다면
				cord[arr[i][j]] = { i,j };
				life[arr[i][j]] = true; //생명 준다.
				smellNo[i][j] = arr[i][j];  //번호 남긴다.
				smell[i][j] = K;
			}
		}
	}
	int t;
	For(j, 1, M + 1) {
		cin >> t;
		dir[j] = t - 1;
	}
	For(j, 1, M + 1) {
		For(k, 0, 4) {
			For(l, 0, 4) {
				cin >> t;
				ddir[j][k][l] = t - 1;   //4개 입력
			}
		}
	}
	sharkMove();

	cout << T << endl;

	return 0;
}