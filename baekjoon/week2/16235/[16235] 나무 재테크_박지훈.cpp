#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#include <algorithm>

#define FOR(i,n) for(int i=0;i<n;i++)
using namespace std;

int dx[8] = { -1,-1,-1,0,1,1,1,0 };
int dy[8] = { -1,0,1,1,1,0,-1,-1 };

struct tree
{
	int x, y, age;
	tree(int x, int y, int age) : x(x), y(y), age(age) {}

};
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int N, M, K;
	int addFood[11][11];
	vector<vector<int>> groundTree[11][11];
	vector<int> groundFood(11);
	cin >> N >> M >> K;
	FOR(i, N) {
		FOR(j, N) {
			groundFood[i] = 5;
		}
	}
	FOR(i,N) {
		FOR(j, N) {
			cin >> addFood[i][j];
		}
	}
	queue<tree> startTree;
	FOR(i, M) {
		int x, y;
		int age;
		cin >> x >> y >> age;
		groundTree[x-1][y-1].push_back(age);
	}
	while (K--) {
		//봄
		queue <tree> willBeFood;
		FOR(i, N) {
			FOR(j, N) {
				sort(groundTree[i][j].begin(), groundTree[i][j].end());
				vector<int> aliveTree;
				FOR(k, groundTree[i][j].size()) {
					if (groundFood[i][j] - groundTree[i][j][k] >=0) { // 가능
						groundFood[i][j] -= groundTree[i][j][k];
						aliveTree.push_back(groundTree[i][j][k] + 1);
					}
					else { // 불가능 작성
						willBeFood.push({ i,j,groundTree[i][j][k] });
						//groundTree[i][j].erase(groundTree[i][j].begin() + k);
					}
				}
				groundTree[i][j] = aliveTree;
			}
		}
		//여름
		while (!willBeFood.empty()) {
			int x = willBeFood.front().x;
			int y = willBeFood.front().y;
			int age = willBeFood.front().age;
			willBeFood.pop();
			groundFood[x][y] += age / 2;
		}
		queue<tree> willBePropa;
		//가을
		FOR(i, N) {
			FOR(j, N) {
				FOR(k, groundTree[i][j].size()) {
					if (groundTree[i][j][k] % 5 == 0) willBePropa.push({i, j, -1});
				}
			}
		}
		//번식 나무 추가
		while (!willBePropa.empty()) {
			int x = willBePropa.front().x;
			int y = willBePropa.front().y;
			willBePropa.pop();
			FOR(i, 8) {
				int nx = x + dx[i];
				int ny = y + dy[i];
				if (nx >= 0 && ny >= 0 && nx < N && ny < N) groundTree[nx][ny].push_back(1);
			}
		}
		//겨울
		FOR(i, N) {
			FOR(j, N) {
				groundFood[i][j] += addFood[i][j];
			}
		}
	}
	int treeCount = 0;

	FOR(i, N) {
		FOR(j, N) {
			treeCount += groundTree[i][j].size();
		}
	}
	cout << treeCount << endl;
}/*
 봄 이제 나이 만큼 양분 빼고, 나이 증가
나이가 어린 나무부터 양분 먹음
양분이 부족하다면 나이만큼 양분을 먹을 수 없는 나무 => 즉시 죽음

여름 => 봄에 죽은 나무 => 양분이 됨
각각 죽은 나무마다 나이를 2로 나눈 값이 나무에 있던 칸에 양분이 추가

가을 => 나무 번식, 나무 번식 나이 => 5의 배수
인전합 칸에 나무 나이가 1인 나무 생성 => 인접은 8개

겨울 => 양분 수동 추가
*/