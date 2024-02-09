#include <bits/stdc++.h>
using namespace std;
int n;
int score;
int cnt;
int board[11][11];

void moveBlock(int t, int x, int y) {
    int curX = x;
    int curY = y;
    if (t == 1) { // 1x1
        curX = x;
        curY = y;
        while (curY < 9 && board[curX][curY + 1] == 0) { // 파란색에 블록 추가
            curY++;
        }
        board[curX][curY] = 1;

        curX = x;
        curY = y;
        while (curX < 9 && board[curX+1][curY] == 0) { // 초록색에 블록 추가
            curX++;
        }
        board[curX][curY] = 1;
    } else if (t == 2) { // 1x2
        curX = x;
        curY = y;
        while (curY < 9 && board[curX][curY + 1] == 0) { // 파란색에 블록 추가
            curY++;
        }
        board[curX][curY] = 1;
        board[curX][curY-1] = 1;

        curX = x;
        curY = y;
        while (curX < 9 && board[curX+1][curY] == 0 && board[curX+1][curY+1] == 0) { // 초록색에 블록 추가
            curX++;
        }
        board[curX][curY] = 1;
        board[curX][curY+1] = 1;
    } else if(t == 3) { // 2x1
        curX = x;
        curY = y;
        while (curY < 9 && board[curX][curY + 1] == 0 && board[curX+1][curY+1] == 0) { // 파란색에 블록 추가
            curY++;
        }
        board[curX][curY] = 1;
        board[curX+1][curY] = 1;

        curX = x;
        curY = y;
        while (curX < 9 && board[curX+1][curY] == 0) { // 초록색에 블록 추가
            curX++;
        }
        board[curX][curY] = 1;
        board[curX-1][curY] = 1;
    }
}

void getScore() {
    // 파란칸 점수 흭득 가능 여부 확인
    for (int j = 9; j > 5; j--) {
        bool isFull = true;
        for (int i = 0; i < 4; i++) {
            if (board[i][j] != 1) {
                isFull = false;
            }
        }
        if (isFull) { // j번째 열이 가득 찼으면 한칸씩 옮김
            for (int k = j; k >= 1; k--) { // 열
                for (int l = 0; l < 4; l++) { // 행
                    board[l][k] = board[l][k - 1];
                    board[l][k-1] = 0;
                }
            }
            j++; // 한 칸 내린 후, 내린 칸부터 다시 조사
            score++;
        }
    }

    // 연두색칸 점수 흭득 가능 여부 확인
    for (int i = 9; i > 5; i--) {
        bool isFull = true;
        for (int j = 0; j < 4; j++) {
            if (board[i][j] != 1) {
                isFull = false;
            }
        }
        if (isFull) { // i번째 행이 가득 찼으면 한칸씩 옮김
            for (int k = i; k >= 1; k--) { // 행
                for (int l = 0; l < 4; l++) { // 열
                    board[k][l] = board[k-1][l];
                    board[k-1][l] = 0;
                }
            }
            i++; // 한 칸 내린 후, 내린 칸부터 다시 조사
            score++;
        }
    }
}

void blur() {
    int blurCnt = 0;
    for(int j=4; j<6; j++) { // 파란색 연한 부분에 포함된 블록 열 수 확인
        for(int i=0; i<4; i++) {
            if(board[i][j] == 1) {
                blurCnt++;
                break;
            }
        }
    }

    while(blurCnt--) { // 파란색 연한 부분 처리
        for(int j=9; j>4; j--) {
            for(int i=0; i<4; i++) {
                board[i][j] = board[i][j-1];
                board[i][j-1] = 0;
            }
        }
    }

    blurCnt = 0;
    for(int i=4; i<6; i++) { // 초록색 연한 부분에 포함된 블록 행 수 확인
        for(int j=0; j<4; j++) {
            if(board[i][j] == 1) {
                blurCnt++;
                break;
            }
        }
    }

    while(blurCnt--) { // 초록색 연한 부분 처리
        for(int i=9; i>4; i--) {
            for(int j=0; j<4; j++) {
                board[i][j] = board[i-1][j];
                board[i-1][j] = 0;
            }
        }
    }
}

int main() {
    // 1. 블록에 대한 입력을 받는다.
    // 2. 입력받은 블록에 해당하는 유형의 블록을 board에 추가한다.
    // 3. 점수를 얻을 수 있는지 확인한다.
    // 4. 연한 부분을 처리한다.
    cin >> n;
    while (n--) {
        int t, x, y;
        cin >> t >> x >> y;
        moveBlock(t, x, y);
        getScore();
        blur();
    }

    for(int i=0; i<4; i++) { // 파란색 보드 블록 수
        for(int j=6; j<10; j++) {
            if(board[i][j] == 1)    cnt++;
        }
    }

    for(int i=6; i<10; i++) { // 초록색 보드 블록 수
        for (int j=0; j<4; j++) {
            if (board[i][j] == 1) cnt++;
        }
    }
    cout << score << '\n';
    cout << cnt << '\n';
}