#include <bits/stdc++.h>
using namespace std;

class Shark {
public:
    int y;
    int x;
    int speed;
    int dir;
    int sz;
    bool isDie;

    Shark(int y, int x, int speed, int dir, int sz) {
        this->y = y;
        this->x = x;
        this->speed = speed;
        this->dir = dir;
        this->sz = sz;
        this->isDie = false;
    }

    bool operator < (const Shark& other) const {
        if (this->x == other.x)  return this->y < other.y;
        return this->x < other.x;
    }
};

int r, c, m;
vector<Shark> shark;
pair<int, int> sharkCache[101][101]; // 상어의 인덱스와 사이즈 저장
int fx = 0;
int ans;
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, 1, -1 };

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);

    // 1. 낚시왕 한 칸 이동
    // 2. 낚시왕이 있는 열에 있는 상어 중에서 땅과 제일 가까운 상어 잡기
    // 3. 상어 이동

    cin >> r >> c >> m;

    for(int i=0; i<m; i++) {
        int y, x, s, d, z;
        cin >> y >> x >> s >> d >> z;
        shark.push_back(Shark(y, x, s, d, z));
        sharkCache[y][x] = make_pair(i, z);
    }

    for(int i=1; i<=r; i++) {
        fill(sharkCache[i]+1, sharkCache[i]+c+1, make_pair(-1, 0));
    }

    while (fx < c) {
        fx++; // 낚시왕 한 칸 이동

        //for (auto& c : shark) {
        //    cout << c.x << ' ' << c.y << ' ' << c.isDie << ' ' << c.sz << ' ' << c.speed << '\n';
        //}
        //cout << '\n';

        // 낚시왕이 있는 열에 있는 상어중에서 땅과 제일 가까운 상어 잡기
        int mn = r+1;
        int mnIdx = -1;
        for (int i = 0; i < shark.size(); i++) {
            if (shark[i].isDie)   continue;
            if (shark[i].x != fx) continue;
            if (shark[i].y < mn) {
                mn = shark[i].y;
                mnIdx = i;
            }
        }
        if (mnIdx != -1) {
            shark[mnIdx].isDie = true;
            sharkCache[shark[mnIdx].y][shark[mnIdx].x] = make_pair( -1, 0 );
            ans += shark[mnIdx].sz;
        }

        // 상어 이동
        for (int i = 0; i<shark.size(); i++) {
            if (shark[i].isDie)   continue;
            sharkCache[shark[i].y][shark[i].x] = make_pair( -1, 0 );
            int ny = shark[i].y + dy[shark[i].dir - 1] * shark[i].speed;
            int nx = shark[i].x + dx[shark[i].dir - 1] * shark[i].speed;
            while(ny < 1 || ny > r || nx < 1 || nx > c) {
                if(ny < 1) {
                    shark[i].dir = 2;
                    int d = 1 - ny;
                    ny = 1 + d;
                }
                else if(ny > r) {
                    shark[i].dir = 1;
                    int d = ny - r;
                    ny = r - d;
                } else if(nx < 1) {
                    shark[i].dir = 3;
                    int d = 1 - nx;
                    nx = 1 + d;
                } else if(nx > c) {
                    shark[i].dir = 4;
                    int d = nx - c;
                    nx = c - d;
                }
            }
            shark[i].y = ny;
            shark[i].x = nx;
        }

        // 상어 캐시 관리
        for (int i = 0; i < shark.size(); i++) {
            if (shark[i].isDie)  continue;
            int y = shark[i].y;
            int x = shark[i].x;
            auto& priorShark = sharkCache[y][x];
            int sz = shark[i].sz;
            if (priorShark.first == i)   continue;
            if (priorShark.second != 0) { // 해당 좌표에 상어가 이미 존재할 때
                if (sz > priorShark.second) {
                    shark[priorShark.first].isDie = true;
                    priorShark.first = i;
                    priorShark.second = sz;
                }
                else {
                    shark[i].isDie = true;
                }
            }
            else { // 상어가 존재하지 않을 떄
                priorShark.first = i;
                priorShark.second = sz;
            }
        }

//        for(int i=1; i<=r; i++) {
//            for(int j=1; j<=c; j++) {
//                cout << sharkCache[i][j].first << ' ';
//            }
//            cout << '\n';
//        }
//        cout << '\n';
     }
    cout << ans << '\n';
    //    for(auto& shk : shark) {
    //        cout << shk.y << shk.x << '\n';
    //    }
}