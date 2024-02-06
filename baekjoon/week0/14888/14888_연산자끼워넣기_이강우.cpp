#include <iostream>

#define For(i,a,b) for(int i=a;i<b;i++)	//매크로 For문
#define endl '\n'

int pmmd[4];	//플러스, 마이너스, 곱셈, 나눗셈
int mx = -1000000004;
int mn = 1000000004;
using namespace std;

int n;

int arr[12];

int calc(int num, int alpha, int op) {	//숫자에 c에 따른 연산 해서 리턴한다.

    if (op == 0) {	//+
        num = num + alpha;
    }
    else if (op == 1) {	//-
        num = num - alpha;
    }
    else if (op == 2) {	//*
        num = num * alpha;
    }
    else {	// div
        num = num / alpha;
    }
    return num;
}

void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}

void solve(int idx, int sm) {

    if (idx == n-1) {
        if (sm > mx) mx = sm;	//최대 값 갱신

        if (sm < mn) mn = sm;	//최소 값 갱신

        return;
    }
    for (int i = 0; i < 4; i++) {
        if (pmmd[i]) {	//연산자가 있다면
            pmmd[i]--;	//연산자 하나 사용 후
            solve(idx + 1, calc(sm, arr[idx + 1], i));
            pmmd[i]++;	//연산자 원복
        }
    }

}


int main() {

    fastIO();

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    for (int i = 0; i < 4; i++) {	//덧셈, 뺼셈, 곱셈, 나눗셈
        cin >> pmmd[i];
    }
    solve(0, arr[0]);

    cout << mx << endl;
    cout << mn << endl;

    return 0;
}