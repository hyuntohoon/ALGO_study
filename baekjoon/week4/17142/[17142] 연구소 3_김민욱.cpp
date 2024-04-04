#include <bits/stdc++.h>
using namespace std;

int n, m;
int board[55][55];
int boardCpy[55][55];
int mn = INT_MAX;
int tmp;
vector<pair<int, int>> virus;
vector<pair<int, int>> candidate;
bool vis[55][55];
int dy[] = {-1, 0, 1, 0};
int dx[] = {0 ,-1, 0, 1};
int emptyPlace;
int effectPlace;

bool bfs() {

    queue<pair<pair<int, int>, int>> q;
    for(int i=0; i<virus.size(); i++) {
        auto vrs = virus[i];
        q.push({vrs, 0});
        vis[vrs.first][vrs.second] = true;
    }

    int time = 0;
    while(!q.empty()) {
        auto cur = q.front();
        q.pop();

        if(effectPlace == emptyPlace) {
            tmp = max(tmp, time);
            return true;
        }

        for(int dir=0; dir<4; dir++) {
            int ny = cur.first.first + dy[dir];
            int nx = cur.first.second + dx[dir];
            int dist = cur.second;
            if(ny < 0 || ny >= n || nx < 0 || nx >= n) continue;
            if(vis[ny][nx] || board[ny][nx] == 1) continue;
            if(board[ny][nx] == 0) {
                effectPlace++;
                time = dist+1;
            }
            vis[ny][nx] = true;
            q.push({{ny, nx}, dist+1});
        }
    }

    return false;

//    cout << "tmp: " << tmp << '\n';
//    for(int i=0; i<n; i++) {
//        for(int j=0; j<n; j++) {
//            cout << board[i][j] << ' ';
//        }
//        cout << '\n';
//    }
//    cout << '\n';
}

// k개 바이러스를 결정
void dfs(int k, int st) {

    if(k == m) {
        tmp = 0;
        effectPlace = 0;
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                board[i][j] = boardCpy[i][j];
            }
        }
        for(int i=0; i<n; i++) {
            fill(vis[i], vis[i]+n, false);
        }
        if(bfs()) {// virus를 퍼트려서 최소시간 찾기
            mn = min(mn, tmp);
        }
        return;
    }

    for(int i=st; i<candidate.size(); i++) {
        virus.push_back(candidate[i]);
        dfs(k+1, i+1);
        virus.pop_back();
    }

}

int main() {
    cin >> n >> m;
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cin >> board[i][j];
            boardCpy[i][j] = board[i][j];
            if(board[i][j] == 2) {
                candidate.push_back({i, j});
            } else if(board[i][j] == 0) {
                emptyPlace++;
            }
        }
    }

    // 1. backtracking 바이러스중 M개 선택
    // 2. M개 선택한 바이러스 위치에서 BFS해서 최소시간 찾기
    // 3. backtracking기저에서 최소시간 갱신
    dfs(0, 0);
    if(mn == INT_MAX) {
        cout << -1 << '\n';
        return 0;
    }
    cout << mn << '\n';
}