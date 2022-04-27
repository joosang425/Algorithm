#include <bits/stdc++.h>
using namespace std;

pair<int, int> tonado;
int n, result, arr[500][500];

int dir[4][10][3] = {
	// 위쪽
	{{-2, 0, 0},{0,-1,1},{0,1,1},{-1,-2,2},{-1,2,2},{-1,-1,7},{-1,1,7},{-2,-1,10}, {-2,1,10}, {-3,0,5}},
	// 왼쪽
	{{0, -2, 0},{-1,0,1},{1,0,1},{-2,-1,2},{2,-1,2},{-1,-1,7},{1,-1,7},{1,-2,10}, {-1,-2,10}, {0,-3,5}},
	// 아래쪽
	{{2, 0, 0},{0,-1,1},{0,1,1},{1,-2,2},{1,2,2},{1,-1,7},{1,1,7},{2,-1,10}, {2,1,10}, {3,0,5}},
	// 오른쪽
	{{0, 2, 0},{-1,0,1},{1,0,1},{-2,1,2},{2,1,2},{-1,1,7},{1,1,7},{-1,2,10}, {1,2,10},{0,3,5}}
};

// y, x: 현재 토네이도 위치
void land_record(int y, int x, int ny, int nx, int direction) {	
	int total_land = arr[ny][nx];

	for (int i = 1; i <= 9; i++) {
		int nny = y + dir[direction][i][0];
		int nnx = x + dir[direction][i][1];
		int value = dir[direction][i][2];
		int land = (arr[ny][nx] * value) / 100;

		if (nny < 0 || nny >= n || nnx < 0 || nnx >= n)
			result += land;
		else
			arr[nny][nnx] += land;

		total_land -= land;
	}

	int ay = y + dir[direction][0][0];
	int ax = x + dir[direction][0][1];

	if (ay < 0 || ay >= n || ax < 0 || ax >= n)
		result += total_land;
	else
		arr[ay][ax] += total_land;

	arr[ny][nx] = 0;
}

// y, x: 토네이도 시작 위치
// plus_y, plus_x: 더해줄 값
// cnt: 몇 번 가야하는지 체크하기

void tonado_move(int y, int x, int plus_y, int plus_x, int cnt, int direction) {
	int ny = 0, nx = 0;

	while (cnt--) {
		ny = y + plus_y;
		nx = x + plus_x;

		if (arr[ny][nx] != 0)
			land_record(y, x, ny, nx, direction);

		y = ny;
		x = nx;
	}

	tonado.first = ny, tonado.second = nx;
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

	tonado.first = n / 2;
	tonado.second = n / 2;

	int fd = 1, sd = 2;
	int fy = 0, fx = -1;
	int sy = 1, sx = 0;

	for (int i = 0; i < (n * 2 - 1) / 2; i++) {
		tonado_move(tonado.first, tonado.second, fy, fx, i + 1, fd);
		tonado_move(tonado.first, tonado.second, sy, sx, i + 1, sd);

		fy *= -1, fx *= -1, sy *= -1, sx *= -1;
		fd = (fd + 2) % 4;
		sd = (sd + 2) % 4;
	}

	tonado_move(tonado.first, tonado.second, 0, -1, n - 1, 1);

	cout << result << '\n';

	return 0;
}