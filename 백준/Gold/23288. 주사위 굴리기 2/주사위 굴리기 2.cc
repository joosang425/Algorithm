#include <bits/stdc++.h>
using namespace std;

int n, m, k, d, result, arr[20][20];
pair<int, int> dice_pos;

// 뒤, 위, 앞, 밑, 오, 왼
int dice[6] = { 2, 1, 5, 6, 3, 4 };
int dir[4][2] = { {0, 1}, {1,0},{0,-1},{-1,0} };
bool visited[20][20];

void dice_move(int d) {
	// 동
	if (d == 0) {
		int temp = dice[1];
		dice[1] = dice[5];
		dice[5] = dice[3];
		dice[3] = dice[4];
		dice[4] = temp;
	}
	// 남
	else if (d == 1) {
		int temp = dice[1];
		dice[1] = dice[0];
		dice[0] = dice[3];
		dice[3] = dice[2];
		dice[2] = temp;
	}
	// 서
	else if (d == 2) {
		int temp = dice[1];
		dice[1] = dice[4];
		dice[4] = dice[3];
		dice[3] = dice[5];
		dice[5] = temp;
	}
	// 북
	else {
		int temp = dice[1];
		dice[1] = dice[2];
		dice[2] = dice[3];
		dice[3] = dice[0];
		dice[0] = temp;
	}
}

int bfs(int y, int x) {
	queue<pair<int, int>> q;
	
	int cnt = 1;
	q.push({ y,x });
	visited[y][x] = true;

	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dir[i][0];
			int nx = cx + dir[i][1];

			if (ny < 0 || ny >= n || nx < 0 || nx >= m || visited[ny][nx] || (arr[y][x] != arr[ny][nx]))
				continue;

			q.push({ ny,nx });
			visited[ny][nx] = true;
			cnt++;
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

	dice_pos.first = 0, dice_pos.second = 0;
	d = 0;

	for (int i = 0; i < k; i++) {
		memset(visited, false, sizeof(visited));

		int ny = dice_pos.first + dir[d][0];
		int nx = dice_pos.second + dir[d][1];

		// 이동 방향에 칸이 없다면 방향을 반대로 한 뒤 한 칸 굴러간다.
		if (ny < 0 || ny >= n || nx < 0 || nx >= m) {
			d = (d + 2) % 4;

			ny = dice_pos.first + dir[d][0];
			nx = dice_pos.second + dir[d][1];
		}

		// 주사위 굴리기
		dice_pos.first = ny, dice_pos.second = nx;
		dice_move(d);

		// 도착한 칸에 대한 점수 획득
		int cnt = bfs(dice_pos.first, dice_pos.second);
		result += arr[dice_pos.first][dice_pos.second] * cnt;

		// 이동 방향 결정
		int value = arr[dice_pos.first][dice_pos.second];
		int num = dice[3];
		
		if (num > value)
			d = (d + 1) % 4;
		else if (num < value)
			d = (d + 3) % 4;
	}

	cout << result << '\n';

	return 0;
}
