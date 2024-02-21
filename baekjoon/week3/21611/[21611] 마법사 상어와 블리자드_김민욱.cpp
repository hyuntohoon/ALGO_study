#include <bits/stdc++.h>
using namespace std;

int n, m;
int board[55][55];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };
int dy2[] = { 0, 1, 0, -1 }; // 좌 하 우 상
int dx2[] = { -1, 0, 1, 0 };
int sy, sx;
int destroyed[4]; // 폭발한 구슬의 개수
vector<pair<pair<int, int>, int>> destroyList; // 폭발 시작할 인덱스와 개수

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // 1. di, si 고려하여 구슬 파괴, 파괴된 좌표 기억
    // 2. 빈 칸으로 이동시키기 -> 리스트에 담고 0제거
    // 3. 구슬 폭발 -> 리스트에서 4개 이상 연속하는 구슬 제거
    // 4. 빈칸 이동, 폭발 반복 / 폭발 없을때 까지 반복
    // 5. 연속하는 구슬을 그룹으로 처리하여 board 갱신
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }
    sy = n / 2;
    sx = n / 2;
    while (m--) {
        int d, s;
        cin >> d >> s;
        d = d - 1;
        while (s) { // 블리자드 마법 시전
            int ny = sy + s*dy[d];
            int nx = sx + s*dx[d];
            board[ny][nx] = 0;
            s--;
        }
        int y = sy;
        int x = sx;
        int dir = 0;
        int dist = 1;
        int num = 0;
        vector<int> balls;
        bool isFinish = false;
        while (num < n*n) { // 달팽이 돌면서 리스트에 담기
            for (int i = 0; i < dist; i++) {
                int ny = y + dy2[dir];
                int nx = x + dx2[dir];
                if(ny < 0 || ny >= n || nx < 0 || nx >= n) {
                    isFinish = true;
                    break;
                }
                balls.push_back(board[ny][nx]);
                y = ny;
                x = nx;
            }
            if(isFinish)    break;
            dir = (dir + 1) % 4;
            num++;
            if (num % 2 == 0) {
                dist++;
            }
        }

        balls.erase(remove(balls.begin(), balls.end(), 0), balls.end()); // 구슬 파괴

        while (true) {
            int sz = balls.size();
            for (int i = 0; i < sz; i++) { // 구슬 폭발 반복
                int ball = balls[i];
                int cnt = 1;
                for (int j = i + 1; j < sz; j++) {
                    if (ball == balls[j]) {
                        cnt++;
                    }
                    else {
                        break;
                    }
                }
                if (cnt >= 4) {
                    destroyList.push_back({ { i, cnt } ,balls[i]});
                    i += cnt;
                }
            }

            if (destroyList.empty())   break;

            int gap = 0;
            for (auto& d : destroyList) {
                destroyed[d.second] += d.first.second;
                balls.erase(balls.begin()+d.first.first-gap, balls.begin() + d.first.first - gap + d.first.second);
                gap += d.first.second;
            }
            destroyList.clear();
        }


        // 구슬 변화
        balls.push_back(0); // 마지막 구슬 처리하기 위해 삽입
        vector<int> newBalls;
        int cnt = 1;
        for(int i=0; i<balls.size()-1; i++) {
            if(balls[i] == balls[i+1]) {
                cnt++;
            } else {
                newBalls.push_back(cnt);
                newBalls.push_back(balls[i]);
                cnt = 1;
            }
        }

        // 구슬을 board에 채우기
        dir = 0;
        dist = 1;
        num = 0;
        int idx = 0;
        y = sy;
        x = sx;
        for(int i=0; i<n; i++)
            fill(board[i], board[i]+n, 0);

        isFinish = false;
        while(idx < newBalls.size()) {
            for (int i = 0; i < dist; i++) {
                int ny = y + dy2[dir];
                int nx = x + dx2[dir];
                if(ny < 0 || ny >= n || nx < 0 || nx >= n) {
                    isFinish = true;
                    break;
                }
                board[ny][nx] = newBalls[idx++];
                if (idx >= newBalls.size()) {
                    isFinish = true;
                    break;
                }
                y = ny;
                x = nx;
            }
            if(isFinish)    break;
            dir = (dir + 1) % 4;
            num++;
            if (num % 2 == 0) {
                dist++;
            }
        }

        //cout << "newBalls: ";
        //for (int i = 0; i < newBalls.size(); i++) {
        //    cout << newBalls[i] << ' ';
        //}
        //cout << '\n';

//        for (int i = 0; i < balls.size(); i++) {
//            cout << balls[i] << ' ';
//        }
//        cout << '\n';

        //for (int i = 0; i < n; i++) {
        //    for (int j = 0; j < n; j++) {
        //        cout << board[i][j] << ' ';
        //    }
        //    cout << '\n';
        //}
        //cout << '\n';
    }

    int ans = 0;
    for(int i=1; i<=3; i++) {
        ans += i*destroyed[i];
    }
    cout << ans << '\n';
}