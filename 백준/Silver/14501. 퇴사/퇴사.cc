#include <iostream>
using namespace std;

int day_arr[16], price_arr[16];
int dp[16], price[16];

int main() {
	int N;
	cin >> N;

	for (int i = 1; i <= N; i++)
		cin >> day_arr[i] >> price_arr[i];

	dp[1] = day_arr[1] + 1;
	price[1] = price_arr[1];

	for (int i = 2; i <= N; i++) {
		dp[i] = day_arr[i] + i;
		int max = -123456789;
		for (int j = i - 1; j >= 1; j--) {
			if (dp[j] <= i) {
				if (max < price[j])
					max = price[j];
			}
		}
		if (max == -123456789)
			price[i] = price_arr[i];
		else
			price[i] = max + price_arr[i];
	}


	int result = 0;
	for (int i = 1; i <= N; i++) {
		if (dp[i] <= N + 1) {
			if (result < price[i])
				result = price[i];
		}
	}

	cout << result << endl;

	return 0;
}