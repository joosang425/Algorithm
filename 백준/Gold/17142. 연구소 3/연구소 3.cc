#include <bits/stdc++.h>
using namespace std;

int n, m, empty_cnt, result = 987654321, arr[50][50], temp[50][50];
bool selected[10];

int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };

vector<pair<int, int>> virus;

void bfs(queue<pair<int, int>> q) {
	int nvirus = 0, cnt = 0;

	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dir[i][0];
			int nx = cx + dir[i][1];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n)
				continue;
			// 벽인 경우나 활성 바이러스인 경우는 진행x 
			if (arr[ny][nx] == 1 || temp[ny][nx] != -1)
				continue;

			temp[ny][nx] = temp[cy][cx] + 1;
			// 바이러스가 퍼질 수 있는 칸을 센다
			if (arr[ny][nx] == 0) {
				nvirus++;
				cnt = temp[ny][nx];
			}

			q.push({ ny,nx });
		}
	}

	// 바이러스가 다 퍼질 수 있는 경우
	if (empty_cnt == nvirus)
		result = min(result, cnt);
}

// 조합
void dfs(int idx, int cnt) {
	if (cnt == m) {
		memset(temp, -1, sizeof(temp));

		queue<pair<int, int>> q;

		for (int i = 0; i < virus.size(); i++) {
			if (selected[i]) {
				// 활성 바이러스로 변경
				temp[virus[i].first][virus[i].second] = 0;
				q.push({ virus[i].first, virus[i].second });
			}
		}

		bfs(q);
		return;
	}

	for (int i = idx; i < virus.size(); i++) {
		if (selected[i])
			continue;

		selected[i] = true;
		dfs(i, cnt + 1);
		selected[i] = false;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];

			if (arr[i][j] == 2)
				virus.push_back({ i,j });
			else if (arr[i][j] == 0)
				empty_cnt++;
		}
	}

	dfs(0, 0);

	if (result == 987654321)
		cout << -1 << '\n';
	else
		cout << result << '\n';

	return 0;
}
