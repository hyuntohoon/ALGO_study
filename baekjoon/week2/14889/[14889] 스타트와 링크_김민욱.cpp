#include <bits/stdc++.h>
using namespace std;
int n;
int s[21][21];
bool startTeam[21];
int mn = 10e8;

// k번째 사람의 팀을 결정한다.
void dfs(int k, int st) {
    if(k == n/2) {
        int cap1 = 0;
        int cap2 = 0;
        for(int i=1; i<=n; i++) {
            for(int j=i+1; j<=n; j++) {
                if(startTeam[i] && startTeam[j]) {
                    cap1 += (s[i][j] + s[j][i]);
                } else if(!startTeam[i] && !startTeam[j]) {
                    cap2 += (s[i][j] + s[j][i]);
                }
            }
        }
        mn = min(mn, abs(cap1 - cap2));
        return;
    }

    for(int i=st; i<=n; i++) {
        startTeam[i] = true;
        dfs(k+1, i+1);
        startTeam[i] = false;
    }
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> s[i][j];
        }
    }
    dfs(0, 1);
    cout << mn << '\n';
}