#include <bits/stdc++.h>
using namespace std;

int MAP[51][51];
int n, m, ry, rx, rd, cnt;

int dir[4][2] = { {-1,0}, {0,1},{1,0},{0,-1} };

int solve(int y, int x, int d) {
	if (!MAP[y][x]) {
		MAP[y][x] = 2;
		cnt++;
	}

	for (int i = 0; i < 4; i++) {
		int nd = (d + 3 - i) % 4;
		int ny = y + dir[nd][0];
		int nx = x + dir[nd][1];

		if (ny < 0 || ny >= n || nx < 0 || nx >= m)
			continue;

		if (!MAP[ny][nx])
			solve(ny, nx, nd);
	}

	int nd = (d + 2) % 4;
	int ny = y + dir[nd][0];
	int nx = x + dir[nd][1];

	if (MAP[ny][nx] == 1) {
		cout << cnt << '\n';
		exit(0);
	}
	else
		solve(ny, nx, d);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	cin >> ry >> rx >> rd;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> MAP[i][j];
		}
	}

	solve(ry, rx, rd);

	return 0;
}