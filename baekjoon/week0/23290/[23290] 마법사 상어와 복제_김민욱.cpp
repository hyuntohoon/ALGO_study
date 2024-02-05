#include <bits/stdc++.h>
using namespace std;
vector<int> board[5][5];
vector<int> board_copy[5][5];
int dx[] = { 0, -1, -1, 0, 1, 1, 1, 0, -1 };
int dy[] = { 0, 0, -1,-1, -1, 0, 1, 1, 1 };
int dy2[] = {0, -1, 0, 1, 0};
int dx2[] = {0, 0, -1, 0, 1};
bool sm[5][5][101];
bool vis[5][5];
int m, s, sx, sy;
vector<pair<pair<int, int>, int>> best;
vector<pair<pair<int, int>, int>> tmp;
int sum;
int mx;

bool isValid(int x, int y, int dir, int cnt) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    if (ny < 1 || ny > 4 || nx < 1 || nx > 4)    return false;
    if (sm[nx][ny][cnt]) return false;
    return true;
}

void move(int i, int j, int n, int dir) {
    board[i][j].erase(board[i][j].begin()+n, board[i][j].begin()+n+1);
    int nx = i + dx[dir];
    int ny = j + dy[dir];
    board[nx][ny].push_back(dir);
}

void dfs(int k, int x, int y) {
    if(k == 3) {
        if(mx == sum) {
            if (!best.empty()) {
                int t = 0;
                int b = 0;
                for (int i = 0; i < 3; i++) {
                    t += (int) (tmp[i].second * pow(10, 2 - i));
                    b += (int) (best[i].second * pow(10, 2 - i));
                }
                if (t < b) {
                    copy(tmp.begin(), tmp.end(), best.begin());
                }
            }
        } else if(mx < sum) {
            if(!best.empty()) {
                copy(tmp.begin(), tmp.end(), best.begin());
            } else {
                for (const auto &item: tmp) {
                    best.push_back(item);
                }
            }
            mx = sum;
        }
        return;
    }

    for(int dir=1; dir<=4; dir++) {
        int nx = x + dx2[dir];
        int ny = y + dy2[dir];
        if (ny < 1 || ny > 4 || nx < 1 || nx > 4)    continue;
        if(vis[nx][ny]) continue;
        vis[nx][ny] = true;
        sum += board[nx][ny].size();
        tmp.push_back({{nx, ny}, dir});
        dfs(k+1, nx, ny);
        tmp.pop_back();
        vis[nx][ny] = false;
        sum -= board[nx][ny].size();
    }
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    // 둘 이상 물고기가 같은 칸에 있을 수 있음
    // 마법사 상어와 물고기가 같은 칸에 있을 수 있음
    // 복제 마법 시전
    // 모든 물고기가 한 칸 이동. 상어가 있는 칸, 물고기 냄새가 있는 칸, 범위 넘어가는 칸 이동X
    // 각 물고기는 자신이 가지고 있는 이동 방향이 이동할 수 있는 칸을 향할 때까지 방향을 45도 반시계 회전

    // 1. 각 좌표마다 포함되는 물고기 방향을 벡터에 담는다.
    // 2. 이동 시키기전 물고기의 상태를 저장한다.
    // 3. 4x4를 순회하면서 물고기를 가능한 방향으로 이동시킨다.
    // 4. 3칸 이동하여 제외할 수 있는 물고기를 최대로 하는 방향을 찾는다.
    // 5. 제외된 물고기를 제거한다.
    // 6. 이동 시키기 전 상태의 물고기를 복제한다.
    // 7. S번 반복한다.
    cin >> m >> s;
    for (int i = 0; i < m; i++) {
        int x, y, d;
        cin >> x >> y >> d;
        board[x][y].push_back(d);
    }
    cin >> sx >> sy;
    for (int i = 0; i < s; i++) {
        // 이동 시키기 전 물고기의 상태를 저장
        for (int k = 1; k <= 4; k++) {
            for (int l = 1; l <= 4; l++) {
                for (int n = 0; n < board[k][l].size(); n++) {
                    board_copy[k][l].push_back(board[k][l][n]);
                }
            }
        }

        // 4x4를 순회하면서 물고기를 가능한 방향으로 이동시킴
        for (int k = 1; k <= 4; k++) {
            for (int l = 1; l <= 4; l++) {
                for (int n = 0; n < board[k][l].size(); n++) {
                    for (int dir = 0; dir < 8; dir++) {
                        int direction = (board[k][l][n] + dir) % 8;
                        if (isValid(k, l, direction, i)) {
                            move(k, l, n, direction);
                            break;
                        }
                    }
                }
            }
        }

        // 상어 3칸 이동시키고, 이동경로의 물고기 제거
        dfs(0, sx, sy);
        for(int j=0; j<3; j++) {
            cout << sx << sy << '\n';
            sx += dx2[best[j].second];
            sy += dy2[best[j].second];
//            if(!board[sx][sy].empty()) {
//                sm[sx][sy][i] = true;
//                board[sx][sy].clear();
//            }
        }

        // 이동 시키기 전 상태의 물고기를 복제한다.
        for (int k = 1; k <= 4; k++) {
            for (int l = 1; l <= 4; l++) {
                for (int n = 0; n < board_copy[k][l].size(); n++) {
                    board[k][l].push_back(board_copy[k][l][n]);
                }
            }
        }

        if(i >= 2) {
            for(int k=1; k<=4; k++) {
                for(int l=1; l<=4; l++) {
                    sm[k][l][i-2] = false;
                }
            }
        }
    }
    int ans = 0;
    for(int i=1; i<=4; i++) {
        for(int j=1; j<=4; j++) {
            cout << i << ' ' << j << ": ";
            for(int n=0; n<board[i][j].size(); n++) {
                cout << board[i][j][n] << ' ';
            }
            cout << '\n';
            ans += board[i][j].size();
        }
    }
    cout << ans << '\n';
}