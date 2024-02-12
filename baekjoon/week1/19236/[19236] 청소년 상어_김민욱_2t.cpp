#include <bits/stdc++.h>
using namespace std;
int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1}; // 반시계 방향
int dx[] = {0, -1, -1, -1, 0, 1, 1, 1};
int tmp;
int mx;

void eat(int sy, int sx, int sDir, int srcBoard[4][4], map< int, pair<pair<int, int>, int> > srcFishes) {

    map< int, pair<pair<int, int>, int> > fishes;
    int board[4][4];

    copy(srcFishes.begin(), srcFishes.end(), inserter(fishes, fishes.end()));
    for(int i=0; i<4; i++)
        copy(srcBoard[i], srcBoard[i]+4, board[i]);

    mx = max(mx, tmp);

    // 1. 물고기 이동
    for(auto& fish : fishes) {
        int y = fish.second.first.first;
        int x = fish.second.first.second;
        int dir = fish.second.second-1;

        for(int d=0; d<8; d++) { // 가능한 방향 탐색
            int ny = y + dy[dir];
            int nx = x + dx[dir];
            if(ny < 0 || ny >= 4 || nx < 0 || nx >= 4 || board[ny][nx] == -1) { // 이동 가능하지 않으면 반시계로 방향 변경
                dir = (dir + 1) % 8;
                continue;
            }
            // 이동 가능하면 물고기 이동 후 빠져나감
            fishes[board[y][x]].second = dir+1; // 회전한 물고기 방향으로 변경
            if(board[ny][nx] != 0) { // 물고기가 있는 칸으로 이동할 경우 해당 물고기의 좌표 교환
                swap(fishes[board[ny][nx]].first, fishes[board[y][x]].first); // 방향은 그대로 두고 좌표만 변경
            } else { // 빈칸으로 이동할 경우 원래 있던 물고기의 좌표 변경
                fishes[board[y][x]].first = make_pair(ny, nx);
            }
            swap(board[ny][nx], board[y][x]); // board에서 물고기 위치 변경
            break;
        }
    }

    // 2. 상어 이동
    for(int dist=1; dist<=3; dist++) {
        int sny = sy + dist*dy[sDir];
        int snx = sx + dist*dx[sDir];
        if(sny < 0 || sny >= 4 || snx < 0 || snx >= 4 || board[sny][snx] == 0 || board[sny][snx] == -1) continue;

        int eatenFishNum = board[sny][snx];
        int dir = fishes[eatenFishNum].second-1;
        tmp += eatenFishNum;
        fishes.erase(eatenFishNum);
        board[sny][snx] = -1;
        board[sy][sx] = 0;

        eat(sny, snx, dir, board, fishes);

        tmp -= eatenFishNum;
        fishes[eatenFishNum] = make_pair(make_pair(sny, snx), dir+1);
        board[sny][snx] = eatenFishNum;
        board[sy][sx] = -1;
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int board[4][4];
    map< int, pair<pair<int, int>, int> > fishes; // fish num : {{y, x}, dir}
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            int a, b;
            cin >> a >> b;
            board[i][j] = a;
            fishes.insert(make_pair(a, make_pair(make_pair(i, j), b)));
        }
    }

    tmp += board[0][0];
    int dir = fishes[board[0][0]].second-1;
    fishes.erase(board[0][0]);
    board[0][0] = -1;

    eat(0, 0, dir, board, fishes);

    cout << mx << '\n';
}

/* map 출력문
     for(const auto& item : fishes) {
        cout << item.first << ' ';
    }
    cout << '\n';
 */

/* board 출력문
 *     for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            cout << board[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
 */