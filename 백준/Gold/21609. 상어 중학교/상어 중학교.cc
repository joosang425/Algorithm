#include <bits/stdc++.h>
using namespace std;

int n, m, result, arr[20][20], temp_arr[20][20];
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

bool visited[20][20], temp_visited[20][20];
vector<pair<pair<int, int>, pair<int, int>>> candidate;

void copy(bool arr1[][20], bool arr2[][20]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr1[i][j] = arr2[i][j];
		}
	}
}

pair<int,int> bfs(int y, int x) {
	int cnt = 1, rainbow_cnt = 0;

	queue<pair<int, int>> q;
	q.push({ y,x });
	visited[y][x] = true;

	while (!q.empty()) {
		int cy = q.front().first;
		int cx = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dir[i][0];
			int nx = cx + dir[i][1];

			if (ny < 0 || ny >= n || nx < 0 || nx >= n || visited[ny][nx])
				continue;
			if (arr[ny][nx] == -1 || arr[ny][nx] == -2)
				continue;
			if (arr[ny][nx] != 0 && (arr[y][x] != arr[ny][nx]))
				continue;

			if (arr[ny][nx] == 0) {
				cnt++;
				rainbow_cnt++;
				visited[ny][nx] = true;
				q.push({ ny,nx });
			}	// 무지개 블록인 경우 
			else {
				cnt++;
				visited[ny][nx] = true;
				temp_visited[ny][nx] = true;	// 무지개 블록은 어떤 번호든 갈 수 있는 칸이기 때문에 temp_visited 배열을 이용한다.
				q.push({ ny,nx });
			}	// 일반 블록인 경우
		}
	}

	// 무지개 블록은 모두 갈 수 있기 때문에 썼던 블록을 false로 변경 -> 이것을 하지 않으면 다음 bfs 때 같은 무지개 블록을 쓸 수 없어진다.
	copy(visited, temp_visited);

	return { cnt, rainbow_cnt };
}

// 조건을 위한 함수
bool cmp(pair<pair<int, int>, pair<int, int>> a, pair<pair<int, int>, pair<int, int>> b) {
	if (a.first.second == b.first.second) {
		if (a.second.first == b.second.first)
			return a.second.second > b.second.second;

		return a.second.first > b.second.first;
	}

	return a.first.second > b.first.second;
}

// 크기가 가장 큰 블록을 찾는다.
void find_large_group() {
	int large_group = 0;

	// bfs를 통해 현재 같은 번호를 가진 칸의 갯수 구하기
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// 현재 칸이 검은색이거나 무지개이거나 아무것도 없는 칸이거나 방문했던 칸이면 진행 X
			if (arr[i][j] != -1 && arr[i][j] != 0 && arr[i][j] != -2 && !visited[i][j]) {
				pair<int, int> value = bfs(i, j);
				int y = i, x = j;

				// 칸의 갯수가 2보다 작을 경우 조건에 따라 후보군에 넣을 필요가 없음
				if (value.first < 2)
					continue;

				// 현재 가장 큰 크기의 블록 그룹보다 클 경우 후보군 벡터를 초기화 시킨 뒤 가장 큰 블록 그룹으로 최신화 
				if (value.first > large_group) {
					candidate.clear();

					large_group = value.first;
					candidate.push_back({ {value.first, value.second},{y, x} });
				}
				// 같다면 후보군 벡터에 삽입
				else if (value.first == large_group)
					candidate.push_back({ {value.first, value.second},{y, x} });
			}
		}
	}

	// 후보군이 2개 이상일 경우 sort함수를 통해 조건에 따라 정렬
	if (candidate.size() > 1)
		sort(candidate.begin(), candidate.end(), cmp);
}

// 블록 제거
void remove_block(int y, int x) {
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

			if (ny < 0 || ny >= n || nx < 0 || nx >= n || visited[ny][nx] || arr[ny][nx] == -1)
				continue;
			if (arr[ny][nx] != 0 && (arr[y][x] != arr[ny][nx]))
				continue;

			cnt++;
			visited[ny][nx] = true;
			q.push({ ny, nx });
		}
	}

	// 제거된 블록의 갯수^2을 결과값에 더 해준다.
	result += (cnt * cnt);

	// 제거될 블록을 -2로 변경
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (visited[i][j])
				arr[i][j] = -2;
		}
	}
}

// 중력 작용
void fall_block() {
	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] == -1 || arr[i][j] == -2 || arr[i + 1][j] != -2)
				continue;

			int y = i + 1;
			while (1) {
				if (y == n || arr[y][j] != -2)
					break;

				y++;
			}

			arr[y - 1][j] = arr[i][j];
			arr[i][j] = -2;
		}
	}
}

// 격자 90도 반시계 방향으로 회전
void rotate_arr() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			temp_arr[i][j] = arr[j][n - i - 1];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = temp_arr[i][j];
		}
	}
}

void solve() {
	while (1) {
		candidate.clear();
		memset(visited, false, sizeof(visited));
		memset(temp_visited, false, sizeof(temp_visited));

		find_large_group();

		// 후보군 블록 그룹이 없을 때 반복문 종료
		if (candidate.empty())
			break;

		memset(visited, false, sizeof(visited));

		remove_block(candidate[0].second.first, candidate[0].second.second);
		fall_block();
		rotate_arr();
		fall_block();
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	solve();

	cout << result << '\n';

	return 0;
}