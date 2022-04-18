#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321;

int n, number[11], oper[4];
int high = -INF, low = INF;

void dfs(int sum, int idx) {
	if (idx == n) {
		high = max(high, sum);
		low = min(low, sum);

		return;
	}

	for (int i = 0; i < 4; i++) {
		if (oper[i] > 0) {
			oper[i]--;

			if (i == 0)
				dfs(sum + number[idx], idx + 1);
			else if (i == 1)
				dfs(sum - number[idx], idx + 1);
			else if (i == 2)
				dfs(sum * number[idx], idx + 1);
			else 
				dfs(sum / number[idx], idx + 1);

			oper[i]++;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> number[i];

	for (int i = 0; i < 4; i++)
		cin >> oper[i];

	// 조합
	dfs(number[0], 1);

	cout << high << '\n' << low;

	return 0;
}