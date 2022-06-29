#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321;

int w, h, result, dist[21][21];
char arr[21][21];

bool checked[11];
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

pair<int, int> machine;
vector<pair<int, int>> dirty;

int bfs(int sy, int sx, int ey, int ex) {
	bool visited[21][21] = { false, };

	queue<pair<pair<int, int>, int>> q;
	q.push({ {sy, sx}, 0 });
	visited[sy][sx] = true;

	while (!q.empty()) {
		int y = q.front().first.first;
		int x = q.front().first.second;
		int cnt = q.front().second;
		q.pop();

		if (y == ey && x == ex)
			return cnt;

		for (int i = 0; i < 4; i++) {
			int ny = y + dir[i][0];
			int nx = x + dir[i][1];

			if (ny < 0 || ny >= h || nx < 0 || nx >= w)
				continue;
			if (visited[ny][nx] || arr[ny][nx] == 'x')
				continue;

			visited[ny][nx] = true;
			q.push({ {ny,nx}, cnt + 1 });
		}
	}

	return INF;
}

void dfs(int cur, string str) {
	if (dirty.size() == str.length()) {
		if (dist[0][str[0] - '0'] == INF)
			return;

		int temp = dist[0][str[0] - '0'];

		for (int i = 0; i < str.length() - 1; i++) {
			int first = str[i] - '0';
			int second = str[i + 1] - '0';

			if (dist[first][second] == INF)
				return;

			temp += dist[first][second];
		}

		result = min(result, temp);
		return;
	}

	for (int i = 1; i <= dirty.size(); i++) {
		if (!checked[i]) {
			checked[i] = true;
			dfs(i, str + to_string(i));
			checked[i] = false;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	while (1) {
		memset(dist, 0, sizeof(dist));
		memset(checked, false, sizeof(checked));
		result = INF;
		dirty.clear();

		cin >> w >> h;

		if (w == 0 && h == 0)
			break;

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> arr[i][j];

				if (arr[i][j] == 'o') {
					machine.first = i;
					machine.second = j;
				}
				else if (arr[i][j] == '*')
					dirty.push_back({ i,j });
			}
		}

		for (int i = 0; i < dirty.size(); i++) {
			int temp = bfs(machine.first, machine.second, dirty[i].first, dirty[i].second);

			dist[0][i + 1] = temp;
			dist[i + 1][0] = temp;
		}

		for (int i = 0; i < dirty.size(); i++) {
			for (int j = 0; j < dirty.size(); j++) {
				if (i == j)
					continue;

				int temp = bfs(dirty[i].first, dirty[i].second, dirty[j].first, dirty[j].second);

				dist[i + 1][j + 1] = temp;
				dist[j + 1][i + 1] = temp;
			}
		}

		dfs(1, "");

		if (result == INF)
			cout << -1 << '\n';
		else
			cout << result << '\n';
	}

	return 0;
}