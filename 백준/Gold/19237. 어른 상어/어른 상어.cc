#include <bits/stdc++.h>
using namespace std;

struct shark {
	int y;
	int x;
	int dir;
	bool isExist;
};

struct smell {
	int value;
	int num;
};

smell arr[20][20];
shark info[401];
int result, cany, canx, cand;
int n, m, k;

int direction[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int dir_info[401][4][4];

void spray() {
	for (int i = 1; i <= m; i++) {
		if (!info[i].isExist)
			continue;

		int y = info[i].y;
		int x = info[i].x;

		arr[y][x].num = i;
		arr[y][x].value = k;
	}
}

void smell_down() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j].num != 0) {
				arr[i][j].value--;

				if (arr[i][j].value == 0)
					arr[i][j].num = 0;
			}
		}
	}
}

void shark_move() {
	vector<pair<int, pair<int, int>>> v;

	for (int i = 1; i <= m; i++) {
		if (!info[i].isExist)
			continue;

		int y = info[i].y;
		int x = info[i].x;
		int dir = info[i].dir;

		bool isFind = false;

		for (int j = 0; j < 4; j++) {
			int num = dir_info[i][dir][j];

			int ny = y + direction[num][0];
			int nx = x + direction[num][1];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n)
				continue;
			if (arr[ny][nx].value != 0)
				continue;

			isFind = true;

			if (arr[ny][nx].num != 0) {
				// 어떤 상어가 있는 경우

				// 현재 있는 상어보다 인덱스가 큰 경우
				if (arr[ny][nx].num < i)
					info[i].isExist = false;
				// 현재 있는 상어보다 인덱스가 작은 경우 바꿔줌
				else {
					info[arr[ny][nx].num].isExist = false;

					arr[ny][nx].num = i;
					info[i].y = ny;
					info[i].x = nx;
					info[i].dir = num;
				}
			}
			else {
				// 아무 상어도 없는 경우
				arr[ny][nx].num = i;
				info[i].y = ny;
				info[i].x = nx;
				info[i].dir = num;
			}

			break;
		}

		if (!isFind) {
			for (int j = 0; j < 4; j++) {
				int num = dir_info[i][dir][j];

				int ny = y + direction[num][0];
				int nx = x + direction[num][1];

				if (ny < 0 || ny >= n || nx < 0 || nx >= n)
					continue;

				if (arr[ny][nx].num == i) {
					info[i].y = ny;
					info[i].x = nx;
					info[i].dir = num;

					break;
				}
			}
		}
	}

	smell_down();
	spray();
}

bool isCheck() {
	for (int i = 2; i <= m; i++) {
		if (info[i].isExist) {
			return true;
		}
	}

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j].num;

			if (arr[i][j].num != 0) {
				int x = arr[i][j].num;

				arr[i][j].value = k;

				info[x].y = i;
				info[x].x = j;
				info[x].isExist = true;
			}
		}
	}

	// 1: 상, 2: 하, 3: 좌, 4: 우
	int num;
	for (int i = 1; i <= m; i++) {
		cin >> num;

		num--;

		info[i].dir = num;
	}

	// 상, 하, 좌, 우
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 4; j++) {
			for (int z = 0; z < 4; z++) {
				cin >> num;

				num--;

				dir_info[i + 1][j][z] = num;
			}
		}
	}

	while (isCheck()) {
		result++;
		if (result > 1000) {
			result = -1;
			break;
		}

		shark_move();
	}

	cout << result << '\n';

	return 0;
}