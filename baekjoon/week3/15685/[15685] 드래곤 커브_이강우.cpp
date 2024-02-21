//
// Created by newbi on 2024-02-21.
//
#include <iostream>
#include <vector>
#define For(i,a,b) for(int i =a;i<b;i++)
#define endl '\n'

using namespace std;

int x,y,d,g;
bool arr[101][101];
int dy[] = {0,-1,0,1};  //우상좌하
int dx[] = {1,0,-1,0};
int N;

void fastIO(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

void print(){
    For(i,0,10){
        For(j,0,10){
            cout << arr[i][j];
        }
        cout <<endl;
    }
    cout <<endl;
}

void dragonCurve(int y,int x, vector<int> v,int level,int gen){
    if(level == gen+1){
        return;
    }


    if(level == 0){
        y+= dy[v[0]];
        x+= dx[v[0]];
        arr[y][x] = true;
    }
    else {
        for (int i = v.size() - 1; i >= 0; i--) {
            int rotateDir = (v[i] + 1) % 4;
            y += dy[rotateDir];    //90도 회전한 곳 찾고
            x += dx[rotateDir];
            arr[y][x] = true;
            v.push_back(rotateDir); //내 상태 기억
        }
    }
    dragonCurve(y,x,v,level+1,gen);
}

int count(){
    int cnt =0;
    For(i,0,100){
        For(j,0,100){
            if(arr[i][j] && arr[i+1][j] && arr[i][j+1] && arr[i+1][j+1]) cnt++;
        }
    }
    return cnt;
}

int main(){

    fastIO();

    cin >> N;
    For(i,0,N){
        vector<int>v;
        cin >> x >> y >> d >> g;
        v.push_back(d);
        arr[y][x] = true;
        dragonCurve(y,x,v,0,g);
        //print();
    }

    cout << count() <<endl;

    return 0;
}