#include <bits/stdc++.h>
using namespace std;

struct passenger {
	int sy;
	int sx;
	int dy;
	int dx;
	bool isArrive;
};

passenger p[400];
int n, m, oil, distant, arr[20][20];
pair<int, int> taxi;

bool cant;
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

int bfs(int y, int x, int dy, int dx) {
	bool visited[20][20] = { false, };

	queue<pair<pair<int, int>, int>> q;
	q.push({ {y,x}, 0 });
	visited[y][x] = true;

	while (!q.empty()) {
		int cy = q.front().first.first;
		int cx = q.front().first.second;
		int cnt = q.front().second;
		q.pop();

		if (cy == dy && cx == dx)
			return cnt;

		for (int i = 0; i < 4; i++) {
			int ny = cy + dir[i][0];
			int nx = cx + dir[i][1];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n)
				continue;
			if (visited[ny][nx] || arr[ny][nx])
				continue;

			q.push({ {ny,nx},cnt + 1 });
			visited[ny][nx] = true;
		}
	}

	return -1;
}

bool cmp(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b) {
	if (a.first.second == b.first.second) {
		if (a.second.first == b.second.first)
			return a.second.second < b.second.second;

		return a.second.first < b.second.first;
	}

	return a.first.second < b.first.second;
}

int solve() {
	vector<pair<pair<int, int>, pair<int, int>>> v;

	for (int i = 0; i < m; i++) {
		if (p[i].isArrive)
			continue;

		int re = bfs(taxi.first, taxi.second, p[i].sy, p[i].sx);
		if (re == -1) {
			cant = true;
			return -1;
		}

		v.push_back({ {i, re}, {p[i].sy, p[i].sx} });
	}

	if (v.empty())
		return -1;

	sort(v.begin(), v.end(), cmp);

	distant = v[0].first.second;
	return v[0].first.first;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	// n: 격자의 크기, m: 승객의 수, oil: 초기 연료
	cin >> n >> m >> oil;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	// 택시의 위치
	cin >> taxi.first >> taxi.second;

	taxi.first--;
	taxi.second--;

	// arr 배열에 각 승객의 출발지의 목적지 표시 
	int sy, sx, dy, dx;
	for (int i = 0; i < m; i++) {
		cin >> sy >> sx >> dy >> dx;

		sy--;
		sx--;
		dy--;
		dx--;

		p[i].sy = sy, p[i].sx = sx, p[i].dy = dy, p[i].dx = dx;
		p[i].isArrive = false;
	}

	// next: 현재 택시에서 가장 가까운 거리의 승객
	// distant: 승객과의 거리
	while (1) {
		int next = solve();

		if (next == -1) {
			if (cant)
				oil = -1;

			break;
		}

		if (oil - distant < 0) {
			oil = -1;
			break;
		}
		else
			oil -= distant;
		
		taxi.first = p[next].sy, taxi.second = p[next].sx;

		int des_distant = bfs(taxi.first, taxi.second, p[next].dy, p[next].dx);
		if (des_distant == -1) {
			oil = -1;
			break;
		}

		if (oil - des_distant < 0) {
			oil = -1;
			break;
		}
		else {
			taxi.first = p[next].dy, taxi.second = p[next].dx;
			oil += des_distant;
			p[next].isArrive = true;
		}
	}

	cout << oil << '\n';

	return 0;
}