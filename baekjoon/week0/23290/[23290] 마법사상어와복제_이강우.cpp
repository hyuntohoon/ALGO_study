//
// Created by newbi on 2024-02-05.
//
#include <iostream>
#include <vector>
#include <algorithm>

#define For(i,a,b)  for(int i=a;i<b;i++)
#define endl '\n'
using namespace std;
int sx,sy, M,S;
int dx[] = {0,-1,-1,-1,0,1,1,1};    //물고기 dir
int dy[] = {-1,-1,0,1,1,1,0,-1};

int cx[]={-1,0,1,0};    //상좌하우
int cy[]={0,-1,0,1};

vector <pair<int,pair<int,int>>> fishs;  //방향,위치
vector<pair<int,string>> moveDir;  //먹은 물고기 수, 이동 좌표
vector <pair<int,pair<int,int>>> copyFish;  //복사될 물고기들
int arr[5][5];      //바다
int smell[5][5];   //물고기의 냄새


void fastIO(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
bool custom(pair<int,string>p1 ,pair<int,string>p2){
    if(p1.first == p2.first){
        return p1.second < p2.second;
    }
    else{
        return p1.first > p2.first;
    }
}

bool out(int x,int y){
    return x <1 || x >4 || y < 1 || y >4;
}

void fishMove(){
    for(auto &fish : fishs){
        int x = fish.second.first;
        int y = fish.second.second;
        int dir = fish.first;
        arr[x][y]--;    //현재 물고기 감소
        for(int i=0;i<8;i++){
            int qx = x + dx[dir];
            int qy = y + dy[dir];

            if(out(qx,qy)|| (qx == sx && qy == sy) || smell[qx][qy] >0 ) {
                dir--;  //감소
                if(dir<0) dir =7; //음수 처리
                continue;
            }//나갔 거나 상어가 있는 지점 SKIP + 물고기 냄새도 SKIP

            fish.second.first = qx; //좌표 이동
            fish.second.second = qy;
            fish.first = dir;
            break;
        }
        arr[fish.second.first][fish.second.second]++;    //물고기 이동 자리로 이동
    }
}
void DFS(int x,int y,int sm, string st){
    if(st.length() == 3){
        moveDir.push_back({sm,st});
        return;
    }
    for(int i=0;i<4;i++){
        int qx = x + cx[i];
        int qy = y + cy[i];
        if(out(qx,qy)) continue;
        int eatFish = arr[qx][qy];
        arr[qx][qy] = 0;    //물고기 없애고
        DFS(qx, qy, sm + eatFish, st + to_string(i + 1));
        arr[qx][qy] = eatFish;  //나중에 원복
    }
}

void removeFish(int x,int y){
    fishs.erase(remove_if(fishs.begin(),fishs.end(),[x,y](const pair<int, pair<int, int>>& fish){
        return fish.second.first == x && fish.second.second == y;
    }),fishs.end());

}
void smellDecrease(){
    For(i,1,5){
        For(j,1,5){
            if(smell[i][j] > 0) smell[i][j]--;
        }
    }
}

void copyInit(){
    copyFish.clear();
    copy(fishs.begin(),fishs.end(), back_inserter(copyFish));   //물고기 카피한다.
}
void copyMagic(){
    for(auto elem :copyFish){
        fishs.push_back({elem.first,{elem.second.first,elem.second.second}});//복제 물고기 추가
        arr[elem.second.first][elem.second.second]++;//물고기 증가
    }
}

void sharkMove(){
    moveDir.clear();

    DFS(sx,sy,0,"");
    sort(moveDir.begin(),moveDir.end(),custom);
    string way = moveDir[0].second;
    for(auto c : way){
        sx = sx +cx[(c-'0')-1]; //실제 상어 이동
        sy = sy +cy[(c-'0')-1];
        //cout <<sx <<" "<<sy <<endl;
        if(arr[sx][sy]>0){  //가는 길에 물고기가 있다면
            arr[sx][sy] = 0;
            removeFish(sx,sy);  //물고기 삭제
            smell[sx][sy] = 3;  //2턴간 지속되는 물고기의 냄새가 생긴다.
        }
    }

}

void print(){   //DEBUG
    For(i,1,5){
        For(j,1,5){
            if(i == sx && j == sy){
                cout <<"S"<<" ";
            }
            else {
                cout << arr[i][j] << " ";
            }
        }
        cout << endl;
    }
    cout <<endl;
}

void dirPrint(){    //DEBUG
    for(auto elem : fishs)
        cout <<"X : "<< elem.second.first << "  Y : "<< elem.second.second <<"  Dir : "<< elem.first <<endl;
}
void smellPrint(){  //DEBUG
    cout << "smell" <<endl;
    For(i,1,5){
        For(j,1,5){
            cout << smell[i][j]<<" ";
        }
        cout <<endl;
    }
    cout <<endl;
}
int check(){
    int sm =0;
    for(int i=1;i<5;i++){
        for(int j=1;j<5;j++){
            sm += arr[i][j];
        }
    }
    return sm;
}

void solve(){
    for(int i=0;i<S;i++){
    copyInit();
    fishMove();
    sharkMove();
    smellDecrease();
    copyMagic();
    }
    cout << check() <<endl;
}


int main(){
    fastIO();
    cin >> M >> S;
    int x,y,dir;
    For(i,0,M){
        cin >> x >> y >> dir;
        arr[x][y]++;    //물고기 추가
        fishs.push_back({dir-1,{x,y}});//물고기를 집어넣는다.
    }
    cin >> sx >> sy;    //상어 위치

    solve();

    return 0;
}
