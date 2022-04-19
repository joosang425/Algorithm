#include <bits/stdc++.h>
using namespace std;

int n, l, result, arr[100][100];

bool row_cross(int idx) {
	int same = arr[idx][0], cnt = 1;

	for (int j = 1; j < n; j++) {
		if (same == arr[idx][j])
			cnt++;
		else {
			// 두 칸의 높이 차이가 1이 아닌 경우
			if (abs(same - arr[idx][j]) > 1)
				return false;
			else {
				// 현재 칸의 높이가 더 낮은 경우
				if (same > arr[idx][j]) {
					int cur = arr[idx][j];

					for (int z = j; z < j + l; z++) {
						if (cur != arr[idx][z])
							return false;
					}

					j = j + l - 1;
					cnt = 0;
				}
				// 현재 칸의 높이가 더 높은 경우
				else {
					// l개가 연속되지 않은 경우
					if (cnt < l)
						return false;
					
					cnt = 1;
				}
			}

			same = arr[idx][j];
		}
	}

	return true;
}

bool col_cross(int idx) {
	int same = arr[0][idx], cnt = 1;

	for (int j = 1; j < n; j++) {
		if (same == arr[j][idx])
			cnt++;
		else {
			// 두 칸의 높이 차이가 1이 아닌 경우
			if (abs(same - arr[j][idx]) > 1)
				return false;
			else {
				// 현재 칸의 높이가 더 낮은 경우
				if (same > arr[j][idx]) {
					int cur = arr[j][idx];

					for (int z = j; z < j + l; z++) {
						if (cur != arr[z][idx])
							return false;
					}

					j = j + l - 1;
					cnt = 0;
				}
				// 현재 칸의 높이가 더 높은 경우
				else {
					// l개가 연속되지 않은 경우
					if (cnt < l)
						return false;

					cnt = 1;
				}
			}

			same = arr[j][idx];
		}
	}

	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> l;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		// 행
		if (row_cross(i))
			result++;
		// 열
		if (col_cross(i))
			result++;
	}

	cout << result << '\n';

	return 0;
}