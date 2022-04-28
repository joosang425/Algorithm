#include <bits/stdc++.h>
using namespace std;

int n, m, d, s, result, arr[50][50];

bool cloud[50][50], temp_cloud[50][50];

int dir[8][2] = { {0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1} };

void cloud_move(int d, int s) {
	bool temp[50][50] = { false, };

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// 구름이 있는 칸이면 진행
			if (cloud[i][j]) {
				int y = i, x = j;

				for (int m = 0; m < s; m++) {
					y = y + dir[d][0];
					// 연결되어 있기 때문에 이 조건문 필요
					if (y == -1)
						y = n - 1;
					if (y == n)
						y = 0;

					x = x + dir[d][1];
					if (x == -1)
						x = n - 1;
					if (x == n)
						x = 0;
				}

				temp[y][x] = true;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cloud[i][j] = temp[i][j];

			// 현재 구름이 있는 칸의 물의 양 1 증가
			if (temp[i][j])
				arr[i][j]++;
		}
	}
}

void water_add() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int cnt = 0;

			// 구름이 있는 칸에서 물복사버그 마법 시전
			if (cloud[i][j]) {
				for (int d = 1; d < 8; d += 2) {
					int ny = i + dir[d][0];
					int nx = j + dir[d][1];

					// 물이 없거나 격자 범위 벗어나면 continue
					if (ny < 0 || ny >= n || nx < 0 || nx >= n || arr[ny][nx] == 0)
						continue;

					cnt++;
				}

				// 물이 있는 칸의 갯수만큼 
				arr[i][j] += cnt;
			}
		}
	}
}

void cloud_create() {
	// 물의 양이 2 이상이거나 구름이 사라진 칸이 아니면 구름 생성
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] >= 2 && !cloud[i][j]) {
				temp_cloud[i][j] = true;
				arr[i][j] -= 2;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cloud[i][j] = temp_cloud[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	// 첫 비구름 생성
	cloud[n - 1][0] = cloud[n - 1][1] = cloud[n - 2][0] = cloud[n - 2][1] = true;

	// m번의 명령동안 진행
	for (int i = 0; i < m; i++) {
		cin >> d >> s;

		memset(temp_cloud, false, sizeof(temp_cloud));

		// 모든 구름 이동 및 물의 양 1증가
		cloud_move(d - 1, s);
		// 물복사버그 마법 시전
		water_add();
		// 구름 생성
		cloud_create();
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result += arr[i][j];
		}
	}

	cout << result << '\n';

	return 0;
}