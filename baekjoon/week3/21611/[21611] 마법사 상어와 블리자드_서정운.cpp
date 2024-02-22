#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;

#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'
#define all(v) v.begin(), v.end()
#define rall(v) v.rbegin(), v.rend()
//constexpr inline auto nx = [](int x, int i) -> int {return "0121"[i] - '1' + x; };
//constexpr inline auto ny = [](int y, int i) -> int {return "1210"[i] - '1' + y; };
//constexpr inline auto outside = [](int x, int y, int R, int C) -> bool {return (min(x, y) < 0 || x >= R || y >= C); };
constexpr inline auto FAST = []() -> void {cin.tie(0)->sync_with_stdio(0); };


deque<int> q;
int board[55][55];

int N, M;

ll score = 0;

// 12시부터 반시계방향
int nx(int x, int i) {
    return "0121"[i] - '1' + x;
}

int ny(int y, int i) {
    return "1012"[i] - '1' + y;
}

bool outside(int x, int y, int R, int C) {
    return min(x, y) < 0 || x >= R || y >= C;
}

// 상하좌우에서 바꾸기
int dirconvert(int d) {
    if (d == 1) return 0;
    if (d == 2) return 2;
    if (d == 3) return 1;
    return 3;
}

vector<pair<int, int>> pos;

void init() {
    int x, y;
    x = y = N / 2;

    int dir = 3;
    For(i, 0, N + 1) {
        For(j, 0, i) {
            x = nx(x, dir); y = ny(y, dir);
            if (outside(x, y, N, N)) return;
            pos.push_back({ x,y });
        }
        dir = (dir + 1) % 4;
        For(j, 0, i) {
            x = nx(x, dir); y = ny(y, dir);
            if (outside(x, y, N, N)) return;
            pos.push_back({ x,y });
        }
        dir = (dir + 1) % 4;
    }
}

void remove(int d, int s) {
    int size = q.size();

    int cnt = 0;
    for (int i = 0; i < size; i++) {
        int now = q.front(); q.pop_front();
        auto p = pos[i];
        // 아직 덜 지웠다면, 
        if (cnt < s) {
            // 위, 아래
            if (d == 0 || d == 2) {
                // 상어 열일 때,
                if (p.second == N / 2) {
                    if (d == 0 && p.first < N / 2) {
                        cnt++; continue;
                    }
                    if (d == 2 && p.first > N / 2) {
                        cnt++; continue;
                    }
                }
            }
            // 좌, 우
            if (d == 1 || d == 3) {
                // 상어 행일 때,
                if (p.first == N / 2) {
                    if (d == 1 && p.second < N / 2) {
                        cnt++; continue;
                    }
                    if (d == 3 && p.second > N / 2) {
                        cnt++; continue;
                    }
                }
            }
        }
        q.push_back(now);
    }
}

void compress() {
    int target, cnt;
    target = -1, cnt = 0;
    deque<pair<int, int>> tmp, tmp2;
    while (q.size()) {
        int now = q.front(); q.pop_front();
        if (target != now) {
            if (target != -1) tmp.push_back({ target, cnt });
            target = now; cnt = 1;
        }
        else cnt++;
    }
    if (target != -1) tmp.push_back({ target, cnt });

    while (true) {
        bool flag = false;
        for (int t = tmp.size(); t--;) {
            auto now = tmp.front(); tmp.pop_front();
            if (now.second >= 4) {
                score += now.first * now.second;
                flag = true; continue;
            }
            if (tmp2.size() && tmp2.back().first == now.first) {
                tmp2.back().second += now.second;
            }
            else tmp2.push_back(now);
        }
        swap(tmp, tmp2);
        if (!flag) break;
    }

    while (tmp.size()) {
        q.push_back(tmp.front().second);
        q.push_back(tmp.front().first);
        tmp.pop_front();
        if (q.size() >= pos.size()) break;
    }

    while (q.size() > pos.size()) q.pop_back();

}

int main() {

    cin >> N >> M;

    For(i, 0, N) For(j, 0, N) cin >> board[i][j];

    init();

    for (auto p : pos) {
        if (board[p.first][p.second] == 0) break;
        q.push_back(board[p.first][p.second]);
    }

    For(i, 0, M) {
        int d, s; cin >> d >> s;
        remove(dirconvert(d), s);
        compress();

        //cout << "===DEBUG===" << endl;
        //for (int t = q.size(); t--;) {
        //    cout << q.front() << ' '; q.push_back(q.front()); q.pop_front();
        //}
        //cout << endl;
    }

    cout << score;

}
