#include <bits/stdc++.h>
using namespace std;

class Tree {
public:
    int y;
    int x;
    int age;
    Tree(int y, int x, int age) {
        this->y = y;
        this->x = x;
        this->age = age;
    }
    bool operator < (Tree& tree) {
        return this->age < tree.age;
    }
};

int n, m, k;
int board[11][11]; // 땅의 양분을 저장
int a[11][11]; // 추가되는 양분의 양
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
deque<Tree> trees;
vector<Tree> dTrees;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    // 1. 봄: 나무가 자신의 나이만큼 양분을 먹고, 나이가 1 증가
    // 자신의 칸에 있는 양분만 먹을 수 있음. 하나의 칸에 여러개의 나무 -> 어린 나무부터 양분
    // 자신의 나이만큼 양분 못먹으면 죽음
    // 2. 여름: 봄에 죽은 나무가 양분으로 변함. 죽은 나무마다 나이/2를 양분에 추가
    // 3. 가을: 나무 번식. 나무 나이 5의 배수
    // 4. 겨울: 땅에 입력만큼 양분 추가
    // 5. k번 반복 후 나무의 개수 세기
    cin >> n >> m >> k;
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin >> a[i][j];
            board[i][j] = 5;
        }
    }
    for(int i=0; i<m; i++) {
        int y, x, age;
        cin >> y >> x >> age; // 행, 열, 나이 순 입력
        trees.push_back(Tree(y, x, age));
    }

    sort(trees.begin(), trees.end());

    while(k--) {

//        for(int i=1; i<=n; i++) {
//            for(int j=1; j<=n; j++) {
//                cout << board[i][j] << ' ';
//            }
//            cout << '\n';
//        }
//        cout << '\n';
//
//        for(auto& tree : trees) {
//            cout << tree.y << ' ' << tree.x << ' ' << tree.age << '\n';
//        }

        // 봄
        int size = trees.size();
        while(size--) {
            Tree tree = trees.front();
            trees.pop_front();
            if(board[tree.y][tree.x] >= tree.age) {
                board[tree.y][tree.x] -= tree.age;
                tree.age++;
                trees.push_back(tree);
            } else {
                dTrees.push_back(tree);
            }
        }

        // 여름
        for(auto& dt : dTrees) {
            board[dt.y][dt.x] += dt.age/2;
        }
        dTrees.clear();

        // 가을
        size = trees.size();
        vector<Tree> tmp;
        while(size--) {
            Tree tree = trees.front();
            trees.pop_front();
            if(tree.age % 5 == 0) {
                for(int dir=0; dir<8; dir++) {
                    int ny = tree.y + dy[dir];
                    int nx = tree.x + dx[dir];
                    if(ny < 1 || ny > n || nx < 1 || nx > n) continue;
                    trees.push_back(Tree(ny, nx, 1));
                }
            }
            tmp.push_back(tree);
        }
        for(auto& t : tmp) {
            trees.push_back(t);
        }

        // 겨울
        for(int i=1; i<=n; i++) {
            for(int j=1; j<=n; j++) {
                board[i][j] += a[i][j];
            }
        }

    }
    cout << trees.size() << '\n';
}