//#include "H.h"
#include <iostream>
#include <algorithm>
#include <vector>

#include <stdio.h>
#define FOR(i,n) for(int i=0;i<n;i++)
#define MAX 1000
#define RED 1
#define BLUE 0

using namespace std;
int N;
vector<int> S;
vector<int> L;
int arr[21][21];
int ans = 123456789;

void go(int person) {
	if (person == N) {
		if (S.size() == N / 2 && L.size() == N / 2) {
			int T1 = 0, T2 = 0;
			int temp;
			FOR(i, N / 2) {
				for (int j = 0; j < N / 2; j++) {
					T1 += arr[S[i]][S[j]];
				}
			}
			FOR(i, N / 2) {
				for (int j = 0; j < N / 2; j++) {
					T2 += arr[L[i]][L[j]];
				}
			}
			temp = T1 - T2;
			if (temp < 0) {
				temp *= -1;
			}
			ans = min(temp, ans);
		}
		return;
	}
	S.push_back(person);
	go(person + 1);
	S.pop_back();
	L.push_back(person);
	go(person + 1);
	L.pop_back();


}
int main() {
	cin >> N;
	FOR(i, N) {
		for (int j = 0; j < N; j++) {
			cin >> arr[i][j];
		}
	}
	go(0);
	cout << ans;
}
