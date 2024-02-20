#include <iostream>
#include <vector>
#include <queue>
#define FOR(i,n) for(int i=0;i<n;i++)
int dx[4] = {0,0,-1,1};
int dy[4] = {1,-1,0,0};

using namespace std;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    int N;
    bool favoritePeople[401][401];
    int arr[21][21];
    FOR(i, 401) {
        FOR(j, 401) {
            favoritePeople[i][j] = 0;
        }
    }
    FOR(i,21){
        FOR(j, 21) {
            arr[i][j] = -1;
        }
    }
    queue<int> Q;
    cin >> N;
    FOR(i, (N * N)) {
        int temp;
        cin >> temp;
        Q.push(temp);
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        favoritePeople[temp][a] = 1;
        favoritePeople[temp][b] = 1;
        favoritePeople[temp][c] = 1;
        favoritePeople[temp][d] = 1;
    }
    while (!Q.empty()) {
        int nowSitPeople = Q.front();
        Q.pop();
        int bestFavoritePeopleCount = -1;
        int bestBlankSit = -1;
        int goodX = -1;
        int goodY = -1;
        FOR(x, N) {
            FOR(y, N) {
                if (arr[x][y] != -1) continue;
                int nowFavoritePeopleCount = 0;
                int blankSit = 0;
                FOR(k, 4) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (nx >= 0 && ny >= 0 && nx < N && ny < N) {
                        if (arr[nx][ny] == -1) blankSit++;
                        else if (favoritePeople[nowSitPeople][arr[nx][ny]]) nowFavoritePeopleCount++;
                    }
                }
                if (nowFavoritePeopleCount > bestFavoritePeopleCount || 
                    (nowFavoritePeopleCount == bestFavoritePeopleCount && blankSit > bestBlankSit) ||
                    (nowFavoritePeopleCount == bestFavoritePeopleCount && blankSit == bestBlankSit && (goodX == -1 || x < goodX || (x == goodX && y < goodY)))) {
                    bestFavoritePeopleCount = nowFavoritePeopleCount;
                    bestBlankSit = blankSit;
                    goodX = x;
                    goodY = y;
                }
            }
        }
        arr[goodX][goodY] = nowSitPeople;
    }
    int result = 0;
    FOR(x, N) {
        FOR(y, N) {
            int nowFavoritePeopleCount = 0;
            FOR(k, 4) {
                int nx = x + dx[k];
                int ny = y + dy[k];
                if (nx >= 0 && ny >= 0 && nx < N && ny < N) {
                    if(favoritePeople[arr[x][y]][arr[nx][ny]]) nowFavoritePeopleCount++;
                }
            }
            if (nowFavoritePeopleCount == 1) result += 1;
            else if (nowFavoritePeopleCount == 2) result += 10;
            else if (nowFavoritePeopleCount == 3) result += 100;
            else if (nowFavoritePeopleCount == 4) result += 1000;
        }
    }
    cout << result << endl;
}
