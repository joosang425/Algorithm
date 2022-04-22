#include <bits/stdc++.h>
using namespace std;

int r, c, t, result, arr[50][50];

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
pair<int, int> m_up, m_down;

void dust_move() {
	int temp[50][50] = { 0, };

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (arr[i][j] == -1 || arr[i][j] == 0)
				continue;

			int cnt = 0;

			for (int d = 0; d < 4; d++) {
				int y = i + dir[d][0];
				int x = j + dir[d][1];

				if (y < 0 || y >= r || x < 0 || x >= c || arr[y][x] == -1)
					continue;

				temp[y][x] += arr[i][j] / 5;
				cnt++;
			}

			arr[i][j] -= arr[i][j] / 5 * cnt;
		}
	}

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			arr[i][j] += temp[i][j];
		}
	}
}

void air_move() {
	// 공기청정기 위
	int y = m_up.first, x = m_up.second;
	for (int i = y - 1; i > 0; i--)
		arr[i][x] = arr[i - 1][x];
	for (int j = x; j < c - 1; j++)
		arr[0][j] = arr[0][j + 1];
	for (int i = 0; i < y; i++)
		arr[i][c - 1] = arr[i + 1][c - 1];
	for (int j = c - 1; j > x + 1; j--)
		arr[y][j] = arr[y][j - 1];

	arr[y][x + 1] = 0;

	// 공기청정기 아래
	y = m_down.first, x = m_down.second;
	for (int i = y + 1; i < r - 1; i++)
		arr[i][x] = arr[i + 1][x];
	for (int j = 0; j < c - 1; j++)
		arr[r - 1][j] = arr[r - 1][j + 1];
	for (int i = r - 1; i > y; i--)
		arr[i][c - 1] = arr[i - 1][c - 1];
	for (int j = c - 1; j > x + 1; j--)
		arr[y][j] = arr[y][j - 1];

	arr[y][x + 1] = 0;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> r >> c >> t;

	int cnt = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> arr[i][j];

			// 공기청정기에 해당하는 행 저장
			if (cnt == 0 && arr[i][j] == -1) {
				m_up.first = i;
				m_up.second = j;
				cnt++;
			}
			else if (cnt >= 1 && arr[i][j] == -1) {
				m_down.first = i;
				m_down.second = j;
			}
		}
	}

	for (int i = 0; i < t; i++) {
		dust_move();
		air_move();
	}

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (arr[i][j] == -1)
				continue;

			result += arr[i][j];
		}
	}

	cout << result << '\n';

	return 0;
}