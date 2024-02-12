#include <bits/stdc++.h>
using namespace std;

int n, m, k;
int board[21][21];
int dice[6] = {1, 6, 4, 3, 2, 5}; // 상 하 좌 우 앞 뒤
int tmp[6]; // 상 하 좌 우 앞 뒤
int dy[] = {0, 1, 0, -1}; // 동 남 서 북 (시계 방향)
int dx[] = {1, 0, -1, 0};
bool vis[21][21];

void changeDice(int dir) {
    switch (dir) {
        case 0: // 동쪽으로 굴러간 경우
            tmp[0] = dice[2]; // 좌 -> 상
            tmp[1] = dice[3]; // 우 -> 하
            tmp[2] = dice[1]; // 하 -> 좌
            tmp[3] = dice[0]; // 상 -> 우
            tmp[4] = dice[4]; // 앞
            tmp[5] = dice[5]; // 뒤
            break;
        case 1: // 남쪽으로 굴러간 경우
            tmp[0] = dice[4]; // 앞 -> 상
            tmp[1] = dice[5]; // 뒤 -> 하
            tmp[2] = dice[2]; // 좌
            tmp[3] = dice[3]; // 우
            tmp[4] = dice[1]; // 하 -> 앞
            tmp[5] = dice[0]; // 상 -> 뒤
            break;
        case 2: // 서쪽으로 굴러간 경우
            tmp[0] = dice[3]; // 우 -> 상
            tmp[1] = dice[2]; // 좌 -> 하
            tmp[2] = dice[0]; // 상 -> 좌
            tmp[3] = dice[1]; // 하 -> 우
            tmp[4] = dice[4]; // 앞
            tmp[5] = dice[5]; // 뒤
            break;
        case 3: // 북쪽으로 굴러간 경우
            tmp[0] = dice[5]; // 뒤 -> 상
            tmp[1] = dice[4]; // 앞 -> 하
            tmp[2] = dice[2]; // 좌
            tmp[3] = dice[3]; // 우
            tmp[4] = dice[0]; // 상 -> 앞
            tmp[5] = dice[1]; // 하 -> 뒤
            break;
    }
    copy(tmp, tmp+6, dice);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cin >> board[i][j];
        }
    }
    // 1. 주사위를 이동 방향으로 한 칸 이동 시킨다.
    // 2. 이동 방향에 따른 주사위 전개도를 변경한다.
    // 3. 주사위가 도착한 칸에서 연속해서 이동할 수 있는 칸 수를 구한다. (bfs)
    // 4. 도착한 칸에서 점수를 계산후 합산한다.
    // 5. 다음 이동 방향을 결정하고 k번 반복한다.

    int cy = 0, cx = 0;
    int dDir = 0;
    int ans = 0;
    queue<pair<int, int> > q;
    while(k--) {
        int y = cy + dy[dDir];
        int x = cx + dx[dDir];
        if(y < 0 || y >= n || x < 0 || x >= m) {
            dDir = (dDir+2) % 4;
            k++;
            continue;
        }

        changeDice(dDir);

        for(int i=0; i<21; i++)
            fill(vis[i], vis[i]+21, 0);

        int sum = 0;
        q.push(make_pair(y, x));
        vis[y][x] = true;
        while(!q.empty()) {
            auto cur = q.front();
            q.pop();
            sum++;
            for(int dir=0; dir<4; dir++) {
                int ny = cur.first + dy[dir];
                int nx = cur.second + dx[dir];
                if(ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
                if(vis[ny][nx] || board[y][x] != board[ny][nx]) continue;
                q.push(make_pair(ny, nx));
                vis[ny][nx] = true;
            }
        }
        ans += sum * board[y][x];
        if(board[y][x] < dice[1]) { // A > B
            dDir = (dDir + 1) % 4;
        } else if(board[y][x] > dice[1]) { // A < B
            dDir = (dDir - 1 + 4) % 4;
        }
        cy = y;
        cx = x;
    }
    cout << ans << '\n';
}