#include <bits/stdc++.h>
using namespace std;

int MAP[21][21], n, m, y, x, k;
int v[6];

void solve(int num) {
	if (num == 1) {
		if (x + 1 >= m)
			return;

		int temp = v[0];

		v[0] = v[5];
		v[5] = v[2];
		v[2] = v[4];
		v[4] = temp;

		x += 1;

		if (MAP[y][x] == 0)
			MAP[y][x] = v[2];
		else {
			v[2] = MAP[y][x];
			MAP[y][x] = 0;
		}

		cout << v[0] << '\n';
	}
	else if (num == 2) {
		if (x - 1 < 0)
			return;

		int temp = v[0];

		v[0] = v[4];
		v[4] = v[2];
		v[2] = v[5];
		v[5] = temp;

		x -= 1;

		if (MAP[y][x] == 0)
			MAP[y][x] = v[2];
		else {
			v[2] = MAP[y][x];
			MAP[y][x] = 0;
		}

		cout << v[0] << '\n';
	}
	else if (num == 3) {
		if (y - 1 < 0)
			return;

		int temp = v[0];

		v[0] = v[1];
		v[1] = v[2];
		v[2] = v[3];
		v[3] = temp;

		y -= 1;

		if (MAP[y][x] == 0)
			MAP[y][x] = v[2];
		else {
			v[2] = MAP[y][x];
			MAP[y][x] = 0;
		}

		cout << v[0] << '\n';
	}
	else {
		if (y + 1 >= n)
			return;

		int temp = v[0];

		v[0] = v[3];
		v[3] = v[2];
		v[2] = v[1];
		v[1] = temp;

		y += 1;

		if (MAP[y][x] == 0)
			MAP[y][x] = v[2];
		else {
			v[2] = MAP[y][x];
			MAP[y][x] = 0;
		}

		cout << v[0] << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> y >> x >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> MAP[i][j];
		}
	}

	//v[0] = 0;
	//v[4] = 0;

	int num;
	for (int i = 0; i < k; i++) {
		cin >> num;

		solve(num);
	}

	return 0;
}