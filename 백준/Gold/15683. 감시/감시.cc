#include <bits/stdc++.h>
using namespace std;

int n, m, result = 987654321;
vector<pair<pair<int, int>, int>> v;

int case_[5] = { 4, 2, 4, 4, 1 };
int arr[8][8];

void copy(int arr1[][8], int arr2[][8]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr1[i][j] = arr2[i][j];
		}
	}
}

void check_cctv(int dir, pair<pair<int, int>, int> cur) {
	dir %= 4;
	int y = cur.first.first;
	int x = cur.first.second;

	// 동쪽
	if (dir == 0) {
		for (int j = x + 1; j < m; j++) {
			if (arr[y][j] == 6)
				break;

			arr[y][j] = -1;
		}
	}
	// 북쪽
	else if (dir == 1) {
		for (int i = y - 1; i >= 0; i--) {
			if (arr[i][x] == 6)
				break;

			arr[i][x] = -1;
		}
	}
	// 서쪽
	else if (dir == 2) {
		for (int j = x - 1; j >= 0; j--) {
			if (arr[y][j] == 6)
				break;

			arr[y][j] = -1;
		}
	}
	// 남쪽
	else {
		for (int i = y + 1; i < n; i++) {
			if (arr[i][x] == 6)
				break;

			arr[i][x] = -1;
		}
	}
}

void dfs(int cnt) {
	// 저장한 cctv의 개수가 되면 사각지대 탐색 시작
	if (cnt == v.size()) {
		int zero = 0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (arr[i][j] == 0)
					zero++;
			}
		}

		result = min(result, zero);
		return;
	}

	int temp[8][8];
	int type = v[cnt].second;

	for (int i = 0; i < case_[type]; i++) {
		copy(temp, arr);

		if (type == 0)
			check_cctv(i, v[cnt]);
		else if (type == 1) {
			check_cctv(i, v[cnt]);
			check_cctv(i + 2, v[cnt]);
		}
		else if (type == 2) {
			check_cctv(i, v[cnt]);
			check_cctv(i + 1, v[cnt]);
		}
		else if (type == 3) {
			check_cctv(i, v[cnt]);
			check_cctv(i + 1, v[cnt]);
			check_cctv(i + 2, v[cnt]);
		}
		else {
			check_cctv(i, v[cnt]);
			check_cctv(i + 1, v[cnt]);
			check_cctv(i + 2, v[cnt]);
			check_cctv(i + 3, v[cnt]);
		}

		dfs(cnt + 1);
		copy(arr, temp);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];

			if (arr[i][j] == 0 || arr[i][j] == 6)
				continue;

			// cctv 위치와 타입 저장
			v.push_back({ {i, j}, arr[i][j] - 1 });
		}
	}

	dfs(0);

	cout << result << '\n';

	return 0;
}