#include <bits/stdc++.h>
using namespace std;

int n, m, x, y, k;
int dice[6]; // 상, 하, 좌, 우, 앞, 뒤
int diceTmp[6];
int board[21][21];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> x >> y >> k;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cin >> board[i][j];
        }
    }
    while(k--) {
        int dir;
        cin >> dir;
        switch (dir) {
            case 1: // 동쪽
                if(y + 1 >= m) continue;
                y += 1;
                dice[0] = diceTmp[2]; // 상 = 좌
                dice[1] = diceTmp[3]; // 하 = 우
                dice[2] = diceTmp[1]; // 좌 = 하
                dice[3] = diceTmp[0]; // 우 = 상
                dice[4] = diceTmp[4]; // 앞
                dice[5] = diceTmp[5]; // 뒤
                break;
            case  2: // 서쪽
                if(y - 1 < 0) continue;
                y -= 1;
                dice[2] = diceTmp[0]; // 좌 = 상
                dice[3] = diceTmp[1]; // 우 = 하
                dice[1] = diceTmp[2]; // 하 = 좌
                dice[0] = diceTmp[3]; // 상 = 우
                dice[4] = diceTmp[4]; // 앞
                dice[5] = diceTmp[5]; // 뒤
                break;
            case 3: // 북쪽
                if(x - 1 < 0) continue;
                x -= 1;
                dice[5] = diceTmp[0]; // 뒤 = 상
                dice[0] = diceTmp[4]; // 상 = 앞
                dice[4] = diceTmp[1]; // 앞 = 하
                dice[1] = diceTmp[5]; // 하 = 뒤
                dice[2] = diceTmp[2]; // 좌
                dice[3] = diceTmp[3]; // 우
                break;
            case 4: // 남쪽
                if(x + 1 >= n) continue;
                x += 1;
                dice[0] = diceTmp[5]; // 상 = 뒤
                dice[4] = diceTmp[0]; // 앞 = 상
                dice[1] = diceTmp[4]; // 하 = 앞
                dice[5] = diceTmp[1]; // 뒤 = 하
                dice[2] = diceTmp[2]; // 좌
                dice[3] = diceTmp[3]; // 우
                break;
         }

        if(board[x][y] != 0) {
            dice[1] = board[x][y];
            board[x][y] = 0;
        } else {
            board[x][y] = dice[1];
        }

//        for(int i=0; i<6; i++) {
//            cout << dice[i] << ' ';
//        }
//        cout << '\n';

        for(int i=0; i<6; i++) {
            diceTmp[i] = dice[i];
        }
        cout << dice[0] << '\n';
    }
}