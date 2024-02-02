#include <iostream>
#include <algorithm>
#include <vector>
#define endl '\n'
using namespace std;

int N, M;
int arr[9][9];
int cctvNum = 0;
int cctvDir[9];
int cctvVis[9];
vector <pair<int,pair<int, int>>> V;
int room[9][9];
int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
int ans = 9876543210;

void checkCctv2(int x, int y, int dir, int tempArr[][9]) {// 시작지점부터 dir 방향으로 직진
	while (N > y && M > x && x >= 0 && y >= 0 && tempArr[y][x] != 6) {
		tempArr[y][x] = 1;
		x = x + dx[dir];
		y = y + dy[dir];
	}
}

void cctvRot() { // 방향 돌리고 실행
	int tempArr[9][9];
	copy(&arr[0][0], &arr[0][0] + 9 * 9, &tempArr[0][0]); //배열 복제

	for (int i = 0; i < cctvNum; i++) {
		int cctv = V[i].first;
		int x = V[i].second.second;
		int y = V[i].second.first;
		int nowDir = cctvDir[i];
		if (cctv == 1) checkCctv2(x, y, nowDir, tempArr);

		if (cctv == 2) {
			int nowDir2 = (nowDir + 2) % 4;
			checkCctv2(x, y, nowDir, tempArr);
			checkCctv2(x, y, nowDir2, tempArr);
		}
		if (cctv == 3) {
			int nowDir2 = (nowDir + 3) % 4;
			checkCctv2(x, y, nowDir, tempArr);
			checkCctv2(x, y, nowDir2, tempArr);
		}
		if (cctv == 4) {
			int nowDir2 = (nowDir + 2) % 4;
			int nowDir3 = (nowDir + 3) % 4;
			checkCctv2(x, y, nowDir, tempArr);
			checkCctv2(x, y, nowDir2, tempArr);
			checkCctv2(x, y, nowDir3, tempArr);
		}
		if (cctv == 5) {
			int nowDir = 0;
			int nowDir2 = (nowDir + 2) % 4;
			int nowDir3 = (nowDir + 3) % 4;
			int nowDir4 = (nowDir + 1) % 4;
			checkCctv2(x, y, nowDir4, tempArr);
			checkCctv2(x, y, nowDir, tempArr);
			checkCctv2(x, y, nowDir2, tempArr);
			checkCctv2(x, y, nowDir3, tempArr);
		}
	}
	int result = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			if (tempArr[i][j] == 0) result++; // 감시받지 않는 구역만 카운트
		}
	}
	ans = min(result, ans);
}

void go(int cnt) {
	if (cnt == cctvNum) {
		cctvRot();
		return;
	}
	for (int j = 0; j < 4; j++) {
		cctvDir[cnt] = j; // 현재 CCTV의 방향 설정
		go(cnt + 1); // 다음 CCTV 방향 설정으로 넘어감
	}
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			int temp;
			cin >> temp;
			if (temp != 0 && temp != 6) {
				cctvNum++;
				V.push_back(make_pair(temp,make_pair(i, j)));
				continue;
			}
			arr[i][j] = temp;
		}
	}
	
	go(0);

	cout << ans << endl;
}