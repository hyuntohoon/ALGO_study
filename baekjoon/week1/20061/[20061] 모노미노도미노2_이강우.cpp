#include <iostream>

#define For(i,a,b) for(int i=a;i<b;i++)
#define endl '\n'

using namespace std;

bool domino[10][10];

int dx[2] = { 0,1 };	//우, 하
int dy[2] = { 1,0 };
int N, score;
int curX,curY,curT;
bool out(int x, int y) {	//장외 처리
    return x < 0 || x >= 10 || y < 0 || y >= 10;
}

void fastIO() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);
}
void move() {	// 오른쪽으로 이동
    int addX =0 ,addY = 0;  //추가 좌표
    if(curT == 2) {
        addX = curX;
        addY = curY+1;
        domino[addX][addY] = false;
    }
    else if(curT == 3) {
        addX = curX + 1;
        addY = curY;
        domino[addX][addY] = false;
    }
    domino[curX][curY] = false;	//현재 도미노 초기화

    int x = curX;
    int y = curY;
    int xx = addX;
    int yy = addY;
    int qx,qy,tx,ty;
    while (true) {
        qx = x + dx[0];
        qy = y + dy[0];

        if(curT != 1) {
            tx = xx + dx[0];
            ty = yy + dy[0];
            if (out(tx, ty) || domino[tx][ty]) break;
        }

        if (out(qx, qy) || domino[qx][qy]) break;	//장외거나, 이미 도미노가 있는 자리라면
        //update
        x = qx;
        y = qy;
        xx = tx;
        yy = ty;
    }
    domino[x][y] = true;
    if(curT != 1) domino[xx][yy] = true;


    x = curX;
    y = curY;
    xx = addX;
    yy = addY;      //변수 초기화

    while (true) {
        qx = x + dx[1];
        qy = y + dy[1];

        if (out(qx, qy) || domino[qx][qy]) break;	//장외거나, 이미 도미노가 있는 자리라면
        //update
        if(curT != 1) {
            tx = xx + dx[1];
            ty = yy + dy[1];
            if (out(tx, ty) || domino[tx][ty]) break;
        }
        x = qx;
        y = qy;
        xx = tx;
        yy = ty;
    }
    domino[x][y] = true;
    if(curT != 1) domino[xx][yy] = true;
}


void print() {
    For(i, 0, 10) {
        For(j, 0, 10) {
            if (i >= 4 && j >= 4) {
                cout << "  ";
            }
            else {
                if (domino[i][j]) {	//도미노 라면
                    cout << 'O' << " ";
                }
                else {				//도미노가 아니라면
                    cout << 'X' << " ";
                }
            }
        }
        cout << endl;
    }

}
void right_scoop(int col) {	//param : 현재 열
    for (int i = col; i >= 4;i--) {
        for (int j = 0; j < 4; j++) {
            domino[j][i] = domino[j][i-1];	//한칸 씩 떙긴다.
        }
    }
}

void down_scoop(int row){
    for (int i = row; i >= 4;i--) {
        for (int j = 0; j < 4; j++) {
            domino[i][j] = domino[i-1][j];	//한칸 씩 떙긴다.
        }
    }
}

void check() {	//오른쪽 체크
    for (int i = 4; i < 10; i++) {	//맞는지 체크
        bool found = true;
        for (int j = 0; j < 4; j++) {
            if (!domino[j][i]) {	//행중에  false 값이 나온다면
                found = false;	//찾음 처리
                break;
            }
        }
        if (found) {	//4개가 완벽한 라인 찾았다면
            score++;
            right_scoop(i);	//한칸씩 땡겨온다
        }
    }
    int rcnt = 0;
    for(int a=4;a<6;a++){   //신비한 영역 진입
        for(int b=0;b<4;b++){
            if(domino[b][a]){
                rcnt++;
                break;
            }
        }
    }
    while(rcnt--){
        right_scoop(9); //마지막 행 부터 땡겨온다
    }

    for (int i = 4; i < 10; i++) {    //맞는지 체크
        bool found = true;
        for (int j = 0; j < 4; j++) {
            if (!domino[i][j]) {    //행중에  false 값이 나온다면
                found = false;    //찾음 처리
                break;
            }
        }
        if (found) {	//4개가 완벽한 라인 찾았다면
            score++;
            down_scoop(i);	//한칸씩 땡겨온다
        }
    }

    int dcnt = 0;
    for(int a=4;a<6;a++){   //신비한 영역 진입
        for(int b=0;b<4;b++){
            if(domino[a][b]){
                dcnt++;
                break;
            }
        }
    }
    while(dcnt--){
        down_scoop(9); //마지막 행 부터 땡겨온다
    }


}
int count(){
    int sm = 0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            if(domino[i][j]) sm++;
        }
    }
    return sm;
}


int main() {
    fastIO();

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> curT >> curX >> curY;

        if (curT == 1) {	// 1X1 처리
            domino[curX][curY] = true;
        }
        else if (curT == 2) {	//1X2 처리
            domino[curX][curY] = true;
            domino[curX][curY+1] = true;
        }
        else {				//2X1 처리
            domino[curX][curY] = true;
            domino[curX+1][curY] = true;
        }
        move();
        check();
        //print();
    }
    cout << score << endl;
    cout << count() << endl;


    return 0;
}