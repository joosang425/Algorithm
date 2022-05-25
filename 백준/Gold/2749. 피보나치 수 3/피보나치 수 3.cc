#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000;
long long n, arr[1500050];

void fib() {
	arr[0] = 0;
	arr[1] = arr[2] = 1;

	for (int i = 3; i < 1500000; i++)
		arr[i] = (arr[i - 1] + arr[i - 2]) % MOD;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	fib();

	cout << arr[n % 1500000] << '\n';

	return 0;
}