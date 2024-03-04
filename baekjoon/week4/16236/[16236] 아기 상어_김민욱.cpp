#include <bits/stdc++.h>
using namespace std;

class Shark {
public:
    int y, x, sz, cnt;
    Shark() {}
    Shark(int y, int x, int sz) {
        this->y = y;
        this->x = x;
        this->sz = sz;
        this->cnt = 0;
    }
};

class Fish {
public:
    int y, x, sz, dist;
    Fish(int y, int x, int sz, int dist) {
        this->y = y;
        this->x = x;
        this->sz = sz;
        this->dist = dist;
    }

    bool operator < (const Fish& o) const {
        if (this->dist == o.dist) { // 거리가 같으면
            if (this->y == o.y) { // y좌표가 같으면
                return this->x < o.x;  // 가장 왼쪽
            }
            return this->y < o.y;
        }
        return this->dist < o.dist;
    }
};

int board[21][21];
vector<Fish> fishes;
int dy[] = { -1, 0, 1, 0 };
int dx[] = { 0, -1, 0, 1 };
bool vis[21][21];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // 1. 현재 상어 위치 기준 bfs를 통해 먹을 수 있는 물고기 개수와 거리를 확인
    // 벡터에 넣고 거리, 가장 위쪽, 가장 왼쪽 순으로 정렬
    // 2. 먹을 수 있는 물고기가 한 마리면 먹으로 가기
    // 3. 먹을 수 있는 물고기가 두 마리 이상이면 거리가 가장 가까운, 가장 위쪽, 가장 왼쪽 물고기 먹으러 가기

    int n;
    cin >> n;
    Shark shk;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
            if (board[i][j] == 9) {
                shk = Shark(i, j, 2);
            }
        }
    }

    int t = 0;
    while (true) {

//        cout << "shk: " << shk.y << ' ' << shk.x << '\n';
        for (int i = 0; i < n; i++)
            fill(vis[i], vis[i] + n, false);
        fishes.clear();

        queue<pair<pair<int, int>, int>> q;
        q.push({{ shk.y, shk.x }, 0});
        vis[shk.y][shk.x] = true;
        board[shk.y][shk.x] = 0;
        while (!q.empty()) {
            auto cur = q.front();
            //cout << cur.first.first << ' ' << cur.first.second << ' ' << cur.second << '\n';
            q.pop();
            for (int dir = 0; dir < 4; dir++) {
                int ny = cur.first.first + dy[dir];
                int nx = cur.first.second + dx[dir];
                if (ny < 0 || ny >= n || nx < 0 || nx >= n)	continue;
                if (board[ny][nx] > shk.sz || vis[ny][nx])	continue;
                if (board[ny][nx] >= 1 && board[ny][nx] <= 6 && board[ny][nx] < shk.sz) {
                    fishes.push_back(Fish(ny, nx, board[ny][nx], cur.second+1));
                }
                q.push({ {ny, nx}, cur.second + 1 });
                vis[ny][nx] = true;
            }

        }

        if (fishes.empty()) {
            break;
        }

        sort(fishes.begin(), fishes.end());

//        for (auto & fish : fishes) {
//            cout << fish.dist << ' ' << fish.y << ' ' << fish.x << '\n';
//        }

        shk.y = fishes[0].y;
        shk.x = fishes[0].x;
        board[shk.y][shk.x] = 0;
        t += fishes[0].dist;
        shk.cnt++;
        if (shk.cnt == shk.sz) {
            shk.sz++;
            shk.cnt = 0;
        }
    }
    cout << t << '\n';
}