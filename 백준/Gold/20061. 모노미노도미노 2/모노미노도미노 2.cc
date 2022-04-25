#include <bits/stdc++.h>
using namespace std;

int n, t, x, y, result;

int blue_arr[4][6];
int green_arr[6][4];

// 1: 1X1, 2: 1X2, 3: 2X1 

void move(int type, int idx) {
	// 파란색
	if (type == 0) {
		for (int j = idx; j > 0; j--) {
			blue_arr[0][j] = blue_arr[0][j - 1];
			blue_arr[1][j] = blue_arr[1][j - 1];
			blue_arr[2][j] = blue_arr[2][j - 1];
			blue_arr[3][j] = blue_arr[3][j - 1];
		}

		blue_arr[0][0] = blue_arr[1][0] = blue_arr[2][0] = blue_arr[3][0] = 0;
	}
	// 초록색
	else {
		for (int i = idx; i > 0; i--) {
			green_arr[i][0] = green_arr[i - 1][0];
			green_arr[i][1] = green_arr[i - 1][1];
			green_arr[i][2] = green_arr[i - 1][2];
			green_arr[i][3] = green_arr[i - 1][3];
		}

		green_arr[0][0] = green_arr[0][1] = green_arr[0][2] = green_arr[0][3] = 0;
	}
}

void full_check() {
	// 파란색
	for (int j = 0; j < 6; j++) {
		if (blue_arr[0][j] && blue_arr[1][j] && blue_arr[2][j] && blue_arr[3][j]) {
			blue_arr[0][j] = blue_arr[1][j] = blue_arr[2][j] = blue_arr[3][j] = 0;
			result++;
			move(0, j);
		}
	}

	// 초록색
	for (int i = 0; i < 6; i++) {
		if (green_arr[i][0] && green_arr[i][1] && green_arr[i][2] && green_arr[i][3]) {
			green_arr[i][0] = green_arr[i][1] = green_arr[i][2] = green_arr[i][3] = 0;
			result++;
			move(1, i);
		}
	}
}

void remove_block(int type, int cnt) {
	// 파란색
	if (type == 0) {
		for (int i = 0; i < cnt; i++) {
			blue_arr[0][5] = blue_arr[1][5] = blue_arr[2][5] = blue_arr[3][5] = 0;
			move(0, 5);
		}
	}

	// 초록색
	else {
		for (int i = 0; i < cnt; i++) {
			green_arr[5][0] = green_arr[5][1] = green_arr[5][2] = green_arr[5][3] = 0;
			move(1, 5);
		}
	}
}

void soft_check() {
	// 파란색 
	int blue_cnt = 0;
	if (blue_arr[0][0] || blue_arr[1][0] || blue_arr[2][0] || blue_arr[3][0])
		blue_cnt++;
	if (blue_arr[0][1] || blue_arr[1][1] || blue_arr[2][1] || blue_arr[3][1])
		blue_cnt++;
	
	if (blue_cnt != 0)
		remove_block(0, blue_cnt);

	// 초록색
	int green_cnt = 0;
	if (green_arr[0][0] || green_arr[0][1] || green_arr[0][2] || green_arr[0][3])
		green_cnt++;
	if (green_arr[1][0] || green_arr[1][1] || green_arr[1][2] || green_arr[1][3])
		green_cnt++;

	if (green_cnt != 0)
		remove_block(1, green_cnt);
}

void put_block(int type, int y, int x) {
	if (type == 1) {
		// 파란색
		int j;
		for (j = 0; j < 6; j++) {
			if (blue_arr[y][j] == 1)
				break;
		}

		if (j == 6)
			blue_arr[y][5] = 1;
		else
			blue_arr[y][j - 1] = 1;

		// 초록색
		int i;
		for (i = 0; i < 6; i++) {
			if (green_arr[i][x] == 1)
				break;
		}

		if (i == 6)
			green_arr[5][x] = 1;
		else
			green_arr[i - 1][x] = 1;
	}
	else if (type == 2) {
		// 파란색
		int j;
		for (j = 1; j < 6; j++) {
			if (blue_arr[y][j] == 1)
				break;
		}

		if (j == 6)
			blue_arr[y][5] = blue_arr[y][4] = 1;
		else
			blue_arr[y][j - 1] = blue_arr[y][j - 2] = 1;

		// 초록색
		int i;
		for (i = 0; i < 6; i++) {
			if (green_arr[i][x] == 1 || green_arr[i][x + 1] == 1)
				break;
		}

		if (i == 6)
			green_arr[5][x] = green_arr[5][x + 1] = 1;
		else
			green_arr[i - 1][x] = green_arr[i - 1][x + 1] = 1;
	}
	else {
		// 파란색
		int j;
		for (j = 0; j < 6; j++) {
			if (blue_arr[y][j] == 1 || blue_arr[y + 1][j] == 1)
				break;
		}

		if (j == 6)
			blue_arr[y][5] = blue_arr[y + 1][5] = 1;
		else
			blue_arr[y][j - 1] = blue_arr[y + 1][j - 1] = 1;

		// 초록색
		int i;
		for (i = 1; i < 6; i++) {
			if (green_arr[i][x] == 1)
				break;
		}

		if (i == 6)
			green_arr[5][x] = green_arr[4][x] = 1;
		else
			green_arr[i - 1][x] = green_arr[i - 2][x] = 1;
	}

	full_check();
	soft_check();
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t >> x >> y;

		put_block(t, x, y);
	}

	cout << result << '\n';
	
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 6; j++) {
			if (blue_arr[i][j] != 0)
				cnt++;
		}
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 4; j++) {
			if (green_arr[i][j] != 0)
				cnt++;
		}
	}

	cout << cnt << '\n';

	return 0;
}