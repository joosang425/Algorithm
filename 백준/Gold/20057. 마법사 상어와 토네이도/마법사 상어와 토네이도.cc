#include <bits/stdc++.h>
using namespace std;

int n, cnt, result, arr[500][500];
// 좌, 하, 우, 상
int dir[4][10][3] = {
	{{-1, 0, 1}, {1, 0, 1}, {-1, -1, 7}, {1, -1, 7}, {-2, -1, 2}, {2, -1, 2}, {-1, -2, 10}, {1, -2, 10}, {0, -3, 5}, {0, -2 ,0}},
	{{0, -1, 1}, {0, 1, 1}, {1, -1, 7}, {1, 1, 7}, {1, -2, 2}, {1, 2, 2}, {2, -1, 10}, {2, 1, 10}, {3, 0, 5}, {2, 0, 0}},
	{{-1, 0, 1}, {1, 0, 1}, {-1, 1, 7}, {1, 1, 7}, {-2, 1, 2}, {2, 1, 2}, {-1, 2, 10}, {1, 2, 10}, {0, 3, 5}, {0, 2, 0}},
	{{0, -1, 1}, {0, 1, 1}, {-1, -1, 7}, {-1, 1, 7}, {-1, -2, 2}, {-1, 2, 2}, {-2, -1, 10}, {-2, 1, 10}, {-3, 0, 5}, {-2, 0, 0}}
};

void spread(int y, int x) {
	cnt++;
	// 좌
	for (int j = 0; j < cnt; x--, j++) {
		int sum = 0;

		for (int d = 0; d < 9; d++) {
			int ny = y + dir[0][d][0];
			int nx = x + dir[0][d][1];
			int value = (arr[y][x - 1] * dir[0][d][2]) / 100;

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) {
				result += value;
				sum += value;
			}
			else {
				arr[ny][nx] += value;
				sum += value;
			}
		}

		int ny = y + dir[0][9][0];
		int nx = x + dir[0][9][1];

		if (ny < 0 || ny >= n || nx < 0 || nx >= n)
			result += (arr[y][x - 1] - sum);
		else
			arr[ny][nx] += (arr[y][x - 1] - sum);

		arr[y][x - 1] = 0;
	}
	// 하
	for (int i = 0; i < cnt; y++, i++) {
		int sum = 0;

		for (int d = 0; d < 9; d++) {
			int ny = y + dir[1][d][0];
			int nx = x + dir[1][d][1];
			int value = (arr[y + 1][x] * dir[1][d][2]) / 100;

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) {
				result += value;
				sum += value;
			}
			else {
				arr[ny][nx] += value;
				sum += value;
			}
		}

		int ny = y + dir[1][9][0];
		int nx = x + dir[1][9][1];

		if (ny < 0 || ny >= n || nx < 0 || nx >= n)
			result += (arr[y + 1][x] - sum);
		else
			arr[ny][nx] += (arr[y + 1][x] - sum);

		arr[y + 1][x] = 0;
	}

	cnt++;
	// 우
	for (int j = 0; j < cnt; x++, j++) {
		int sum = 0;

		for (int d = 0; d < 9; d++) {
			int ny = y + dir[2][d][0];
			int nx = x + dir[2][d][1];
			int value = (arr[y][x + 1] * dir[2][d][2]) / 100;

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) {
				result += value;
				sum += value;
			}
			else {
				arr[ny][nx] += value;
				sum += value;
			}
		}

		int ny = y + dir[2][9][0];
		int nx = x + dir[2][9][1];

		if (ny < 0 || ny >= n || nx < 0 || nx >= n)
			result += (arr[y][x + 1] - sum);
		else
			arr[ny][nx] += (arr[y][x + 1] - sum);

		arr[y][x + 1] = 0;
	}
	// 상
	for (int i = 0; i < cnt; y--, i++) {
		int sum = 0;

		for (int d = 0; d < 9; d++) {
			int ny = y + dir[3][d][0];
			int nx = x + dir[3][d][1];
			int value = (arr[y - 1][x] * dir[3][d][2]) / 100;

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) {
				result += value;
				sum += value;
			}
			else {
				arr[ny][nx] += value;
				sum += value;
			}
		}

		int ny = y + dir[3][9][0];
		int nx = x + dir[3][9][1];

		if (ny < 0 || ny >= n || nx < 0 || nx >= n)
			result += (arr[y - 1][x] - sum);
		else
			arr[ny][nx] += (arr[y - 1][x] - sum);

		arr[y - 1][x] = 0;
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

	// 시작점은 정중앙
	int sy = (n - 1) / 2, sx = (n - 1) / 2;

	// 7X7 -> 3번, 5X5 -> 2번
	for (int i = 0; i < (n - 1) / 2; i++)
		spread(sy--, sx++);

	cnt++;
	// 좌
	for (int j = 0; j < cnt; sx--, j++) {
		int sum = 0;

		for (int d = 0; d < 9; d++) {
			int ny = sy + dir[0][d][0];
			int nx = sx + dir[0][d][1];
			int value = (arr[sy][sx - 1] * dir[0][d][2]) / 100;

			if (ny < 0 || ny >= n || nx < 0 || nx >= n) {
				result += value;
				sum += value;
			}
			else {
				arr[ny][nx] += value;
				sum += value;
			}
		}

		int ny = sy + dir[0][9][0];
		int nx = sx + dir[0][9][1];

		if (ny < 0 || ny >= n || nx < 0 || nx >= n)
			result += (arr[sy][sx - 1] - sum);
		else
			arr[ny][nx] += (arr[sy][sx - 1] - sum);

		arr[sy][sx - 1] = 0;
	}

	cout << result << '\n';

	return 0;
}
