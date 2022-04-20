#include <bits/stdc++.h>
using namespace std;

int n, m, h, a, b, result = 987654321;
bool arr[32][32];	// 가로선 번호, 세로선 번호 

bool check() {
	for (int i = 1; i <= n; i++) {
		int cur = i;

		for (int j = 1; j <= h; j++) {
			if (arr[cur][j])
				cur = cur + 1;
			else if (arr[cur - 1][j])
				cur = cur - 1;
		}

		if (cur != i)
			return false;
	}

	return true;
}

void solve(int idx, int cnt) {
	if (cnt >= 4)
		return;

	if (check()) {
		result = min(result, cnt);

		return;
	}

	for (int i = idx; i < n; i++) {
		for (int j = 1; j <= h; j++) {
			if (arr[i][j] || arr[i - 1][j] || arr[i + 1][j])
				continue;

			arr[i][j] = true;
			solve(i, cnt + 1);
			arr[i][j] = false;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> h;

	//	a: 가로선 번호, b: 세로선 번호 
	for (int i = 0; i < m; i++) {
		cin >> a >> b;

		arr[b][a] = true;
	}

	solve(1, 0);

	if (result == 987654321)
		cout << -1 << '\n';
	else
		cout << result << '\n';

	return 0;
}