#include <bits/stdc++.h>
using namespace std;
int board[5][5];
map<int, pair<pair<int, int>, int> > m;
int dy[] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dx[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int mx;
int numSum;
int sy = 1;
int sx = 1;
int sDir;


// 물고기 움직임 -> 상어 이동의 한 사이클을 결정
void dfs() {

    mx = max(mx, numSum);

    for(auto &item : m) { // 물고기 이동
        int dir = item.second.second;
        int y = item.second.first.first;
        int x = item.second.first.second;
        int ny = y;
        int nx = x;
        bool isMove = false;
        for(int d=0; d<8; d++) {
            ny = y + dy[dir];
            nx = x + dx[dir];
            if(ny < 1 || ny > 4 || nx < 1 || nx > 4 || board[ny][nx] == -1) {
                dir = (dir+1)%8;
                if(dir == 0)    dir = 8;
                continue;
            }
            isMove = true;
            break;
        }
        if(isMove) {
            m[item.first].second = dir;
            auto tmp = m[item.first].first; // 좌표 변경
            m[item.first].first = m[board[ny][nx]].first;
            m[board[ny][nx]].first = tmp;
            int num = board[y][x];
            board[y][x] = board[ny][nx];
            board[ny][nx] = num;
        }
    }

    for(int i=1; i<=4; i++) {
        for(int j=1; j<=4; j++) {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';

    if(sy == 1 && sx == 1) {
        for(int depth=1; depth<=3; depth++) { // 상어 이동
            int nsy = sy + depth*dy[sDir];
            int nsx = sx + depth*dx[sDir];
            if(nsy < 1 || nsy > 4 || nsx < 1 || nsx > 4 || board[nsy][nsx] == 0) continue;

            int sDirTmp = sDir;

            // 상어 이동
            int tmpNum = board[nsy][nsx];
            numSum += board[nsy][nsx];
            sDir = m[board[nsy][nsx]].second;
            auto tmp = m[board[nsy][nsx]];
            m.erase(board[nsy][nsx]);
            board[sy][sx] = 0;
            board[nsy][nsx] = -1;
            sy = nsy;
            sx = nsx;

            dfs();

            // 원복
            sy = 1;
            sx = 1;
            board[sy][sx] = -1;
            board[nsy][nsx] = tmpNum;
            sDir = sDirTmp;
            numSum -= board[nsy][nsx];
            m[board[nsy][nsx]] = tmp;
        }
    } else {
        for(int depth=1; depth<=3; depth++) { // 상어 이동
            int nsy = sy + depth*dy[sDir];
            int nsx = sx + depth*dx[sDir];
            if(nsy < 1 || nsy > 4 || nsx < 1 || nsx > 4 || board[nsy][nsx] == 0) continue;

            // 바꾸기 전 백업
            int tmpKey = board[sy][sx]; // -1
            int sDirTmp = sDir; // 6
            auto tmpValue = m[board[sy][sx]]; // m[-1]

            // 상어 이동
            numSum += board[nsy][nsx];
            sDir = m[tmpKey].second;
            m.erase(board[nsy][nsx]);
            board[sy][sx] = 0;
            board[nsy][nsx] = -1;
            int tmpSy = sy;
            int tmpSx = sx;
            sy = nsy;
            sx = nsx;

            dfs();

            // 원복
            sy = tmpSy;
            sx = tmpSx;
            board[sy][sx] = -1;
            board[nsy][nsx] = tmpKey;
            sDir = sDirTmp;
            m[tmpKey] = tmpValue;
            numSum -= board[nsy][nsx];
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // 1. 상어를 (0, 0)에 위치 시키고 방향을 해당 자리의 물고기 방향과 동일하게 설정
    // 2. map을 이용하여 1번부터 16번까지 물고기의 좌표와 방향을 저장
    // 3. map을 순회하며 물고기 이동 및 board 업데이트
    // 4. 상어가 이동할 수 있는 모든 경우를 탐색하고 이동할 수 없을 때 까지 반복
    for(int i=1; i<=4; i++) {
        for(int j=1; j<=4; j++) {
            int a, b;
            cin >> a >> b;
            board[i][j] = a;
            m[a] = make_pair(make_pair(i, j), b);
        }
    }
    mx = board[1][1];
    numSum += board[1][1];
    sDir = m[board[1][1]].second;
    m.erase(board[1][1]);
    board[1][1] = -1;
    dfs();
    cout << mx << '\n';
}
// 실패한 풀이