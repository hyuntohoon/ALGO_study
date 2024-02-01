//
// Created by newbi on 2024-02-01.
//
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int T[20];	//기간
int P[20];	//가격
int dp[20];	//가장 최적값 메모제이션
int n;
void fastIO() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}


int main() {

    fastIO();
    cin >> n;

    for (int i = 1; i <= n; i++) {	//값들 넣고
        cin >> T[i] >> P[i];
    }

    for (int i = n; i >= 1; i--) {
        if (T[i] + i - 1 > n) {		//날짜를 초과했다면
            dp[i] = dp[i + 1];	//이전 MAX값 가져옴
        }
        else {
            dp[i] = max(dp[i + 1], P[i] + dp[i + T[i]]);
            //현재 최적의 값은 이전의 값과 현재 값+ 다음 상담가능한 최적값의 합 중 큰 값 집어넣는다.
        }


    }

    /*
    for (int i = 0; i <= n; i++) {
        cout << T[i] << " ";
    }
    cout << endl;
    for (int i = 0; i <= n; i++) {
        cout << P[i] << " ";
    }
    cout << endl;

    for (int i = 0; i <= n; i++) {
        cout << dp[i] << " ";
    }
    cout << endl;
    */
    cout << dp[1]<<'\n';
    return 0;
}