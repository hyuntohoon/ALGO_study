#include <iostream>
#include <algorithm>
#include <vector>
#define endl '\n'

using namespace std;

int N;
int arr[21][21];
int sum;
int result = 9876543210;

int sumSection1(int d1, int d2, int x, int y) { // section1 sum 구하기
	int start = 0;
	int nowSum = 0;
	for (int j = 1; j < y; j++) {
		if (y - d1 <= j)start++;
		for (int i = 1; i <= x + d1 - start; i++) {
			nowSum += arr[j][i];
		}
	}
	return nowSum;
}

int sumSection2(int d1, int d2, int x, int y) { // section2 sum 구하기
	int start = 0;
	int nowSum = 0;
	for (int j = y; j <= N; j++) {
		for (int i = 1; i < x+start; i++) {
			nowSum += arr[j][i];
			if (i == x + d2 - 1) break;

		}
		start++;
	}
	return nowSum;
}

int sumSection3(int d1, int d2, int x, int y) { // section3 sum 구하기
	int start = 1;
	int nowSum = 0;
	for (int j = 1; j <= y-d1+d2; j++) {
		for (int i = x + d1 + start; i <= N; i++) {
			nowSum += arr[j][i];

		}
		if (y - d1 <= j) {
			start++;
		}
	}
	return nowSum;
}

int sumSection4(int d1, int d2, int x, int y) { // section4 sum 구하기
	int start = 0;
	int nowSum = 0;
	for (int j = N; j > y - d1 + d2; j--) {
		if (y + d2 >= j) start++;
		for (int i = x + d2 + start; i <= N; i++) {
			nowSum += arr[j][i];
		}
	}
	return nowSum;
}

void checkDiv(int d1, int d2, int x, int y) { // 조건에 맞는 x, y, d1, d2 실행
	if (1 <= x + d1 + d2 && x + d1 + d2 <= N && 1 <= y - d1 && y - d1 < y && y + d2 <= N) { // 함수 실행
		int section1Sum = sumSection1(d1, d2, x, y);
		int section2Sum = sumSection2(d1, d2, x, y);
		int section3Sum = sumSection3(d1, d2, x, y);
		int section4Sum = sumSection4(d1, d2, x, y);
		int section5Sum = sum - (section1Sum + section2Sum + section3Sum + section4Sum);

		int maxSum = section1Sum;
		maxSum = max(section2Sum, maxSum);
		maxSum = max(section3Sum, maxSum);
		maxSum = max(section4Sum, maxSum);
		maxSum = max(section5Sum, maxSum);

		int minSum = section1Sum;
		minSum = min(section2Sum, minSum);
		minSum = min(section3Sum, minSum);
		minSum = min(section4Sum, minSum);
		minSum = min(section5Sum, minSum);

		result = min(result, abs(minSum - maxSum));
	}
}

void input() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for (int i = 1; i < N + 1; i++) {
		for (int j = 1; j < N + 1; j++) {
			cin >> arr[i][j];
			sum += arr[i][j];
		}
	}
}

void run() {
	input();
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int o = 1; o <= N; o++) {
				for (int p = 1; p <= N; p++) {
					checkDiv(o, p, i, j); // 4중 for문을 이용한 모든 경우의 수 시작
				}
			}
		}
	}
	cout << result << endl;
}
int main() {
	run();
}