#include <bits/stdc++.h>
using namespace std;
int n, m, h;
int board[32][12];
int mn = 4;

// i번 세로선의 결과가 i번이 나오는지 확인
bool isValid() {
    for(int i=1; i<=n; i++) {
        int curX = i;
        int curY = 1;
        while(curY <= h) {
            if (board[curY][curX] == 1) {
                curX++;
                curY++;
            } else if(board[curY][curX-1] == 1){
                curX--;
                curY++;
            } else if(board[curY][curX] == 0) {
                curY++;
            }
        }
        if(curX != i) {
            return false;
        }
    }
    return true;
}

// dfs 한 번 호출마다 사다리 하나를 결정
void dfs(int k, int row, int col) {

    if(isValid()) {
        mn = min(mn, k);
        return;
    }

    if(k == 3) {
        return;
    }

    for(int i=row; i<=h; i++) {
        for(int j = (i == row ? col : 1); j<n; j++) {
            if(board[i][j] == 1 || board[i][j-1] == 1 || board[i][j+1] == 1) continue;
            board[i][j] = 1;
            dfs(k+1, i, j+2);
            board[i][j] = 0;
        }
    }
}

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    // 1. i번 세로선의 결과가 i번이 나오는지 확인
    // i세로선이 i결과가 나오지 않으면 바로 false return
    // 2. 추가 가능한 자리에 사다리를 추가
    // 이미 사다리가 있거나, 연속하는 경우 사다리 추가 X
    // 3. 추가 후 i번 세로선의 결과가 i번이 나오는지 확인
    // 4. 3개까지 추가해본 후 backtrack하고 다른 경우 진행 반복

    cin >> n >> m >> h;
    int a, b;
    for(int i=0; i<m; i++) {
        cin >> a >> b;
        board[a][b] = 1;
    }
    dfs(0, 1, 1);
    if(mn > 3) {
        cout << -1 << '\n';
        return 0;
    }
    cout << mn << '\n';
}