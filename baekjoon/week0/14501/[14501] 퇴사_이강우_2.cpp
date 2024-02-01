//
// Created by newbi on 2024-02-01.
//
#include <iostream>

using namespace std;

int N,ans;

int T[18];
int P[18];
bool visited[18];
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

void solve(int start , int sm) {

    //cout <<"Start : " << start <<"  Sum : " << sm << endl;

    if (ans < sm) ans = sm;

    for (int idx = start + 1; idx <= N; idx++) {
        if (visited[idx]) continue;
        if (N < idx + T[idx] - 1) continue;	//상담 일 수가 N일을 초과해버리면 SKIP
        sm += P[idx];
        for (int i = T[idx] - 1; i >= 0; i--) {
            visited[idx + i] = true;	//방문처리해버린다
        }
        solve(idx, sm);
        sm -= P[idx];
        for (int i = T[idx] - 1; i >= 0; i--) {
            visited[idx + i] = false;	//원상 복귀
        }

    }
    return;

}



int main() {
    fastIO();
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> T[i] >> P[i];
    }

    solve(0, 0);

    cout << ans << '\n';


    return 0;
}