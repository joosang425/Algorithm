#include <bits/stdc++.h>
using namespace std;

const int INF = 987654321;

int n, result;
char arr[50][50];

int visited[50][50][4];
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

pair<int, int> st, ed;
queue<pair<pair<int, int>, int>> q;

pair<int, int> chdir(int d) {
	if (d == 0 || d == 1)
		return { 2, 3 };
	else
		return { 0, 1 };
}

void bfs() {
	while (!q.empty()) {
		int y = q.front().first.first;
		int x = q.front().first.second;
		int d = q.front().second;
		q.pop();

		int ny = y + dir[d][0];
		int nx = x + dir[d][1];
		pair<int, int> nd = chdir(d);

		if (ny < 0 || ny >= n || nx < 0 || nx >= n)
			continue;

		if (arr[ny][nx] == '*')
			continue;
		else if (arr[ny][nx] == '!') {
			if (visited[ny][nx][d] > visited[y][x][d]) {
				visited[ny][nx][d] = visited[y][x][d];
				q.push({ {ny,nx},d });
			}

			if (visited[ny][nx][nd.first] > visited[y][x][d] + 1) {
				visited[ny][nx][nd.first] = visited[y][x][d] + 1;
				q.push({ {ny,nx}, nd.first });
			}

			if (visited[ny][nx][nd.second] > visited[y][x][d] + 1) {
				visited[ny][nx][nd.second] = visited[y][x][d] + 1;
				q.push({ {ny,nx},nd.second });
			}
		}
		else if (arr[ny][nx] == '.') {
			if (visited[ny][nx][d] > visited[y][x][d]) {
				visited[ny][nx][d] = visited[y][x][d];
				q.push({ {ny,nx},d });
			}
		}
		else if (arr[ny][nx] == '#') {
			if (visited[ny][nx][d] > visited[y][x][d])
				visited[ny][nx][d] = visited[y][x][d];
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	int cnt = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];

			if (arr[i][j] == '#') {
				if (cnt == 0) {
					st.first = i;
					st.second = j;
					cnt++;
				}
				else {
					ed.first = i;
					ed.second = j;
				}
			}

			visited[i][j][0] = visited[i][j][1] = visited[i][j][2] = visited[i][j][3] = INF;
		}
	}
	
	for (int i = 0; i < 4; i++) {
		q.push({ {st.first, st.second}, i });
		visited[st.first][st.second][i] = 0;
	}

	bfs();

	result = INF;
	for (int i = 0; i < 4; i++)
		result = min(result, visited[ed.first][ed.second][i]);

	cout << result << '\n';

	return 0;
}