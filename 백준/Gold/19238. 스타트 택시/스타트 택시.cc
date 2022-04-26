#include <bits/stdc++.h>
using namespace std;

struct info {
	int sy;
	int sx;
	int dy;
	int dx;
	bool isArrive;
};

int n, m, gas, arr[20][20];
int d[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

bool visited[20][20];
info passenger[400];
pair<int, int> taxi;

vector<pair<pair<int, int>, pair<int, int>>> candidate;

int bfs(int sy, int sx, int dy, int dx) {
	queue<pair<pair<int, int>, int>> q;
	q.push({ {sy,sx},0 });
	visited[sy][sx] = true;

	while (!q.empty()) {
		int cy = q.front().first.first;
		int cx = q.front().first.second;
		int cnt = q.front().second;
		q.pop();

		if (cnt > gas)
			continue;
		if (cy == dy && cx == dx)
			return cnt;

		for (int i = 0; i < 4; i++) {
			int ny = cy + d[i][0];
			int nx = cx + d[i][1];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n || visited[ny][nx] || arr[ny][nx])
				continue;

			visited[ny][nx] = true;
			q.push({ {ny,nx}, cnt + 1 });
		}
	}

	return -1;
}

bool cmp(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b) {
	if (a.first.first == b.first.first) {
		if (a.second.first == b.second.first)
			return a.second.second < b.second.second;

		return a.second.first < b.second.first;
	}

	return a.first.first < b.first.first;
}

pair<int,int> solve() {
	// 태울 수 있는 거리인 승객 저장
	for (int i = 0; i < m; i++) {
		memset(visited, false, sizeof(visited));

		if (passenger[i].isArrive)
			continue;

		int dis = bfs(taxi.first, taxi.second, passenger[i].sy, passenger[i].sx);

		if (dis != -1)
			candidate.push_back({ {dis, i},{passenger[i].sy, passenger[i].sx} });
	}

	if (candidate.empty())
		return { -1, -1 };

	sort(candidate.begin(), candidate.end(), cmp);

	return { candidate[0].first.first, candidate[0].first.second };
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> gas;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	cin >> taxi.first >> taxi.second;
	taxi.first--, taxi.second--;

	int sy, sx, dy, dx;

	for (int i = 0; i < m; i++) {
		cin >> sy >> sx >> dy >> dx;
		sy--, sx--, dy--, dx--;

		passenger[i] = { sy,sx,dy,dx, false };
	}

	for (int i = 0; i < m; i++) {
		candidate.clear();

		// 현재 택시 위치에서 갈 수 있는 곳 저장
		pair<int,int> next = solve();

		// 현재 택시 위치에서 정해진 연료로 갈 수 없는 경우
		// 목적지까지 가야하므로 같아도 종료
		if (next.first >= gas || next.second == -1) {
			gas = -1;
			break;
		}
		else
			gas -= next.first;

		taxi.first = passenger[next.second].sy, taxi.second = passenger[next.second].sx;

		memset(visited, false, sizeof(visited));
		// 현재 위치에서 목적지까지의 거리와 위치 구하기
		int des_dis = bfs(taxi.first, taxi.second, passenger[next.second].dy, passenger[next.second].dx);

		// 목적지까지 정해진 연료로 갈 수 없는 경우
		// or 목적지로 갈 수 없는 경우
		// 같은 경우에는 도착 후 충전이 가능하므로 클 때만 종료
		if (des_dis > gas || des_dis == -1) {
			gas = -1;
			break;
		}
		else
			gas += des_dis;
	
		// 택시 위치를 변경 및 승객 도착 기록
		taxi.first = passenger[next.second].dy;
		taxi.second = passenger[next.second].dx;
		passenger[next.second].isArrive = true;
	}

	cout << gas << '\n';

	return 0;
}
