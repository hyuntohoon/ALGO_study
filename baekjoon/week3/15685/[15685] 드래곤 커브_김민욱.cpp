#include <bits/stdc++.h>
using namespace std;

int dy[] = {0, -1, 0, 1};
int dx[] = {1, 0, -1, 0};
int board[105][105];
int n;

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for(int i=0; i<n; i++) {
        int x, y, d, g;
        cin >> x >> y >> d >> g;

        vector<int> directions;
        directions.push_back(d);
        board[y][x] = 1;
        y += dy[d];
        x += dx[d];
        board[y][x] = 1;

        while(g--) {
            for(int j=directions.size()-1; j>=0; j--) {
                int dir = (directions[j] + 1) % 4;
                y += dy[dir];
                x += dx[dir];
                board[y][x] = 1;
                directions.push_back(dir);
            }
        }
    }

    int ans = 0;
    for(int i=0; i<=100; i++) {
        for(int j=0; j<=100; j++) {
            if(board[i][j] == 1) {
                if(board[i][j+1] == 1 && board[i+1][j] == 1 && board[i+1][j+1] == 1) {
                    ans++;
                }
            }
        }
    }
    cout << ans << '\n';
}