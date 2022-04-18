#include <bits/stdc++.h>
using namespace std;

int n, result = 987654321, arr[20][20];
bool selected[20];

void dfs(int idx, int cnt) {
	// 두 팀으로 나눴을 경우 최솟값 계산
	if (cnt == n / 2) {
		int start = 0, link = 0;

		// 둘 다 같은 값인 경우 같은 팀
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (selected[i] && selected[j]) {
					start += arr[i][j];
					start += arr[j][i];
				}
				else if (!selected[i] && !selected[j]) {
					link += arr[i][j];
					link += arr[j][i];
				}
			}
		}

		result = min(result, abs(start - link));
		return;
	}

	for (int i = idx; i < n; i++) {
		if (selected[i])
			continue;

		selected[i] = true;
		dfs(i, cnt + 1);
		selected[i] = false;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	dfs(0, 0);

	cout << result << '\n';

	return 0;
}
