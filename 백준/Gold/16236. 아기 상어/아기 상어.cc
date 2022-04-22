#include <bits/stdc++.h>
using namespace std;

int n, result, arr[20][20];
bool visited[20][20];

int dir[4][2] = { {0, 1},{0, -1},{1,0},{-1,0} };
pair<pair<int, int>, pair<int, int>> shark;

vector<pair<int, pair<int, int>>> candidate;

void bfs(int y, int x) {
	queue<pair<pair<int, int>, int>> q;
	
	q.push({ {y,x}, 0 });
	visited[y][x] = true;

	while (!q.empty()) {
		int cy = q.front().first.first;
		int cx = q.front().first.second;
		int cnt = q.front().second;
		q.pop();

		// 현재 위치에 물고기가 있으면서 그 물고기의 크기가 상어의 크기보다 작은 경우 vector에 삽입 -> 크기가 같으면 지나갈 수는 있지만 못 먹는다는 조건 주의
		if (arr[cy][cx] != 0 && shark.second.first > arr[cy][cx]) {
			visited[cy][cx] = true;
			candidate.push_back({ cnt,{cy,cx} });
			continue;
		}

		for (int i = 0; i < 4; i++) {
			int ny = cy + dir[i][0];
			int nx = cx + dir[i][1];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n || visited[ny][nx])
				continue;
			if (arr[ny][nx] > shark.second.first)
				continue;

			q.push({ {ny,nx}, cnt + 1 });
			visited[ny][nx] = true;
		}
	}
}

bool com(pair<int, pair<int, int>> a, pair<int, pair<int, int>> b) {
	if (a.first == b.first) {
		if (a.second.first == b.second.first)
			return a.second.second < b.second.second;

		return a.second.first < b.second.first;
	}

	return a.first < b.first;
}

void shark_move() {
	// 조건에 맞게 정렬
	sort(candidate.begin(), candidate.end(), com);

	int cnt = candidate[0].first;
	int y = candidate[0].second.first;
	int x = candidate[0].second.second;

	// 현재 이동 횟수 만큼 더해줌 
	result += cnt;

	// 먹은 물고기는 0으로 초기화
	arr[y][x] = 0;

	// 아기 상어가 먹이를 먹은 횟수 1 증가
	shark.second.second++;
	// 먹이를 먹은 횟수가 아기 상어의 크기가 되면 크기 1 증가
	if (shark.second.second == shark.second.first) {
		shark.second.first++;
		shark.second.second = 0;
	}

	shark.first.first = y;
	shark.first.second = x;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];

			// 아기 상어 위치, 크기, 먹은 횟수 초기화
			if (arr[i][j] == 9) {
				shark.first.first = i;
				shark.first.second = j;
				shark.second.first = 2;
				shark.second.second = 0;
				arr[i][j] = 0;
			}
		}
	}

	// 아기 상어가 먹을 물고기가 없을 때까지 진행
	while (1) {
		memset(visited, false, sizeof(visited));
		candidate.clear();

		bfs(shark.first.first, shark.first.second);

		if (candidate.empty())
			break;

		shark_move();
	}

	cout << result << '\n';

	return 0;
}