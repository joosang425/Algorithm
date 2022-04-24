#include <bits/stdc++.h>
using namespace std;

int n, m, result = 987654321, MAP[50][50], temp[50][50];
bool isVirus[10];

int empty_cnt;

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

vector<pair<int, int>> v;

void bfs(queue<pair<int,int>> q) {
	int Nvirus = 0;
	int cnt = 0;

	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dir[i][0];
			int nx = cx + dir[i][1];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n)
				continue;
			if (MAP[ny][nx] == 1 || temp[ny][nx] != -1)
				continue;

			temp[ny][nx] = temp[cy][cx] + 1;
			if (MAP[ny][nx] == 0) {
				Nvirus++;
				cnt = temp[ny][nx];
			}

			q.push({ ny,nx });
		}
	}

	if (empty_cnt == Nvirus)
		result = min(result, cnt);
}

void solve(int idx, int virus) {
	if (virus == m) {
		memset(temp, -1, sizeof(temp));
		queue<pair<int, int>> q;

		for (int i = 0; i < v.size(); i++) {
			if (isVirus[i]) {
				q.push({ v[i].first, v[i].second });
			
				temp[v[i].first][v[i].second] = 0;
			}
		}

		bfs(q);
		return;
	}

	for (int i = idx; i < v.size(); i++) {
		if (!isVirus[i]) {
			isVirus[i] = true;
			solve(i + 1, virus + 1);
			isVirus[i] = false;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];

			if (MAP[i][j] == 2)
				v.push_back({ i,j });
			else if (MAP[i][j] == 0)
				empty_cnt++;
		}
	}

	solve(0, 0);

	if (result == 987654321)
		cout << -1 << '\n';
	else
		cout << result << '\n';

	return 0;
}