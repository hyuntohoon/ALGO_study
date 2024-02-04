#include <bits/stdc++.h>
using namespace std;
int n, m;
int board[9][9];
int board_copy[9][9];
vector<int> cctv;
vector<int> direction;
int mn = 8*8+1;

void move(int dir, int i, int j) {
    if(dir == 0) { // 오른쪽
        for(int k=j; k<m; k++) {
            if(board[i][k] == 6)    break;
            if(board[i][k] == 0) {
                board[i][k] = -1;
            }
        }
    } else if(dir == 1) { // 아래
        for(int k=i; k<n; k++) {
            if(board[k][j] == 6)    break;
            if(board[k][j] == 0) {
                board[k][j] = -1;
            }
        }
    } else if(dir == 2) { // 왼쪽
        for(int k=j; k>=0; k--) {
            if(board[i][k] == 6)    break;
            if(board[i][k] == 0) {
                board[i][k] = -1;
            }
        }
    } else if(dir == 3) { // 위쪽
        for(int k=i; k>=0; k--) {
            if(board[k][j] == 6)    break;
            if(board[k][j] == 0) {
                board[k][j] = -1;
            }
        }
    }
}

void update() {
    int idx = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(board[i][j] == 1) {
                if(direction[idx] == 0) {
                    move(0, i, j);
                } else if(direction[idx] == 1) { // 아래
                    move(1, i, j);
                } else if(direction[idx] == 2) { // 왼쪽
                    move(2, i, j);
                } else if(direction[idx] == 3) { // 위쪽
                    move(3, i, j);
                }
                idx++;
            } else if(board[i][j] == 2) {
                if(direction[idx] == 0) {
                    move(0, i, j);
                    move(2, i, j);
                } else if(direction[idx] == 1) {
                    move(1, i, j);
                    move(3, i, j);
                }
                idx++;
            } else if(board[i][j] == 3) {
                if(direction[idx] == 0) { // 위, 오른쪽
                    move(3, i, j);
                    move(0, i, j);
                } else if(direction[idx] == 1) { // 오른쪽, 아래
                    move(0, i, j);
                    move(1, i, j);
                } else if(direction[idx] == 2) { // 아래, 왼쪽
                    move(1, i, j);
                    move(2, i, j);
                } else if(direction[idx] == 3) { // 왼쪽, 위
                    move(2, i, j);
                    move(3, i, j);
                }
                idx++;
            } else if(board[i][j] == 4) {
                if(direction[idx] == 0) { // 위, 오른쪽, 왼쪽
                    move(3, i, j);
                    move(0, i, j);
                    move(2, i, j);
                } else if(direction[idx] == 1) { // 위, 오른쪽, 아래
                    move(3, i, j);
                    move(0, i, j);
                    move(1, i, j);
                } else if(direction[idx] == 2) { // 왼쪽, 오른쪽, 아래
                    move(2, i, j);
                    move(0, i, j);
                    move(1, i, j);
                } else if(direction[idx] == 3) { // 위, 아래, 왼쪽
                    move(3, i, j);
                    move(1, i, j);
                    move(2, i, j);
                }
                idx++;
            } else if(board[i][j] == 5) {
                move(0, i, j);
                move(1, i, j);
                move(2, i, j);
                move(3, i, j);
                idx++;
            }
        }
    }

    int cnt = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(board[i][j] == 0) {
                cnt++;
            }
        }
    }
    mn = min(mn, cnt);
}

void undo() {
    for(int i=0; i<n; i++) {
        copy(board_copy[i], board_copy[i]+m, board[i]);
    }
}

// k번째 cctv 방향을 결정
void dfs(int k) {
    if(k == cctv.size()) {
        update();
        undo();
        return;
    }

    int dirCnt;
    if(cctv[k] == 1 || cctv[k] == 3 || cctv[k] == 4) {
        dirCnt = 4;
    } else if(cctv[k] == 2) {
        dirCnt = 2;
    } else if(cctv[k] == 5) {
        dirCnt = 1;
    }
    for(int dir=0; dir<dirCnt; dir++) {
        direction.push_back(dir);
        dfs(k+1);
        direction.pop_back();
    }
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cin >> board[i][j];
            board_copy[i][j] = board[i][j];
            if(board[i][j] != 0 && board[i][j] != 6) { // cctv 벡터에 넣기
                cctv.push_back(board[i][j]);
            }
        }
    }
    // 1. board를 순회하면서 CCTV 찾아서 벡터에 넣기
    // 2. 벡터를 순회하면서 각각의 CCTV가 가능한 모든 케이스 탐색 (dfs)
    // 3. 모든 cctv를 고려하였으면 cctv번호와 방향에 맞게 board를 업데이트
    // 4. 사각지대 최소값 갱신
    // 5. board를 원래대로 되돌리고 다른 케이스에서 반복
    dfs(0);
    cout << mn << '\n';
}