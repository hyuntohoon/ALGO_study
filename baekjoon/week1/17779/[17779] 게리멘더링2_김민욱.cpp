#include <bits/stdc++.h>
using namespace std;
int n;
int board[21][21];
int restrict[21][21];
int sum;
int ans = 10e8;
int population[5];
vector<int> vec;

void calcPop(int x, int y, int d1, int d2) {
    fill(population, population+5, 0);
    for(int i=0; i<21; i++) {
        fill(restrict[i], restrict[i]+21, 0);
    }

    // 5구역
    int curX = x;
    int curY = y;
    while(curX <= x+d1 && curY >= y-d1) {
        restrict[curX++][curY--] = 5;
    }

    curX = x;
    curY = y;
    while(curX <= x+d2 && curY <= y+d2) {
        restrict[curX++][curY++] = 5;
    }

    curX = x+d1;
    curY = y-d1;
    while(curX <= x+d1+d2 && curY <= y-d1+d2) {
        restrict[curX++][curY++] = 5;
    }

    curX = x+d2;
    curY = y+d2;
    while(curX <= x+d2+d1 && curY >= y+d2-d1) {
        restrict[curX++][curY--] = 5;
    }

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(restrict[i][j] == 5) {
                vec.push_back(j);
            }
        }
//        cout << i << vec.size() << '\n';
        if(vec.size() == 2) {
            int st = vec[0];
            int en = vec[1];
            for(int j=st+1; j<en; j++) {
                restrict[i][j] = 5;
            }
        }
        vec.clear();
    }

    for(int r=1; r<x+d1; r++) { // 1구역
        for(int c=1; c<=y; c++) {
            if(restrict[r][c] == 5) continue;
            restrict[r][c] = 1;
        }
    }
    for(int r=1; r<=x+d2; r++) { // 2구역
        for(int c=y+1; c<=n; c++) {
            if(restrict[r][c] == 5) continue;
            restrict[r][c] = 2;
        }
    }
    for(int r=x+d1; r<=n; r++) { // 3구역
        for(int c=1; c<y-d1+d2; c++) {
            if(restrict[r][c] == 5) continue;
            restrict[r][c] = 3;
        }
    }
    for(int r=x+d2+1; r<=n; r++) { // 4구역
        for(int c=y-d1+d2; c<=n; c++) {
            if(restrict[r][c] == 5) continue;
            restrict[r][c] = 4;
        }
    }

    cout << "d1, d2, x, y: " << d1 << d2 << x << y << '\n';
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cout << restrict[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            if(restrict[i][j] == 1) {
                population[0] += board[i][j];
            } else if(restrict[i][j] == 2) {
                population[1] += board[i][j];
            } else if(restrict[i][j] == 3) {
                population[2] += board[i][j];
            } else if(restrict[i][j] == 4) {
                population[3] += board[i][j];
            } else if(restrict[i][j] == 5) {
                population[4] += board[i][j];
            }
        }
    }
    int mx = *max_element(population, population+5);
    int mn = *min_element(population, population+5);
    ans = min(ans, mx-mn);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // 1. 가능한 모든 x, y, d1, d2 경우를 구한다.
    // d1, d2에 의해 가능한 x, y가 달라지므로 d1, d2를 고정하고 x, y를 결정
    // 2. 정해진 x, y, d1, d2에 대해 선거구를 나눈다.
    // 3. 나눈 선거구에 대해 각각의 인구수를 구한다.
    // x, y, d1, d2를 이용해서 1~4 선거구의 인원수를 구하고, 전체에서 빼서 5 선거구의 인원수를 구한다.
    // 4. 가장 많은 인구의 선거구와 가장 적은 인구의 선거구의 차이의 최소를 갱신한다.
    cin >> n;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> board[i][j];
        }
    }

    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            sum += board[i][j];
        }
    }

    for(int d1=1; d1<n; d1++) {
        for(int d2=1; d2<n; d2++) {
            for(int x=1; x+d1+d2<=n; x++) {
                for(int y=1+d1; y<=n-d2; y++) {
                    calcPop(x, y, d1, d2);
                }
            }
        }
    }
    cout << ans << '\n';
}