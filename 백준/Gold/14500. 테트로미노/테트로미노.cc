#include <bits/stdc++.h>
using namespace std;

bool visited[500][500];
int n, m, arr[500][500], result;

int dir[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };
vector<pair<int, int>> v;

void bfs(int y, int x, int cnt) {
	// 크기가 4가 되면 도형이 완성
	if (cnt == 4) {
		int sum = 0;

		for (int i = 0; i < v.size(); i++)
			sum += arr[v[i].first][v[i].second];

		result = max(result, sum);
		return;
	}

	// 상, 하, 좌, 우로 움직이면서 도형을 만들어줌
	for (int i = 0; i < 4; i++) {
		int ny = y + dir[i][0];
		int nx = x + dir[i][1];

		if (ny < 0 || ny >= n || nx < 0 || nx >= m || visited[ny][nx])
			continue;

		v.push_back({ ny,nx });
		visited[ny][nx] = true;
		bfs(ny, nx, cnt + 1);
		visited[ny][nx] = false;
		v.pop_back();
	}

	// ㅗ 모형은 만들어질 수 없기 때문에 if문으로 진행
	// ㅏ
	if (y + 1 < n && y + 2 < n && x + 1 < m) {
		int sum = 0;

		sum += arr[y][x];
		sum += arr[y + 1][x];
		sum += arr[y + 2][x];
		sum += arr[y + 1][x + 1];

		result = max(result, sum);
	}
	// ㅓ
	if (y + 1 < n && y + 2 < n && x - 1 >= 0) {
		int sum = 0;

		sum += arr[y][x];
		sum += arr[y + 1][x];
		sum += arr[y + 2][x];
		sum += arr[y + 1][x - 1];

		result = max(result, sum);
	}
	// ㅜ
	if (x + 1 < m && x + 2 < m && y + 1 < n) {
		int sum = 0;

		sum += arr[y][x];
		sum += arr[y][x + 1];
		sum += arr[y][x + 2];
		sum += arr[y + 1][x + 1];

		result = max(result, sum);
	}
	// ㅗ
	if (x + 1 < m && x + 2 < m && y - 1 >= 0) {
		int sum = 0;

		sum += arr[y][x];
		sum += arr[y][x + 1];
		sum += arr[y][x + 2];
		sum += arr[y - 1][x + 1];

		result = max(result, sum);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	// 격자만큼 for문을 돌리면서 진행
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j] = true;
			v.push_back({ i, j });
			bfs(i, j, 1);
			v.pop_back();
			visited[i][j] = false;
		}
	}

	cout << result << '\n';

	return 0;
}