//
// Created by newbi on 2024-02-09.
//
#include <iostream>
#include <algorithm>
#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'

using namespace std;

int N;
int arr[21][21];
bool visited[21][21];
int first,second,third,fourth,fifth;
int ans = 1e9;
void fastIO(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

bool out(int x,int y){  //장외 처리
    return x < 1 || x >N || y < 1 || y > N;
}

void reset(){
    fill(&visited[0][0],&visited[0][0]+21*21,false);
    first =0;
    second =0;
    third = 0;
    fourth = 0;
    fifth = 0;
}
void makeBoundaries(int x,int y,int d1,int d2){
    visited[x][y] = true;   //원점 처리
    int rx = x;
    int ry = y;
    int lx = x;
    int ly = y;
    while(true){
        if(lx < x+d1){ //d1도달 전까지
            lx += 1;
            ly -= 1;
        }
        else{
            lx += 1;
            ly += 1;
        }

        if(rx < x+d2){ //d2도달 전까지
            rx += 1;
            ry += 1;
        }
        else{
            rx += 1;
            ry -= 1;
        }

        for(int col = ly;col <=ry;col++){   //ly와 ry사이 모든 영역 방문처리
            visited[lx][col] = true;
        }

        if(rx == lx && ry == ly) break; //만나면 break
    }

    For(i,1,N+1){
        For(j,1,N+1){
            if(visited[i][j]){
             fifth += arr[i][j];
            }
            else if(i < x+d1 && j<= y) first+= arr[i][j];
            else if(i<= x+d2 && j > y) second+= arr[i][j];
            else if(x+d1 <= i && j < y-d1+d2) third+= arr[i][j];
            else if(x+d2< i && y-d1+d2 <= j) fourth+= arr[i][j];

        }
    }
    /*
    cout << "1 :" << first << endl;
    cout << "2 :" << second << endl;
    cout << "3 :" << third << endl;
    cout << "4 :" << fourth << endl;
    cout << "5 :" << fifth << endl;
     */
    int mx = max({first,second,third,fourth,fifth});
    int mn = min({first,second,third,fourth,fifth});
    if(ans > mx-mn) ans = mx-mn;    //최소 값이라면 갱신
    reset();
}

void input(){
    For(i,1,N+1){
        For(j,1,N+1){
            cin >> arr[i][j];
        }
    }
}

void print(){
    For(i,1,N+1){
        For(j,1,N+1){
            if(visited[i][j]) cout << "O ";
            else cout <<"X ";
        }
        cout << endl;
    }
}
void find_way(int x,int y){
    int lcnt =0,rcnt =0;
    int lx =x, ly =y, rx =x, ry = y;
    while(true){
        lx += 1;
        ly -= 1;
        if(out(lx,ly)) break;
        lcnt++;
    }
    while(true){
        rx += 1;
        ry += 1;
        if(out(rx,ry)) break;
        rcnt++;
    }
    for(int i= 1;i<=lcnt;i++){
        for(int j=1;j<=rcnt;j++){
            makeBoundaries(x,y,i,j);
        }
    }

}

void solve(){
    For(i,1,N+1){
        For(j,1,N+1){
            find_way(i,j);
        }
    }
}

int main(){
    fastIO();
    cin >> N;
    input();
    solve();
    //print();
    cout << ans << endl;
    return 0;
}