#include <bits/stdc++.h>
using namespace std;

int r, c, k, w, x, y, t, result, arr[20][20], temper[20][20];
int dir[5][2] = { {0,0},{0,1},{0,-1},{-1,0},{1,0} };

int right_temper_dir[3][2] = { {-1, 1}, {0, 1}, {1, 1} };
int left_temper_dir[3][2] = { {-1, -1}, {0, -1}, {1, -1} };
int up_temper_dir[3][2] = { {-1, -1}, {-1, 0}, {-1, 1} };
int down_temper_dir[3][2] = { {1, -1}, {1, 0}, {1, 1} };

bool wall[20][20][4], visited[20][20];

vector<pair<int, int>> machine, examine;

void spread_temper(int y, int x, int d, int value) {
	if (value == 1) {
		visited[y][x] = true;
		temper[y][x] += value;

		return;
	}

	visited[y][x] = true;
	temper[y][x] += value;

	if (d == 1) {
		for (int i = 0; i < 3; i++) {
			int ny = y + right_temper_dir[i][0];
			int nx = x + right_temper_dir[i][1];

			if (ny < 0 || ny >= r || nx < 0 || nx >= c || visited[ny][nx])
				continue;

			if (i == 0) {
				if (wall[y][x][0] || wall[y - 1][x][2] || wall[y - 1][x][1] || wall[ny][nx][3])
					continue;
			}
			else if (i == 1) {
				if (wall[y][x][1] || wall[ny][nx][3])
					continue;
			}
			else {
				if (wall[y][x][2] || wall[y + 1][x][0] || wall[y + 1][x][1] || wall[ny][nx][3])
					continue;
			}

			spread_temper(ny, nx, d, value - 1);
		}
	}	// 오른쪽 방향
	else if (d == 2) {
		for (int i = 0; i < 3; i++) {
			int ny = y + left_temper_dir[i][0];
			int nx = x + left_temper_dir[i][1];

			if (ny < 0 || ny >= r || nx < 0 || nx >= c || visited[ny][nx])
				continue;
			if (i == 0) {
				if (wall[y][x][0] || wall[y - 1][x][2] || wall[y - 1][x][3] || wall[ny][nx][1])
					continue;
			}
			else if (i == 1) {
				if (wall[y][x][3] || wall[ny][nx][1])
					continue;
			}
			else {
				if (wall[y][x][2] || wall[y + 1][x][0] || wall[y + 1][x][3] || wall[ny][nx][1])
					continue;
			}

			spread_temper(ny, nx, d, value - 1);
		}
	}	// 왼쪽 방향
	else if (d == 3) {
		for (int i = 0; i < 3; i++) {
			int ny = y + up_temper_dir[i][0];
			int nx = x + up_temper_dir[i][1];

			if (ny < 0 || ny >= r || nx < 0 || nx >= c || visited[ny][nx])
				continue;

			if (i == 0) {
				if (wall[y][x][3] || wall[y][x - 1][1] || wall[y][x - 1][0] || wall[ny][nx][2])
					continue;
			}
			else if (i == 1) {
				if (wall[y][x][0] || wall[ny][nx][2])
					continue;
			}
			else {
				if (wall[y][x][1] || wall[y][x + 1][3] || wall[y][x + 1][0] || wall[ny][nx][2])
					continue;
			}

			spread_temper(ny, nx, d, value - 1);
		}
	}	// 위쪽 방향
	else {
		for (int i = 0; i < 3; i++) {
			int ny = y + down_temper_dir[i][0];
			int nx = x + down_temper_dir[i][1];

			if (ny < 0 || ny >= r || nx < 0 || nx >= c || visited[ny][nx])
				continue;

			if (i == 0) {
				if (wall[y][x][3] || wall[y][x - 1][1] || wall[y][x - 1][2] || wall[ny][nx][0])
					continue;
			}
			else if (i == 1) {
				if (wall[y][x][2] || wall[ny][nx][0])
					continue;
			}
			else {
				if (wall[y][x][1] || wall[y][x + 1][3] || wall[y][x + 1][2] || wall[ny][nx][0])
					continue;
			}

			spread_temper(ny, nx, d, value - 1);
		}
	}
}

void machine_on() {
	for (int i = 0; i < machine.size(); i++) {
		memset(visited, false, sizeof(visited));

		int y = machine[i].first;
		int x = machine[i].second;
		int d = arr[y][x];

		spread_temper(y + dir[d][0], x + dir[d][1], d, 5);
	}
}

void temper_control() {
	int temp[20][20] = { 0, };

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			int d = 0;
			
			for (int s = 0; s < 2; s++) {
				d = s == 0 ? 1 : 4;

				int ny = i + dir[d][0];
				int nx = j + dir[d][1];

				if (ny < 0 || ny >= r || nx < 0 || nx >= c)
					continue;

				if (d == 1) {
					if (wall[i][j][1] || wall[ny][nx][3])
						continue;
				}
				else {
					if (wall[i][j][2] || wall[ny][nx][0])
						continue;
				}

				int value = abs(temper[i][j] - temper[ny][nx]);
				value /= 4;

				if (temper[i][j] > temper[ny][nx]) {
					temp[i][j] -= value;
					temp[ny][nx] += value;
				}
				else {
					temp[i][j] += value;
					temp[ny][nx] -= value;
				}
			}
		}
	}

	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			temper[i][j] += temp[i][j];
		}
	}
}

void edge_temper_control() {
	for (int i = 0; i < r; i++) {
		if (temper[i][0]) temper[i][0]--;
		if (temper[i][c - 1]) temper[i][c - 1]--;
	}
	for (int j = 1; j < c - 1; j++) {
		if (temper[0][j]) temper[0][j]--;
		if (temper[r - 1][j]) temper[r - 1][j]--;
	}
}

bool examine_temper() {
	for (int i = 0; i < examine.size(); i++) {
		int y = examine[i].first, x = examine[i].second;

		if (temper[y][x] < k)
			return false;
	}

	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> r >> c >> k;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> arr[i][j];

			if (arr[i][j] >= 1 && arr[i][j] <= 4)	// 온풍기가 있는 칸
				machine.push_back({ i,j });
			else if (arr[i][j] == 5)	// 온도를 조사해야 하는 칸
				examine.push_back({ i,j });
		}
	}

	cin >> w;

	for (int i = 0; i < w; i++) {
		cin >> x >> y >> t;
		x--, y--;

		if (t == 0)
			wall[x][y][0] = wall[x - 1][y][2] = true;
		else
			wall[x][y][1] = wall[x][y + 1][3] = true;
	}

	while (1) {
		machine_on();
		temper_control();
		edge_temper_control();

		result++;
		if (result > 100) {
			result = 101;
			break;
		}

		if (examine_temper())
			break;
	}

	cout << result << '\n';

	return 0;
}