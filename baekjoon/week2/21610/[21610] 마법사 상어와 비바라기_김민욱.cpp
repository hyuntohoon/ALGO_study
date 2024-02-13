#include <bits/stdc++.h>
using namespace std;

int n, m;
int board[51][51];
bool preClouds[51][51];
vector<pair<int, int>> clouds;
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // 1. 모든 구름을 di방향으로 si칸 이동
    // 2. 구름이 있는 칸의 바구니에 저장된 물의 양 1 증가
    // 3. 구름 모두 제거
    // 4. 2에서 물이 증가한 칸에서 대각선 방향으로 거리가 1인 칸에 물이 있는 바구니 수만큼 물의 양 증가
    // 5. 바구니에 저장된 물의 양이 2 이상인 모든 칸에 구름이 생성하고 물의 양 2 감소, 구름이 생기는 칸은 3에서 구름이 사라진 칸 X
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> board[i][j];
        }
    }
    clouds.emplace_back( n, 1 );
    clouds.emplace_back( n, 2 );
    clouds.emplace_back( n-1, 1 );
    clouds.emplace_back( n-1, 2 );

    while (m--) {
        int d, s;
        cin >> d >> s;
        for (int i=0; i<clouds.size(); i++) {
            s %= n;
            int ny = (clouds[i].first + s*dy[d-1] + n) % n;
            int nx = (clouds[i].second + s*dx[d-1] + n) % n;
            if (ny == 0)	ny = n;
            if (nx == 0)	nx = n;
//            clouds.erase(remove(clouds.begin(), clouds.end(), clouds[0]), clouds.end());
//            clouds.emplace_back(ny, nx);
            clouds[i] = {ny, nx};
            board[ny][nx]++;
            preClouds[ny][nx] = true;
        }
        for (auto& cloud : clouds) {
            int y = cloud.first;
            int x = cloud.second;
            int cnt = 0;
            for (int dir = 1; dir < 8; dir += 2) {
                int ny = y + dy[dir];
                int nx = x + dx[dir];
                if (ny < 1 || ny > n || nx < 1 || nx > n)	continue;
                if (board[ny][nx] != 0) {
                    cnt++;
                }
            }
            board[y][x] += cnt;
        }
        clouds.clear();
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (board[i][j] >= 2 && !preClouds[i][j]) {
                    clouds.emplace_back( i, j );
                    board[i][j] -= 2;
                }
            }
        }

        for (int i = 1; i <= n; i++)
            fill(preClouds[i], preClouds[i]+n+1, 0);

//        for (int i = 1; i <= n; i++) {
//            for (int j = 1; j <= n; j++) {
//                cout << board[i][j] << ' ';
//            }
//            cout << '\n';
//        }
//        cout << '\n';
    }

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ans += board[i][j];
        }
    }
    cout << ans << '\n';
}