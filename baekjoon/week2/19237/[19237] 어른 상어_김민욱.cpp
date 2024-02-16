#include <bits/stdc++.h>
using namespace std;

class Shark {
public:
    int num;
    int y;
    int x;
    int dir;
    Shark(int num, int y, int x) {
        this->num = num;
        this->y = y;
        this->x = x;
    }

//    bool operator==(const Shark& other) const {
//        return this->num == other.num;
//    }
};

int n, m, k;
pair<int, int> board[21][21]; // 상어 번호와 냄새가 사라지기 까지 시간
vector<Shark> shark;
int direction[401][4][4]; // 상어 번호, 방향, 방향 우선 순위
// 위 아래 왼쪽 오른쪽 순서
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m >> k;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            int x;
            cin >> x;
            if(x != 0)
                shark.push_back(*new Shark(x, i, j));
        }
    }
    for(int i=1; i<=m; i++) {
        for(auto& shk : shark) {
            if(shk.num == i) {
                cin >> shk.dir;
            }
        }
    }
    for(int i=0; i<m; i++) {
        for(int j=0; j<4; j++) {
            for(int l=0; l<4; l++) {
                cin >> direction[i][j][l];
            }
        }
    }

    // 1. 냄새 뿌리기
    // 2. 상어 이동
    // 3. 겹치는 상어 제거
    // 4. 1번 상어만 남았는지 확인
    // 5. 냄새 쿨타임 1감소

    int t=0;
    while(true) {

        t++;
        // 냄새 뿌리기
        for(auto &shk : shark) {
            board[shk.y][shk.x] = {shk.num, k};
        }

        // 상어 이동
        for(auto &shk : shark) {
            bool isMove = false;
            for(int dir=0; dir<4; dir++) { // 위 아래 좌 우
                int ny = shk.y + dy[direction[shk.num-1][shk.dir-1][dir]-1];
                int nx = shk.x + dx[direction[shk.num-1][shk.dir-1][dir]-1];
                if(ny < 1 || ny > n || nx < 1 || nx > n)    continue;
                if(board[ny][nx].first != 0)    continue;
                isMove = true;
                shk.dir = direction[shk.num-1][shk.dir-1][dir];
                shk.y = ny;
                shk.x = nx;
                break;
            }
            if(!isMove) { // 냄새가 없는 칸이 없으면 자신의 냄새가 있는 칸으로 우선 순위에 따라 이동
                for(int dir=0; dir<4; dir++) {
                    int ny = shk.y + dy[direction[shk.num-1][shk.dir-1][dir]-1];
                    int nx = shk.x + dx[direction[shk.num-1][shk.dir-1][dir]-1];
                    if(ny < 1 || ny > n || nx < 1 || nx > n)    continue;
                    if(board[ny][nx].first == shk.num) {
                        shk.dir = direction[shk.num-1][shk.dir-1][dir];
                        shk.y = ny;
                        shk.x = nx;
                        break;
                    }
                }
            }
        }

        // 겹치는 상어 제거
        for(int i=0; i<shark.size(); i++) {
            for(int j=i+1; j<shark.size(); j++) {
                if(shark[i].y == shark[j].y && shark[i].x == shark[j].x) {
                    if(shark[i].num < shark[j].num) {
//                        shark.erase(remove(shark.begin(), shark.end(), shark[j]), shark.end());
                        shark.erase(shark.begin() + j);
                        j--;
                    } else {
//                        shark.erase(remove(shark.begin(), shark.end(), shark[i]), shark.end());
                        shark.erase(shark.begin() + i);
                        i--;
                        break;
                    }
                }
            }
        }

        // 상어 1번만 남았는지 확인
        if(shark.size() == 1 || t > 1000) {
            break;
        }

        // 냄새 쿨타임 1 감소
        for(int i=1; i<=n; i++) {
            for(int j=1; j<=n; j++) {
                if(board[i][j].second > 0) {
                    board[i][j].second--;
                    if(board[i][j].second == 0) { // 0초가 되면 board에서 냄새 없앰
                        board[i][j].first = 0;
                    }
                }
            }
        }
    }
    t = t > 1000 ? -1 : t;
    cout << t << '\n';
}