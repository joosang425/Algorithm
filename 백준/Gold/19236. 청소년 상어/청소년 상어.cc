#include <bits/stdc++.h>
using namespace std;

struct fish {
	int y;
	int x;
	int dir;
	bool exist;
};

int a, b, result, arr[4][4];
int direction[9][2] = { {0,0}, {-1,0}, {-1,-1}, {0,-1}, {1,-1},{1,0},{1,1},{0,1},{-1,1} };

fish f[20];

void exchange_fish(int idx, int nidx) {
	fish temp = f[idx];
	f[idx].y = f[nidx].y;
	f[idx].x = f[nidx].x;
	f[nidx].y = temp.y;
	f[nidx].x = temp.x;
}

void fish_move() {
	for (int i = 1; i <= 16; i++) {
		if (!f[i].exist)
			continue;

		int y = f[i].y;
		int x = f[i].x;
		int dir = f[i].dir;

		int ny = y + direction[dir][0];
		int nx = x + direction[dir][1];

		bool flag = false;

		if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4) {
			if (arr[ny][nx] == 0) {
				flag = true;
				f[i].y = ny, f[i].x = nx;
				arr[ny][nx] = i;
				arr[y][x] = 0;
			}
			else if(arr[ny][nx] != -1){
				flag = true;
				exchange_fish(i, arr[ny][nx]);
				swap(arr[y][x], arr[ny][nx]);
			}
		}

		if (!flag) {
			int ndir = dir + 1;
			if (ndir == 9)
				ndir = 1;

			int ny = y + direction[ndir][0];
			int nx = x + direction[ndir][1];

			while (ndir != dir) {
				if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4) {
					if (arr[ny][nx] == 0) {
						f[i].y = ny;
						f[i].x = nx;
						arr[ny][nx] = i;
						arr[y][x] = 0;
						f[i].dir = ndir;
						break;
					}
					else if (arr[ny][nx] != -1) {
						exchange_fish(i, arr[ny][nx]);
						swap(arr[y][x], arr[ny][nx]);
						f[i].dir = ndir;
						break;
					}
				}

				ndir++;
				if (ndir == 9)
					ndir = 1;
				ny = y + direction[ndir][0];
				nx = x + direction[ndir][1];
			}
		}
	}
}

void Copy(int arr1[][4], int arr2[][4], fish f1[], fish f2[]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			arr1[i][j] = arr2[i][j];
		}
	}

	for (int i = 1; i <= 16; i++)
		f1[i] = f2[i];
}

void setting(int y, int x, int ny, int nx, int idx, bool check) {
	if (check) {
		arr[y][x] = 0;
		arr[ny][nx] = -1;
		f[idx].exist = false;
	}
	else {
		arr[y][x] = -1;
		arr[ny][nx] = idx;
		f[idx].exist = true;
	}
}

void solve(int y, int x, int dir, int sum) {
	result = max(result, sum);

	int temp_arr[4][4];
	fish temp_f[20];
	Copy(temp_arr, arr, temp_f, f);

	fish_move();

	for (int i = 1; i <= 3; i++) {
		int ny = y + direction[dir][0] * i;
		int nx = x + direction[dir][1] * i;

		if (ny >= 0 && ny < 4 && nx >= 0 && nx < 4) {
			if (arr[ny][nx] == 0)
				continue;

			int candi = arr[ny][nx];
			int ndir = f[candi].dir;

			setting(y, x, ny, nx, candi, true);
			solve(ny, nx, ndir, sum + candi);
			setting(y, x, ny, nx, candi, false);
		}
		else
			break;
	}

	Copy(arr, temp_arr, f, temp_f);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cin >> a >> b;

			arr[i][j] = a;
			f[a] = { i, j, b, true };
		}
	}

	int cur = arr[0][0];
	int dir = f[cur].dir;
	f[cur].exist = false;
	arr[0][0] = -1;

	solve(0, 0, dir, cur);

	cout << result;

	return 0;
}