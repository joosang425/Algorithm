#include <bits/stdc++.h>
using namespace std;

int r, c, k, result, row_size, col_size, arr[100][100];

bool cmp(pair<int, int> a, pair<int, int> b) {
	if (a.second == b.second)
		return a.first < b.first;

	return a.second < b.second;
}

// R연산
void row_cal() {
	int max_col = 0;

	for (int i = 0; i < row_size; i++) {
		map<int, int> m;

		for (int j = 0; j < col_size; j++) {
			// 0은 무시
			if (arr[i][j] == 0)
				continue;

			m[arr[i][j]]++;
		}

		vector<pair<int, int>> v(m.begin(), m.end());
		sort(v.begin(), v.end(), cmp);	// 조건에 맞게 정렬

		for (int j = 0; j < col_size; j++)
			arr[i][j] = 0;

		int idx = 0;
		for (int j = 0; j < v.size(); j++) {
			// 100이상은 버림
			if (idx > 99)
				break;

			arr[i][idx++] = v[j].first;
			arr[i][idx++] = v[j].second;
		}

		// 가장 큰 열의 크기를 알아야 함
		max_col = max(max_col, idx);
	}

	col_size = max_col;
}

void col_cal() {
	int max_row = 0;

	for (int j = 0; j < col_size; j++) {
		map<int, int> m;

		for (int i = 0; i < row_size; i++) {
			if (arr[i][j] == 0)
				continue;

			m[arr[i][j]]++;
		}

		vector<pair<int, int>> v(m.begin(), m.end());
		sort(v.begin(), v.end(), cmp);

		for (int i = 0; i < row_size; i++)
			arr[i][j] = 0;

		int idx = 0;
		for (int i = 0; i < v.size(); i++) {
			if (idx > 99)
				break;

			arr[idx++][j] = v[i].first;
			arr[idx++][j] = v[i].second;
		}

		max_row = max(max_row, idx);
	}

	row_size = max_row;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> r >> c >> k;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cin >> arr[i][j];
		}
	}

	// 초기 크기는 3 X 3
	row_size = col_size = 3;

	while (1) {
		// 조건에 만족하거나 100번 이상 실행되었을 경우 종료
		if (arr[r - 1][c - 1] == k || result > 100)
			break;

		result++;
		if (row_size >= col_size)
			row_cal();
		else
			col_cal();
	}

	if (result > 100)
		cout << -1 << '\n';
	else
		cout << result << '\n';

	return 0;
}
