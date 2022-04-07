#include <bits/stdc++.h>
using namespace std;

int arr[10][10], result = 987654321;
int paper_cnt[5] = { 5, 5, 5, 5, 5 };

bool can_attach(int y, int x, int size) {
	for (int i = y; i < y + size; i++) {
		for (int j = x; j < x + size; j++) {
			if (!arr[i][j])
				return false;
		}
	}

	return true;
}

void fill_paper(int y, int x, int size, int num) {
	for (int i = y; i < y + size; i++) {
		for (int j = x; j < x + size; j++) {
			arr[i][j] = num;
		}
	}
}

void dfs(int y, int x, int cnt) {
	// 1 찾을 때까지 while문 반복
	while (arr[y][x] == 0) {
		x++;

		if (x == 10) {
			x = 0;
			y++;

			// 끝까지 간 경우 
			if (y == 10) {
				// 현재 추가된 색종이의 수와 비교
				result = min(result, cnt);
				return;
			}
		}
	}

	// 현재 색종이의 수보다 큰 경우 더 이상 진행할 필요 X 
	if (cnt >= result)
		return;

	for (int i = 5; i > 0; i--) {
		// (y + i >= 10)을 하지 않는 이유는
		// 현재 인덱스에 값을 포함해야 하므로 > 10으로 표현
		if (y + i > 10 || x + i > 10 || !paper_cnt[i - 1])
			continue;

		// 현재 위치에서 i크기의 색종이로 덮을 수 있는지 확인
		if (can_attach(y, x, i)) {
			fill_paper(y, x, i, 0);
			paper_cnt[i - 1]--;
			dfs(y, x, cnt + 1);
			paper_cnt[i - 1]++;
			fill_paper(y, x, i, 1);
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cin >> arr[i][j];
		}
	}

	dfs(0, 0, 0);

	if (result == 987654321)
		cout << -1 << '\n';
	else
		cout << result << '\n';

	return 0;
}