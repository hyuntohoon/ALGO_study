//
// Created by newbi on 2024-01-31.
//
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

int ans = 1e8;	//가장 최소의 값 을 구하라

int N, M;
int arr[10][10];
bool detect[10][10];

vector<pair<int,pair<int, int>>> CCTV;	//CCTV 유형 (1 ~ 5), 좌표

int dx[] = { 0,-1,0,1 };	//좌,상,우 하
int dy[] = { -1,0,1,0 };


void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

bool out(int x, int y) {	//나갔을 떄
    return x < 0 || y < 0 || x >= N || y >= M;
}

void DFS(int x,int y,int dir){
    int qx = x + dx[dir];
    int qy = y + dy[dir];   //해당 방향으로 전진한다.

    if(out(qx,qy) || arr[qx][qy] == 6) return;  //나가거나 벽을 만났다면 종료

    if(arr[qx][qy] == 0) {  //빈 공간이라면 CCTV일 경우 감지하면 안됨
        detect[qx][qy] = true;
    }
    DFS(qx,qy,dir); //다음 좌표 넘김

}

void detection(int x, int y, int type,int dir) {
    queue<pair<int,int>> q;
    if(type == 1){  //첫 번째 타입
        DFS(x,y,dir);
    }
    else if(type == 2){ //두 번째 타입
        if (dir<2){   //0 ~ 1
            DFS(x,y,0); //좌
            DFS(x,y,2); //우
        }
        else{   //2~3
            DFS(x,y,1); //상
            DFS(x,y,3); //하
        }
    }
    else if(type == 3){
        DFS(x,y,dir);
        DFS(x,y,(dir+1)%4);     // 0-1(좌상), 1-2(상우), 2-3(우하), 3-0(하좌)
    }
    else if(type == 4){
        for(int i=0;i<4;i++){
            if(i==dir) continue;    //현재 dir인 곳만 뺴고
            DFS(x,y,i);     //3방향 탐색
        }
    }

    else if(type == 5){
        for(int i=0;i<4;i++){
            DFS(x,y,i); //4방향
        }
    }
}

void reset() {
    fill(&detect[0][0], &detect[0][0] + 10 * 10, false);
}
void check(){
    int cnt =0;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(!detect[i][j] && arr[i][j] == 0) cnt++; // 감지 못한 빈 공간이면 카운팅
        }
    }
    if(ans > cnt) ans = cnt;    //최소 값이라면 갱신
}
void print() {
    cout <<endl;
    /*
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
*/
    cout << endl;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cout << detect[i][j] << " ";
        }
        cout << endl;
    }

}

void permutation(vector<int> v) {	//모든 순열 뽑아낸다.
    if (v.size() == CCTV.size()) {	//CCTV 만큼 경우의 수 뽑아낸다.
        for(int i=0;i<v.size();i++){
            detection( CCTV[i].second.first, CCTV[i].second.second, CCTV[i].first,v[i]);    //x,y, type, 순열
        }
        //print(); DEBUG
        check();    //갱신
        reset();
        return;
    }

    for (int i = 0; i < 4; i++) {	//0 부터 3까지 direction 배열 뽑아낸다.
        v.push_back(i);
        permutation(v);
        v.pop_back();
    }
}




int main() {
    fastIO();

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> arr[i][j];
            if (1 <= arr[i][j] && arr[i][j] <= 5)
                CCTV.push_back({ arr[i][j],{ i,j } });	//CCTV면 push back
        }
    }
    vector<int> v;
    permutation(v);	//CCTV 개수만큼 경우의 수 뽑아낸다.

    cout << ans << '\n';

    return 0;
}