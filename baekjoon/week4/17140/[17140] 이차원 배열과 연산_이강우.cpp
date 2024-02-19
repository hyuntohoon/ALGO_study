//
// Created by newbi on 2024-02-19.
//
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'

using namespace std;
vector<vector<int>> vec(3, vector<int>());
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
int R,C,K ;
int row_size;
int col_size;
int cnt[101];
int arr[101][101];
bool custom(int a, int b) { //커스텀 정렬
    if (cnt[a] == cnt[b]) {
        return a < b;
    }
    else {
        return cnt[a] < cnt[b];
    }
}

void opR() {	//R연산
    int mx =0;
    For(i,1,row_size+1){
        vector<int> temp;
        For(j,1,col_size+1){
            if(arr[i][j] == 0) continue;
            cnt[arr[i][j]]++;   //카운트 센다
            temp.push_back(arr[i][j]);   //0나오기 전까지 모든 값을 담는다.
            arr[i][j] =0;   //방문 한 자리 0으로
        }

        sort(temp.begin(),temp.end(), custom);
        temp.erase(unique(temp.begin(),temp.end()),temp.end()); //중복된 값 제거

        vector<int> ans;
        for(auto elem : temp){
            ans.push_back(elem);
            ans.push_back(cnt[elem]);
        }
        if(mx < ans.size()) mx = ans.size();    //최대 값 갱신
        if(ans.size() > 100){
            mx =100;
            For(j, 0, mx) {
                arr[i][j + 1] = ans[j];
            }

        }
        else {
            For(j, 0, ans.size()) {
                arr[i][j + 1] = ans[j];
            }
        }
        memset(cnt,0,sizeof(cnt));
    }
    col_size = mx;  //갱신
}

void opC() {
    int mx =0;
    For(i,1,col_size+1){
        vector<int> temp;
        For(j,1,row_size+1){
            if(arr[j][i] == 0) continue;
            cnt[arr[j][i]]++;   //카운트 센다
            temp.push_back(arr[j][i]);   //0나오기 전까지 모든 값을 담는다.
            arr[j][i] =0;   //방문 한 자리 0으로
        }

        sort(temp.begin(),temp.end(), custom);
        temp.erase(unique(temp.begin(),temp.end()),temp.end()); //중복된 값 제거

        vector<int> ans;
        for(auto elem : temp){
            ans.push_back(elem);
            ans.push_back(cnt[elem]);
        }
        if(mx < ans.size()) mx = ans.size();    //최대 값 갱신
        if(ans.size() > 100){
            mx =100;
            For(j, 0, mx) {
                arr[j + 1][i] = ans[j];
            }

        }
        else {
            For(j, 0, ans.size()) {
                arr[j + 1][i] = ans[j];
            }
        }
        memset(cnt,0,sizeof(cnt));
    }
    row_size = mx;  //갱신
}
bool check(){
    return arr[R][C] == K;
}
void print(){
    For(i,1,row_size+1){
        For(j,1,col_size+1){
            cout << arr[i][j] <<" ";
        }
        cout << endl;
    }
}

int main() {
    fastIO();
    cin >> R >> C >> K;
    For(i, 1, 4) {
        For(j, 1, 4) {
            cin >> arr[i][j];
        }
    }
    row_size = 3;
    col_size = 3;
    int T=0;
    bool found = false;
    while(T <=100){
        if(check()){
            found =true;
            break;
        }
        if(row_size>= col_size){
            opR();
        }
        else{
            opC();
        }
        //print();
        //cout <<endl;
        T++;
    }

    if(found){
        cout << T <<endl;
    }
    else{
        cout << -1 <<endl;
    }


    return 0;
}