#include <bits/stdc++.h>
using namespace std;
deque<int> gear[5];
bool isRotated[5];

// 하나의 톱니를 회전
void dfs(int num, int dir) {
    isRotated[num] = true;
    bool doNext = false;
    bool doPrev = false;
    if (num + 1 <= 4 && gear[num][2] != gear[num + 1][6] && !isRotated[num + 1]) {
        doNext = true;
    }
    if (num - 1 >= 1 && gear[num][6] != gear[num - 1][2] && !isRotated[num - 1]) {
        doPrev = true;
    }
    if (dir == -1) { // 반시계
        int front = gear[num].front();
        gear[num].pop_front();
        gear[num].push_back(front);
    }
    else { // 시계
        int back = gear[num].back();
        gear[num].pop_back();
        gear[num].push_front(back);
    }

    if (doPrev) {
        dfs(num - 1, -dir);
    }

    if (doNext) {
        dfs(num + 1, -dir);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    for (int i = 1; i <= 4; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < s.length(); j++) {
            gear[i].push_back(s[j] - '0');
        }
    }
    int k;
    cin >> k;
    while (k--) {
        int num, dir;
        cin >> num >> dir;
        fill(isRotated + 1, isRotated + 5, false);
        dfs(num, dir);
    }
    int ans = 0;
    for (int i = 1; i <= 4; i++) {
        ans += (int)(gear[i][0] == 0 ? 0 : 1 << (i - 1));
    }
    cout << ans << '\n';
}