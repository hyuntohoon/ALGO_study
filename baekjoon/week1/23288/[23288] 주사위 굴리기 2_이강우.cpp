//
// Created by newbi on 2024-02-12.
//
#include <iostream>
#include <vector>
#include <queue>

#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'

using namespace std;


int N,M,K,dir,score;
vector<int> dice = {1,6,3,4,2,5};
int arr[21][21];
bool visited[21][21];
int curX = 1, curY = 1;

void rollEast(){     //0: 윗면, 1: 아랫면, 2: 동, 3: 서, 4: 북, 5: 남
    dice = {dice[3],dice[2],dice[0],dice[1],dice[4],dice[5]};
}
void rollWest(){     //0: 윗면, 1: 아랫면, 2: 동, 3: 서, 4: 북, 5: 남
    dice = {dice[2],dice[3],dice[1],dice[0],dice[4],dice[5]};
}
void rollSouth(){    //0: 윗면, 1: 아랫면, 2: 동, 3: 서, 4: 북, 5: 남
    dice = {dice[4],dice[5],dice[2],dice[3],dice[1],dice[0]};
}
void rollNorth(){    //0: 윗면, 1: 아랫면, 2: 동, 3: 서, 4: 북, 5: 남
    dice = {dice[5],dice[4],dice[2],dice[3],dice[0],dice[1]};
}

int dx[] = {0,1,0,-1};  //동 남 서 북
int dy[] = {1,0,-1,0};

bool out(int x,int y){
    return x <1 || x >N || y < 1 || y > M;
}

void fastIO(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

int getScore(int x,int y){
    int cnt =1;
    int val = arr[x][y];
    queue<pair<int,int>> q;
    q.push({x,y});
    visited[x][y] = true;

    while(q.size()){
        auto cord = q.front(); q.pop();
        x = cord.first;
        y = cord.second;

        for(int i=0;i<4;i++){
            int qx = x+ dx[i];
            int qy = y +dy[i];

            if(out(qx,qy)||visited[qx][qy]) continue;
            if(arr[qx][qy] == val){
                cnt++;
                visited[qx][qy] = true;
                q.push({qx,qy});
            }
        }
    }
    fill(&visited[0][0],&visited[0][0]+21*21,false);
    return val * cnt;
}

void solve(){
    while(K--){
        int qx = curX +dx[dir];
        int qy = curY +dy[dir];

        if(out(qx,qy)){
            K++;
            dir = (dir+2)%4;    //반대 방향으로 변경
            continue;   //다시 실행
        }
        if(dir ==0){
            rollEast();
        }
        else if(dir == 1){
            rollSouth();
        }
        else if(dir == 2){
            rollWest();
        }
        else if (dir ==3){
            rollNorth();
        }
        curX = qx;
        curY = qy;  //현재 주사위 좌표 갱신
        score += getScore(curX,curY);   //현재 좌표 점수 갱신

        if(dice[1] > arr[curX][curY]){ //크면 시계 방향
            dir = (dir+1)%4;
        }
        else if(dice[1] < arr[curX][curY]){ //작으면 반시계 방향
            dir = dir-1;
            if(dir <0) dir = 3;
        }
    }
}


int main(){
    fastIO();
    cin >> N >> M >> K;
    For(i,1,N+1){
        For(j,1,M+1){
            cin >> arr[i][j];
        }
    }
    solve();
    cout << score << endl;
    return 0;
}
