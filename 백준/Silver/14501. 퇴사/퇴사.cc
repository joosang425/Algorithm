#include <bits/stdc++.h>
using namespace std;

int n, result;
int day[15], price[15], dp[15];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	// n일 만큼 진행
	for (int i = 1; i <= n; i++) {
		cin >> day[i] >> price[i];
		// 현재 일 - 1만큼 진행
		for (int j = 0; j < i; j++) {
			if (day[j] + j <= i && i + day[i] <= n + 1)
				dp[i] = max(dp[i], dp[j] + price[i]);
		}
	}

	for (int i = 0; i <= n; i++)
		result = max(result, dp[i]);

	cout << result << '\n';

	return 0;
}
