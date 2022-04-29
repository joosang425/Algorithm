#include <bits/stdc++.h>
using namespace std;

bool visited[20][20];
int n, m, k, result, arr[20][20];

// 상, 우, 하, 좌
int dir[4][2] = { {-1,0}, {0,1}, {1, 0}, {0,-1} };
// 상, 후, 하, 전, 우, 좌
int dice[6] = { 1, 2, 6, 5, 3, 4 };

pair<pair<int,int>,int> dice_move(int y, int x, int direction) {
	int ny = y + dir[direction][0];
	int nx = x + dir[direction][1];

	if (ny < 0 || ny >= n || nx < 0 || nx >= m) {
		direction = (direction + 2) % 4;
		
		ny = y + dir[direction][0];
		nx = x + dir[direction][1];
	}

	if (direction == 0) {
		int temp = dice[0];
		dice[0] = dice[3];
		dice[3] = dice[2];
		dice[2] = dice[1];
		dice[1] = temp;
	}
	// 우
	else if (direction == 1) {
		int temp = dice[4];
		dice[4] = dice[0];
		dice[0] = dice[5];
		dice[5] = dice[2];
		dice[2] = temp;
	}
	// 하
	else if (direction == 2) {
		int temp = dice[2];
		dice[2] = dice[3];
		dice[3] = dice[0];
		dice[0] = dice[1];
		dice[1] = temp;
	}
	// 좌
	else {
		int temp = dice[5];
		dice[5] = dice[0];
		dice[0] = dice[4];
		dice[4] = dice[2];
		dice[2] = temp;
	}

	return { {ny, nx}, direction };
}

int bfs(int y, int x) {
	int cnt = 1;
	queue<pair<int, int>> q;
	q.push({ y,x });
	visited[y][x] = true;

	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dir[i][0];
			int nx = cx + dir[i][1];

			if (ny < 0 || ny >= n || nx < 0 || nx >= m || visited[ny][nx])
				continue;
			if (arr[ny][nx] != arr[y][x])
				continue;

			cnt++;
			visited[ny][nx] = true;
			q.push({ ny,nx });
		}
	}

	return cnt;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	int y = 0, x = 0, direction = 1;
	pair<pair<int, int>, int> cur;

	for (int i = 0; i < k; i++) {
		memset(visited, false, sizeof(visited));

		cur = dice_move(y, x, direction);

		y = cur.first.first;
		x = cur.first.second;
		direction = cur.second;

		int cnt = bfs(y, x);

		result += (cnt * arr[y][x]);

		if (dice[2] > arr[y][x])
			direction = (direction + 1) % 4;
		else if (dice[2] < arr[y][x])
			direction = (direction + 3) % 4;
	}

	cout << result << '\n';

	return 0;
}