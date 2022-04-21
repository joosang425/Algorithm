#include <bits/stdc++.h>
using namespace std;

int n, l, r, result, arr[51][51], temp[51][51];
bool visited[51][51];

int dir[4][2] = { {-1,0},{0,1},{0,-1},{1,0} };

int bfs(int y, int x) {
	int cnt = 1, sum = arr[y][x];
	
	// 큐를 2개 만든다 (bfs 진행을 위한 큐, 인구이동하는 칸 저장하는 큐)
	queue<pair<int, int>> q, tq;
	tq.push({ y,x });
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

			int value = abs(arr[cy][cx] - arr[ny][nx]);
			
			// 조건을 만족할 시 이동 및 큐에 저장
			if (value >= l && value <= r) {
				tq.push({ ny,nx });
				q.push({ ny,nx });
				cnt++;
				sum += arr[ny][nx];
				visited[ny][nx] = true;
			}
		}
	}

	// 저장해놓은 칸의 값을 변경
	int value = sum / cnt;
	while (!tq.empty()) {
		arr[tq.front().first][tq.front().second] = value;
		tq.pop();
	}

	// 인구이동했는지 확인을 위한 return 값
	return cnt;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> l >> r;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	while (1) {
		memset(visited, false, sizeof(visited));
		bool flag = false;
		
		// bfs를 진행하면서 인구 이동가능한 지역 확인하기
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!visited[i][j]) {
					// bfs를 진행한 뒤 return값이 1보다 작다는 것은 이동할 수 있는 지역이 없다는 뜻이므로 1보다 크면 인구이동 했다고 설정
					if (bfs(i, j) > 1)
						flag = true;
				}
			}
		}
		
		// 인구이동이 없으면 반복문 
		if (!flag)
			break;

		result++;
	}

	cout << result << '\n';

	return 0;
}
