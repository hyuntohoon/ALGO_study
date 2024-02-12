#include <bits/stdc++.h>
using namespace std;
int n;
int board[21][21];
int ans;
vector<int> students[401];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, -1, 0, 1};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    for(int i=0; i<n*n; i++) {
        int num;
        vector< pair<pair<int, int>, int> > candidatePos;
        cin >> num;
        for(int j=0; j<4; j++) {
            int x;
            cin >> x;
            students[num].push_back(x);
        }

        int mx = 0;
        for(int y=1; y<=n; y++) { // 좋아하는 학생이 인접한 칸에 가장 많은 자리 후보 선택
            for(int x=1; x<=n; x++) {
                if(board[y][x] != 0) continue; // 이미 자리가 결정 났으면 continue
                int cnt = 0; // 각 자리의 좋아하는 학생 수
                for(int dir=0; dir<4; dir++) { // 4방향 탐색
                    int ny = y + dy[dir];
                    int nx = x + dx[dir];
                    if(ny < 1 || ny > n || nx < 1 || nx > n || board[ny][nx] == 0) continue;
                    for(auto& s : students[num]) { // (ny, nx)에 있는 학생이 현재 자리를 정하려는 학생(num번 학생)의 좋아하는 학생인지 판단
                        if(s == board[ny][nx]) { // 좋아하는 학생이 맞으면 좋아하는 학생 수 증가
                            cnt++;
                            break;
                        }
                    }
                }
                if(cnt >= mx) { // 좋아하는 학생 수가 현재까지 최대이면 후보에 추가
                    candidatePos.push_back(make_pair(make_pair(y, x), cnt));
                    mx = cnt;
                }
            }
        }
        for(int j=candidatePos.size()-1; j>=0; j--) { // 모든 자리를 탐색한 후, 최종적으로 결정된 최대 좋아하는 학생 수와 비교하여 더 작을 경우 후보에서 제거
            if(mx != candidatePos[j].second) {
                candidatePos.erase(remove(candidatePos.begin(), candidatePos.end(), candidatePos[j]));
            }
        }

        if(candidatePos.size() == 1) { // 만약 1번 조건에서 가능한 자리가 하나이면
            int y = candidatePos[0].first.first;
            int x = candidatePos[0].first.second;
            board[y][x] = num; // 자리 선택
            continue; // 다음 학생 자리 선택
        }


        // 아래부터 2번 조건 확인
        mx = 0;
        for(auto& pos : candidatePos) { // 현재 candidatePos에는 좋아하는 학생 수가 모두 동일한 자리만 있음
            int y = pos.first.first;
            int x = pos.first.second;
            int cnt = 0; // 인접한 빈칸 수
            for(int dir=0; dir<4; dir++) { // 4방향 탐색
                int ny = y + dy[dir];
                int nx = x + dx[dir];
                if(ny < 1 || ny > n || nx < 1 || nx > n) continue;
                if(board[ny][nx] != 0) continue;
                cnt++;
            }
            pos.second = cnt; // 좋아하는 학생 수 -> 빈칸 수로 갱신 : 이제 candidatePos에는 ((y, x), (y, x)에 인접한 빈 칸의 수)로 구성
            mx = max(mx, cnt);
        }

        for(int j=candidatePos.size()-1; j>=0; j--) { // 빈칸 수가 최대값이 아니면 제거
            if(mx != candidatePos[j].second) {
                candidatePos.erase(remove(candidatePos.begin(), candidatePos.end(), candidatePos[j]));
            }
        }

        if(candidatePos.size() == 1) { // 만약 1번 조건에서 가능한 자리가 하나이면
            int y = candidatePos[0].first.first;
            int x = candidatePos[0].first.second;
            board[y][x] = num;
            continue; // 다음 학생 자리 선택
        }

        // 아래부터 3번 조건 확인
        // 행과 열, 빈칸 수 순서를 기준으로 정렬
        std::sort(candidatePos.begin(), candidatePos.end());
        int y = candidatePos[0].first.first; // 정렬 후 첫 번째 원소 선택
        int x = candidatePos[0].first.second;
        board[y][x] = num;
    }

    // 점수 계산: 모든 칸을 순회하며 좋아하는 학생 수 구하기
    for(int k=1; k<=n; k++) {
        for(int l=1; l<=n; l++) {
            int cnt = 0;
            for(int dir=0; dir<4; dir++) {
                int ny = k + dy[dir];
                int nx = l + dx[dir];
                if(ny < 1 || ny > n || nx < 1 || nx > n) continue;
                for(auto& s : students[board[k][l]]) {
                    if(s == board[ny][nx]) {
                        cnt++;
                        break;
                    }
                }
            }
            if(cnt == 1) {
                ans += 1;
            } else if(cnt == 2) {
                ans += 10;
            } else if(cnt == 3) {
                ans += 100;
            } else if(cnt == 4) {
                ans += 1000;
            }
        }
    }
    cout << ans << '\n';
    // 1. board의 각 칸을 탐색하며 비어 있는 칸 중에 좋아하는 학생이 인접한 칸에 가장 많은 자리를 선택
    // 2. 그러한 칸이 한 개라면 그 자리로 학생 배치
    // 3. 1을 만족하는 칸이 여러 개이면 인접한 칸 중에 비어있는 칸이 가장 많은 자리로 선택
    // 4. 하나로 선택되면 그 자리로 학생 배치
    // 5. 3을 만족하는 칸도 여러개이면 행의 번호가 가장 작은 칸, 그러한 칸도 여러 개이면 열의 번호가 가장 작은 칸
}

// board 출력
//for(int i=1; i<=n; i++) {
//    for(int j=1; j<=n; j++) {
//        cout << board[i][j] << ' ';
//    }
//        cout << '\n';
//}

// 자리 선택 후보 위치 출력
//for (const auto &item: candidatePos) {
//  cout << item.first.first << item.first.second << item.second << '\n';
//}
//cout << "===============" << '\n';