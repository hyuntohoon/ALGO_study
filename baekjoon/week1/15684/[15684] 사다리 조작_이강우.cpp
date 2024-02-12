//
// Created by newbi on 2024-02-11.
//
#include <iostream>
#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n';
using namespace std;

void fastIO(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

bool connect[33][33];    //연결된 요소, a번 점선에서 b <-> b+1 연결
int N,M,H;  //세로선, 가로선, 세로선 - 가로선 놓을 수 있는 위치
int a,b;    //a번 점선에서 b,b+1에 연결
int ans = 1e9; //최대 값

bool check(){   //사다리가 제대로 가는지 체크
    int _start;
    For(i,1,N+1){
        _start = i;
        For(j,1,H+1){
            if(connect[j][_start]) _start = _start+1;  //오른쪽 사다리가 있다면 오른쪽으로 이동
            else if(connect[j][_start-1]) _start = _start-1;   //왼쪽 사다리로 이동
        }
        if(_start != i) return false;   //결과가 맞지 않는다면
    }
    return true;
}
void DFS(int cnt,int row){

    if(cnt > 3){
        return;
    }

    if(check()){
        if(ans > cnt) ans = cnt;
        return;
    }


    for(int i = row;i<= H;i++){
        for(int j = 1; j< N;j++){
            if(connect[i][j]) continue; //이미 초기부터 연결되어있었다면 SKIP
            if(connect[i][j-1]||connect[i][j+1]) continue;   //이웃 가로선이 사다리를 가지고 있다면 SKIP

            connect[i][j] = true;   //사다리를 연결하고
            //cout << i <<" : "<< j << "ladder connected"<<endl;
            DFS(cnt+1,i);
            //cout << i <<" : "<< j << "ladder terminated"<<endl;
            connect[i][j] = false;  //다음 경우를 위해 원복

        }
    }
}

int main(){

    fastIO();

    cin >> N >> M >> H;

    For(i,0,M){
        cin >> a >> b;
        connect[a][b] = true;
    }
    DFS(0,1);

    if(ans == 1e9){
        ans = -1;
    }
    cout << ans << endl;

    return 0;
}