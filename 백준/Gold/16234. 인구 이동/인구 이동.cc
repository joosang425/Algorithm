#include <bits/stdc++.h>
using namespace std;

int n, l, r, day, MAP[51][51];
bool visited[51][51], check = true;

int dir[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };

void solve(int y, int x) {
	queue<pair<int, int>> q, tq;
	tq.push({ y,x });
	q.push({ y,x });
	visited[y][x] = true;
	int sum = 0;
	int cnt = 0;

	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		sum += MAP[cy][cx];
		cnt += 1;
		for (int i = 0; i < 4; i++) {
			int ny = cy + dir[i][0];
			int nx = cx + dir[i][1];
			int temp = abs(MAP[cy][cx] - MAP[ny][nx]);

			if (temp < l || temp > r)
				continue;
			if (ny < 0 || ny >= n || nx < 0 || nx >= n)
				continue;
			if (visited[ny][nx])
				continue;


			q.push({ ny,nx });
			tq.push({ ny,nx });
			visited[ny][nx] = true;
		}
	}

	int value = sum / cnt;
	while (!tq.empty()) {
		MAP[tq.front().first][tq.front().second] = value;
		tq.pop();
	}
}

bool cancombi(int y, int x) {
	for (int i = 0; i < 4; i++) {
		int ny = y + dir[i][0];
		int nx = x + dir[i][1];
		int temp = abs(MAP[y][x] - MAP[ny][nx]);

		if (ny < 0 || ny >= n || nx < 0 || nx >= n)
			continue;
		if (temp < l || temp > r)
			continue;

		return true;
	}

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> l >> r;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
		}
	}

	while (check) {
		check = false;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!visited[i][j] && cancombi(i, j)) {
					solve(i, j);
					check = true;
				}
			}
		}

		if (check)
			day++;

		memset(visited, false, sizeof(visited));
	}

	cout << day << '\n';

	return 0;
}