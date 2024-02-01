#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
typedef long long ll;

int numbers[12];
bool check[12]; 
int N;
ll arr[12];
vector<int> V;
int add;
int subt;
int mul;
int divv;
int sum;

ll maxVal = -1234567890;
ll minVal = 9876543210;
ll calVal(int sig, ll firstVal, ll secondVal) {
	ll result = firstVal;
	if (sig == 0) {
		result = result + secondVal;
	}
	if (sig == 1) {
		result = result - secondVal;
	}
	if (sig == 2) {
		result = result * secondVal;
	}
	if (sig == 3) {
		result = result / secondVal;
	}
	return result;
}
void permutation(int cnt) {
	if (cnt == sum) {
		ll result = arr[0];

		for (int i = 0; i < sum; i++) {
			result = calVal(V[numbers[i]], result, arr[i+1]);
		}
		maxVal = max(result, maxVal);
		minVal = min(result, minVal);
	}
	for (int i = 0; i < sum; i++) {
		if (check[i]) continue;
		numbers[cnt] = i;
		check[i] = 1;
		permutation(cnt + 1);
		check[i] = 0;
	}
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	cin >> add >> subt >> mul >> divv;

	sum = add + subt + mul + divv;

	for (int i = 0; i < add; i++) {
		V.push_back(0);
	}
	for (int i = 0; i < subt; i++) {
		V.push_back(1);
	}
	for (int i = 0; i < mul; i++) {
		V.push_back(2);
	}
	for (int i = 0; i < divv; i++) {
		V.push_back(3);
	}
	permutation(0);

	cout << maxVal << endl << minVal << endl;
}
