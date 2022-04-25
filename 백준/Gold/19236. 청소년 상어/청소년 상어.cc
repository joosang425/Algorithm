#include <bits/stdc++.h>
using namespace std;

struct info {
	int y;
	int x;
	int dir;
};

info fish[16];
int a, b, result, arr[4][4];

int d[8][2] = { {-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1} };

void copy(int arr1[][4], int arr2[][4], info fish1[], info fish2[]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			arr1[i][j] = arr2[i][j];
		}
	}

	for (int i = 0; i < 16; i++)
		fish1[i] = fish2[i];
}

void solve(int arr[][4], info fish[], int shark_y, int shark_x, int sum) {
	// 백 트래킹을 위한 함수 
	int temp_arr[4][4];
	info temp_fish[16];

	copy(temp_arr, arr, temp_fish, fish);

	// 물고기 먹기
	int fish_num = temp_arr[shark_y][shark_x];
	int shark_dir = temp_fish[fish_num].dir;

	temp_arr[shark_y][shark_x] = -1;
	temp_fish[fish_num].y = -1;
	temp_fish[fish_num].x = -1;
	temp_fish[fish_num].dir = -1;

	sum += fish_num + 1;
	result = max(result, sum);

	// 물고기 이동
	for (int i = 0; i < 16; i++) {
		// y가 -1이면 현재 물고기가 없다는 뜻
		if (temp_fish[i].y == -1)
			continue;

		int cy = temp_fish[i].y;
		int cx = temp_fish[i].x;
		int cd = temp_fish[i].dir;
		
		int ny = cy + d[cd][0];
		int nx = cx + d[cd][1];
		int nd = cd;

		// 이동할 수 있는 방향 찾기
		while (ny < 0 || ny >= 4 || nx < 0 || nx >= 4 || (ny == shark_y && nx == shark_x)) {
			nd = (nd + 1) % 8;
			ny = cy + d[nd][0];
			nx = cx + d[nd][1];
		}

		// 현재 위치에 다른 물고기가 위치한 경우
		if (temp_arr[ny][nx] != -1) {
			int target = temp_arr[ny][nx];

			temp_fish[target].y = cy;
			temp_fish[target].x = cx;

			temp_fish[i].y = ny;
			temp_fish[i].x = nx;
			temp_fish[i].dir = nd;

			temp_arr[cy][cx] = target;
			temp_arr[ny][nx] = i;
		}
		else {
			temp_fish[i].y = ny;
			temp_fish[i].x = nx;
			temp_fish[i].dir = nd;

			temp_arr[ny][nx] = i;
			temp_arr[cy][cx] = -1;
		}
	}

	// 상어 이동
	for (int i = 1; i < 4; i++) {
		int ny = shark_y + d[shark_dir][0] * i;
		int nx = shark_x + d[shark_dir][1] * i;

		if (ny < 0 || ny >= 4 || nx < 0 || nx >= 4)
			break;

		// 물고기가 있을 때만 이동
		if (temp_arr[ny][nx] != -1)
			solve(temp_arr, temp_fish, ny, nx, sum);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> a >> b;

			a--, b--;

			arr[i][j] = a;
			fish[a] = { i, j, b };
		}
	}

	solve(arr, fish, 0, 0, 0);

	cout << result << '\n';

	return 0;
}