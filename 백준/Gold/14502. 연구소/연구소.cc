#include <bits/stdc++.h>
using namespace std;

int n, m, arr[8][8], temp[8][8], result;
bool selected[8][8];
vector<pair<int, int>> virus;

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

void copy(int arr1[][8], int arr2[][8]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr1[i][j] = arr2[i][j];
		}
	}
}

void bfs() {
	bool visited[8][8] = { false, };

	for (int i = 0; i < virus.size(); i++) {
		queue<pair<int, int>> q;

		int y = virus[i].first;
		int x = virus[i].second;

		q.push({ y,x });
		visited[y][x] = true;

		while (!q.empty()) {
			int cy = q.front().first;
			int cx = q.front().second;
			q.pop();

			for (int i = 0; i < 4; i++) {
				int ny = cy + dir[i][0];
				int nx = cx + dir[i][1];

				if (ny < 0 || ny >= n || nx < 0 || nx >= m || visited[ny][nx] || arr[ny][nx] != 0)
					continue;

				q.push({ ny,nx });
				visited[ny][nx] = true;
				temp[ny][nx] = 2;
			}
		}
	}
}

void dfs(int cnt) {
	if (cnt == 3) {
		copy(temp, arr);
		bfs();

		int cnt = 0;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (temp[i][j] == 0)
					cnt++;
			}
		}

		result = max(result, cnt);

		return;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (selected[i][j] || arr[i][j] != 0)
				continue;

			selected[i][j] = true;
			arr[i][j] = 1;
			dfs(cnt + 1);
			arr[i][j] = 0;
			selected[i][j] = false;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];

			if (arr[i][j] == 2)
				virus.push_back({ i ,j });
		}
	}

	dfs(0);

	cout << result << '\n';

	return 0;
}
