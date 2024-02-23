//
// Created by newbi on 2024-02-23.
//
#include <iostream>
#include <vector>
using namespace std;
int arr [24][24];
int cmd[1004];    //  1: 동, 2: 서, 3: 북, 4: 남
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};

vector<int> dice(6);    //0: 윗면, 1: 아랫면, 2: 동, 3: 서, 4: 북, 5: 남
int N,M,K;

void fastIO(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
bool out(int x, int y){
    return (x < 0 || x >= N || y < 0 || y >= M);
}
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
int main(){
    int x,y;
    fastIO();

    cin >> N >> M >> x >> y >>K;
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            cin >> arr[i][j];
        }
    }
    for(int i=0;i<K;i++){
        cin >> cmd[i];
    }

    for(int i=0;i<K;i++){
        int qx = x + dx[cmd[i]-1];
        int qy = y + dy[cmd[i]-1];

        if(out(qx,qy)) continue;
        if(cmd[i] == 1){    //동
            rollEast();
        }
        else if(cmd[i]==2){ //서
            rollWest();
        }
        else if(cmd[i]==3){ //북
            rollNorth();
        }
        else if(cmd[i]==4){ //남
            rollSouth();
        }

        if(arr[qx][qy] == 0){   //바닥이 0이라면
            arr[qx][qy] = dice[1];
        }
        else{   //0이 아니라면
            dice[1]= arr[qx][qy];
            arr[qx][qy] = 0;
        }
        x = qx;
        y = qy;
        cout << dice[0] <<'\n';
    }

    return 0;
}