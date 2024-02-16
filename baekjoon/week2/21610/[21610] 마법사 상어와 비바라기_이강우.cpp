//
// Created by newbi on 2024-02-16.
//
#include <iostream>
#include <vector>
#include <set>
#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'
typedef long long ll;
using namespace std;

int N, M;
ll arr[52][52];
int dx[] = {  0,-1,-1,-1,0,1,1, 1 };	//시계 방향 회전
int dy[] = { -1,-1, 0, 1,1,1,0,-1 };

int tx[] = { -1,-1,1,1 };
int ty[] = { -1,1,-1,1 };	//대각선 볼 거

pair<int,int> order[101];

struct Cloud {
    int x;
    int y;

    Cloud(int x, int y) :x(x), y(y) {}
};

vector<Cloud> clouds;
set<pair<int, int>> st;


void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

bool out(int x) {
    return x < 0 || x >= N;
}
void print() {
    For(i, 0, N ) {
        For(j, 0, N ) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;

    for (auto elem : clouds) {
        cout << elem.x << ", " << elem.y << endl;
    }

}
void move(int dir,int weight) {

    for (auto &cloud : clouds) {

        int x = cloud.x;
        int y = cloud.y;
        for (int k = 0; k < weight; k++) {
            x += dx[dir];
            y += dy[dir];

            if (x < 0) {
                x = N-1;
            }
            if (x >=N) {
                x = 0;
            }
            if (y < 0) {
                y = N-1;
            }
            if (y >= N) {
                y = 0;
            }
        }



        cloud.x = x;	//갱신한다.
        cloud.y = y;
    }

}
void rain() {

    for (auto cloud : clouds) {	//구름이 있는 위치에 물 1 증가한다.
        arr[cloud.x][cloud.y]++;
    }


}

void waterMagic() {

    for (auto cloud : clouds) {
        int cnt = 0;
        For(i, 0, 4) {
            int qx = cloud.x + tx[i];
            int qy = cloud.y + ty[i];

            if (out(qx)||out(qy) || arr[qx][qy] == 0) continue;
            cnt++;
        }
        arr[cloud.x][cloud.y] += cnt;	//물 복사한다.

    }

}
void evaporate() {
    For(i, 0, N) {
        For(j, 0, N) {
            if (arr[i][j] >= 2) {	//물이 2이상 있다면
                if (st.find({ i,j }) == st.end()) {	//이전 좌표에 없었다면
                    clouds.push_back(Cloud(i, j));	//새로운 구름을 만들고
                    arr[i][j] -= 2;	//물
                }

            }
        }
    }
}

void removeCloud() {
    st.clear();	//이전 set 초기화

    for (auto cloud : clouds) {
        st.insert({ cloud.x,cloud.y });	//집합에 전부 집어넣는다.
    }
    clouds.clear();	//구름 제거
}

void solve() {

    For(i, 0, M) {
        move(order[i].first-1, order[i].second);
        rain();
        waterMagic();
        removeCloud();
        evaporate();
    }
}

ll count() {
    ll sm = 0;
    For(i, 0, N) {
        For(j, 0, N) {
            sm += arr[i][j];
        }
    }
    return sm;
}

int main() {

    //fastIO();

    cin >> N >> M;

    For(i, 0, N) {
        For(j, 0, N) {
            cin >> arr[i][j];
        }
    }

    clouds.push_back(Cloud(N-1, 0));
    clouds.push_back(Cloud(N-1, 1));
    clouds.push_back(Cloud(N-2, 0));
    clouds.push_back(Cloud(N-2, 1));


    For(i, 0, M) {
        cin >> order[i].first;
        cin >> order[i].second;
    }

    solve();
    //print();
    cout << count() << endl;

    return 0;
}