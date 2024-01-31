#include <bits/stdc++.h>
using namespace std;
int n;
int t[16];
int p[16];
vector<int> vec;
int mx;

void dfs(int k, int st) {

    if (k != 0) {
        for (int i = 0; i < vec.size() - 1; i++) {
            if (vec[i] + t[vec[i]] > vec[i + 1]) { // 가능한 경우인지 판단
                return;
            }
        }
        if (vec[vec.size() - 1] + t[vec[vec.size() - 1]] > n+1) { // 마지막 경우 처리
            return;
        }
    }
    int sum = 0;
    for (auto v : vec) { // 가능한 경우이면 최대 갱신
        sum += p[v];
    }
    mx = max(mx, sum);

    for (int i = st; i <= n; i++) { // 조합 모든 경우의 수 구하기
        vec.push_back(i);
        dfs(k + 1, i + 1);
        vec.pop_back();
    }
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> p[i];
    }
    dfs(0, 0);
    cout << mx << '\n';
}