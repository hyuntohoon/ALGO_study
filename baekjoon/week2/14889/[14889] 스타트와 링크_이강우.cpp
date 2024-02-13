//
// Created by newbi on 2024-02-13.
//

#include<iostream>
#include<vector>
#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'

using namespace std;
int N,ans= 1e9;
int arr[21][21];
void fastIO(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

void combi(int start,vector<int> v){
    if(v.size() == N/2){
        vector<int> _link;
        For(i,1,N+1){
            bool found =false;
            for(auto elem : v){
                if(elem == i){
                    found = true;
                    break;
                }
            }
            if(!found) _link.push_back(i);
        }
        int ssum =0;
        for(int i=0;i<v.size();i++){
            for(int j=i+1;j<v.size();j++){
                ssum += arr[v[i]][v[j]];
                ssum += arr[v[j]][v[i]];
            }
        }
        int lsum =0;
        for(int i=0;i<_link.size();i++){
            for(int j=i+1;j<_link.size();j++){
                lsum += arr[_link[i]][_link[j]];
                lsum += arr[_link[j]][_link[i]];
            }
        }
        if(ans > abs(ssum-lsum)) ans = abs(ssum-lsum);
        return;
    }
    for(int i= start;i<=N;i++){
        v.push_back(i);
        combi(i+1,v);
        v.pop_back();
    }
}

int main(){
    fastIO();
    cin >> N;
    For(i,1,N+1){
        For(j,1,N+1){
            cin >> arr[i][j];
        }
    }
    vector<int>v;
    combi(1,v);

    cout << ans << endl;

    return 0;
}