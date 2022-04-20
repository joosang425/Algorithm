#include <bits/stdc++.h>
using namespace std;

int n, m, h, a, b, result = 987654321;
bool arr[30][30];

// 사다리가 어디로 가는지 확인하는 함수
bool ladder_check() {
	for (int i = 1; i <= n; i++) {
		int cur = i;

		for (int j = 1; j <= h; j++) {
			// 현재 위치가 true면 위치를 다음 인덱스로 변경
			if (arr[cur][j])
				cur = cur + 1;
			// 현재 인덱스 - 1이 true면 위치를 이전 인덱스로 변경
			else if (arr[cur - 1][j])
				cur = cur - 1;
		}

		if (cur != i)
			return false;
	}

	return true;
}

void dfs(int idx, int cnt) {
	// 3보다 큰 값이면 -1
	if (cnt == 4)
		return;

	// 현재 사다리 확인
	if (ladder_check()) {
		result = min(result, cnt);

		return;
	}

	for (int i = idx; i < n; i++) {
		for (int j = 1; j <= h; j++) {
			// 두 가로선이 연속하거나 서로 접하는 경우 continue
			if (arr[i][j] || arr[i + 1][j] || arr[i - 1][j])
				continue;

			// 가로선을 추가하면서 확인
			arr[i][j] = true;
			dfs(i, cnt + 1);
			arr[i][j] = false;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> h;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;

		arr[b][a] = true;
	}

	dfs(1, 0);

	if (result == 987654321)
		cout << -1 << '\n';
	else
		cout << result << '\n';

	return 0;
}
