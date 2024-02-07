//
// Created by newbi on 2024-02-06.
//
#include <iostream>
#include <algorithm>
#include <vector>
#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'
using namespace std;

struct Fish {
	int x;
	int y;
	int dir;
	int num;
	Fish(int x, int y, int dir, int num) :x(x), y(y), dir(dir), num(num) {} //생성자
	bool operator<(Fish f) {	//정렬 시 번호 기준 정렬이 이루어진다. (연산자 오버로딩)
		return num < f.num;
	}
};

vector<Fish> fishes;	//물고기 집합

int arr[5][5];	//물고기의 번호
int ans = 0;
int dx[] = { -1,-1,0,1,1,1,0,-1 };	//반시계 방향으로 증가
int dy[] = { 0,-1,-1,-1,0,1,1,1 };

int sx;	//상어의 좌표
int sy;
int sdir;   //상어의 dir

void fastIO() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
}

void swap(int &n1, int &n2) {
	int temp = n1;
	n1 = n2;
	n2 = temp;
}

void print() {	//DEBUG
	For(i, 1, 5) {
		For(j, 1, 5) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void cord() {	//DEBUG
	for (auto elem : fishes) {
		cout << elem.num << "Num : " << elem.x << " : " << elem.y << "  direc : [" << elem.dir << "] " << '\n';
	}
}


bool out(int x, int y) {	//장외 처리
	return x < 1 || x >= 5 || y < 1 || y >= 5;
}

vector<pair<int, int>> sharkWays(int x, int y, int dir) {	//상어가 갈 수 있는 모든경로 반환
	vector<pair<int, int>> ways;
	while (true) {
		x = x + dx[dir];
		y = y + dy[dir];
		if (out(x, y)) break;
		if (arr[x][y] > 0) {  //물고기가 있다면 갈 수 있다.
			ways.push_back({ x, y });
		}
	}
	return ways;    //갈 수 있는 경우의 수 리턴
}



void fishMove() {
	sort(fishes.begin(), fishes.end());		//물고기 번호 순대로 정렬
	for (auto &fish : fishes) {	//첫번째 물고기 부터 이동한다.
		for (int i = 0; i < 8; i++) {	  //dir방향으로
			int qx = fish.x + dx[fish.dir];	//방향 이동
			int qy = fish.y + dy[fish.dir];

			if (out(qx, qy) || (qx == sx && qy == sy)) {	//나갔거나 상어의 좌표로 간다면
				fish.dir = (fish.dir + 1) % 8;	//반시계 회전
				continue;
			}
			//이동 할 수 있다면
			if (arr[qx][qy] != 0) {	//물고기가 있다면
				for (auto & f : fishes) {
					if (f.num == arr[qx][qy]) {
						swap(arr[qx][qy], arr[fish.x][fish.y]);   //바꾼다.
						f.x = fish.x;
						f.y = fish.y;
						break;
					}
				}

			}
			else {   //물고기가 없다면
				arr[qx][qy] = arr[fish.x][fish.y];  //다음 위치로 옮기고
				arr[fish.x][fish.y] = 0;    //현재 위치 초기화
			}

			fish.x = qx;	//현재 물고기 다음 위치로 이동
			fish.y = qy;
			break;	//다음 경우로 넘어간다.
		}

	}
}

void sharkMove(int x, int y, int dir, int sm) {
	sx = x;
	sy = y;
	sdir = dir;	//상어 정보 갱신

	fishMove();	//물고기가 이동하고

	auto ways = sharkWays( sx, sy, sdir);	//현재 상어의 위치와 방향
	if (ways.empty()) {		//더 이상 갈 길이 없다면
		ans = max(ans, sm);
		return;
	}
	vector<Fish> savePoint;
	int saveArr[5][5];
	copy(fishes.begin(), fishes.end(), back_inserter(savePoint));    //임시저장
	copy(&arr[0][0], &arr[0][0] + 25, &saveArr[0][0]);    //arr도 임시저장

	for (auto cord : ways) {
		x = cord.first;	//상어의 경로 경우의 수
		y = cord.second;

		for (auto f : fishes) {
			if (f.x == x && f.y == y) {
				dir = f.dir;   //방향 가져감
				break;
			}
		}
		int temp = arr[x][y];
		sm += temp;
		arr[x][y] = 0;    //물고기 죽음
		fishes.erase(remove_if(fishes.begin(), fishes.end(), [&](const Fish &f) {
			return f.x == x && f.y == y;
		}), fishes.end());   //물고기 벡터에서 제거
		//cout << "상어 이동" <<x<<" : "<<y <<endl;
		//print();
		sharkMove(x,y,dir,sm);
		sm -= temp;	//sm 원복한다.
		copy(&saveArr[0][0], &saveArr[0][0] + 25, &arr[0][0]);    //복구
		fishes.clear();
		copy(savePoint.begin(), savePoint.end(), back_inserter(fishes));    //임시저장
		//cout << "원상 복귀" << x << " : " << y << endl;
		//print();
	}



}

int main() {
	fastIO();
	int firstKill;
	int fdir;
	For(i, 1, 5) {
		For(j, 1, 5) {
			cin >> arr[i][j] >> fdir;
			if (i == 1 && j == 1) { //상어 자리라면
				firstKill = arr[i][j];
				arr[i][j] = 0;
				sdir = fdir-1;
				continue;
			}
			fishes.push_back(Fish(i, j, fdir - 1, arr[i][j]));	//물고기 대입
		}
	}
	sharkMove(1, 1, sdir, firstKill);

	cout << ans << endl;
	return 0;
}