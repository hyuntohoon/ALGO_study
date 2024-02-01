#include <bits/stdc++.h>
using namespace std;
int n;
int t[16];
int p[16];
int mx;
int tmp;

void dfs(int st) {

    mx = max(mx, tmp);

    for(int i=st; i<=n; i++) {
        int next = i + t[i];
        if(next > n+1)  continue;
        tmp += p[i];
        dfs( next);
        tmp -= p[i];
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> p[i];
    }
    dfs(1);
    cout << mx << '\n';
}