#include <bits/stdc++.h>
using namespace std;

int n, arr[1000000], b, c;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> arr[i];

	cin >> b >> c;

	// 총감독관은 시험장에서 1명씩은 있어야 하므로 시험장 수로 저장
	long long result = n;

	for (int i = 0; i < n; i++) {
		// 총감독관이 감시할 수 있는 응시자 수를 뺀다.
		arr[i] -= b;

		// 응시자 수가 0보다 클 경우 if문 진행
		if (arr[i] > 0) {
			if (arr[i] % c > 0) {
				result += arr[i] / c;
				result++;
			}
			else
				result += arr[i] / c;
		}
	}

	cout << result << '\n';

	return 0;
}