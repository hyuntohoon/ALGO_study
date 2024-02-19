//
// Created by newbi on 2024-02-13.
//
#include<iostream>
#include <vector>
#include <algorithm>

#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'

using namespace std;
int N,M,K;
vector<int> tree [12][12];  //좌표마다 들어있는 나무의 나이 표현
const int dx[] ={0,0,1,-1,1,1,-1,-1};
const int dy[] = {1,-1,0,0,1,-1,1,-1};
int A[12][12];
int ground[12][12];
vector<pair<int,int>> survive; //산 나무
void fastIO(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

void init(){
    For(i,1,N+1){
        For(j,1,N+1){
            ground[i][j] = 5;
        }
    }
}
bool out(int x,int y){
    return x <1 || x >N || y <1 || y >N;
}

void fallSummer(){
    For(i,1,N+1){
        For(j,1,N+1){
            if(tree[i][j].size()){//좌표에 나무가 있다면
                vector<int> survive;
                vector<int> dead;
                sort(tree[i][j].begin(),tree[i][j].end());  //정렬
                for(auto t : tree[i][j]){
                    if(ground[i][j]-t >= 0){    //양분을 먹을 수 있다면
                        ground[i][j]-=t;
                        survive.push_back(t+1); //살아남은 나무 추가
                    }
                    else{
                        dead.push_back(t);
                    }
                }
                for(int energy : dead){ //죽은 나무 /2 를 양분에 추가
                    ground[i][j] += energy/2;
                }
                tree[i][j].clear(); //초기화
                if(survive.size()){
                    /*
                    for(auto elem : survive){
                        tree[i][j].push_back(elem);
                    }
                     */
                    tree[i][j] = survive;
                }
            }
        }
    }
}

void spring(){
    For(i,1,N+1){
        For(j,1,N+1){
            if(tree[i][j].size()){
                for(int t : tree[i][j]){
                    if(t %5 ==0){
                        For(a,0,8){
                            int qx = i +dx[a];
                            int qy = j +dy[a];
                            if(out(qx,qy)) continue;
                            tree[qx][qy].push_back(1);  //나이가 1인 나무 번식

                        }
                    }
                }

            }
        }
    }
}

void winter(){
    For(i,1,N+1){
        For(j,1,N+1){
            ground[i][j] += A[i][j];    //S2D2가 양분 추가
        }
    }
}
int count(){
    int sm =0;
    For(i,1,N+1){
        For(j,1,N+1){
            if(tree[i][j].size()) sm += tree[i][j].size();
        }
    }
    return sm;
}

void print(){
    For(i,1,N+1){
        For(j,1,N+1){
            cout << tree[i][j].size()<<" ";
        }
        cout <<endl;
    }
    cout <<endl;

    For(i,1,N+1){
        For(j,1,N+1){
            cout << ground[i][j]<<" ";
        }
        cout <<endl;
    }
    cout <<endl;
}

void solve(){
    while(K--){
        //print();
        fallSummer();
        spring();
        winter();
    }
    //print();
    cout << count() << endl;
}

int main(){
    fastIO();
    cin >> N >> M >> K;

    init();

    For(i,1,N+1){
        For(j,1,N+1){
            cin >> A[i][j];
        }
    }
    int x,y,z;
    For(i,0,M){
        cin >> x >> y >> z;
        tree[x][y].push_back(z);
    }

    solve();

    return 0;
}