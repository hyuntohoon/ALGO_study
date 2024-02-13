//
// Created by newbi on 2024-02-13.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cmath>
#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'

using namespace std;

int N,curX,curY,ans;
vector<int> student[401];	//친한친구를 넣기위한 인접 리스트
bool visited[401][401];	//방문 처리할 배열
int arr[401][401];	//상어초등학교 2차원 배열
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
struct Friend {
    int x;
    int y;
    int cnt;
    int blk;
    Friend(int x, int y, int cnt,int blk) :x(x), y(y), cnt(cnt),blk(blk) {};
    bool operator<(Friend f) {
        if (cnt == f.cnt) {
            if (blk == f.blk) {
                if (x == f.x) {	//x가 같다면
                    return y < f.y;	//y기준으로 정렬
                }
                else {		//x 기준으로 정렬
                    return x < f.x;
                }
            }
            else {
                return blk > f.blk;
            }
        }
        else {	//cnt가 큰게 앞으로
            return cnt > f.cnt;
        }
    }
};

int dx[] = {0,0,-1,1};	//좌우상하
int dy[] = {-1,1,0,0};

bool out(int x, int y) {
    return x <1 || x > N || y < 1 || y > N;	//장외 처리
}


Friend searchFriend(int idx) {	//좌표와 친구 번호 넘긴다
    vector<Friend> fs;
    For(i, 1, N + 1) {
        For(j, 1, N + 1) {
            if (visited[i][j]) continue;
            Friend tmp(i, j, 0, 0);
            For(k, 0, 4) {
                int qx = tmp.x + dx[k];
                int qy = tmp.y + dy[k];
                if (out(qx, qy)) continue;	//장외 시 SKIP
                for (auto f : student[idx]) {	//친구와 겹치는 곳이 있는지?
                    if (f == arr[qx][qy]) {	//친구와 겹치면
                        tmp.cnt++;	//하나 증가
                        break;
                    }
                }
                if (!arr[qx][qy]) tmp.blk++;
            }
            fs.push_back(tmp);
        }
    }
    sort(fs.begin(), fs.end());
    /*
    for (auto elem : fs) {
        cout <<"cnt: " <<elem.cnt << " blk: "<<elem.blk<<"( "<< elem.x <<", "<<elem.y <<")"<< " ";
    }*/
    return fs[0];	//가장 우선순위 높은 것 리턴
}
void print() {
    For(i, 1, N + 1) {
        For(j, 1, N + 1) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void check() {
    For(i, 1, N + 1) {
        For(j, 1, N + 1) {
            int cnt = 0;
            For(k, 0, 4) {
                int qx = i + dx[k];
                int qy = j + dy[k];
                if (out(qx, qy)) continue;
                for (auto f : student[arr[i][j]]) {	//친구와 겹치는 곳이 있는지?
                    if (f == arr[qx][qy]) {	//친구와 겹치면
                        cnt++;
                        break;
                    }
                }
            }

            if (cnt == 1) {
                ans += 1;
            }
            else if (cnt == 2) {
                ans += 10;
            }
            else if (cnt == 3) {
                ans += 100;
            }
            else if (cnt == 4) {
                ans += 1000;
            }
        }
    }
}

int main() {
    fastIO();
    cin >> N;
    int sNo, tmp;
    queue<int> input;
    For(i, 0, pow(N, 2)) {
        cin >> sNo;
        input.push(sNo);
        For(j, 0, 4) {
            cin >> tmp;	//친한 친구 4명 PUSH
            student[sNo].push_back(tmp);
        }
    }


    For(i, 0, pow(N, 2)) {	//하나씩 pop해 학생체크한다.
        int idx = input.front(); input.pop();
        Friend f= searchFriend(idx);	// 1,2,3번을 모두 고려한 좌표가 리턴됨
        arr[f.x][f.y] = idx;	//학생을 자리에 앉힌다.
        visited[f.x][f.y] = true;
        //print();	DEBUG
    }
    check();	//만족도 체크

    cout << ans << endl;

    return 0;
}