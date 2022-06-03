#include <bits/stdc++.h>
using namespace std;

int w, h, num;
char arr[100][100];
int visited[100][100];

pair<int, int> st, ed;

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

int bfs(int y, int x) {
	queue<pair<pair<int, int>, pair<int, int>>> q;
	
	for (int i = 0; i < 4; i++)
		q.push({ {y,x},{0, i} });

	visited[y][x] = 0;

	while (!q.empty()) {
		int cy = q.front().first.first;
		int cx = q.front().first.second;
		int cnt = q.front().second.first;
		int d = q.front().second.second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int ny = cy + dir[i][0];
			int nx = cx + dir[i][1];
			int ncnt = cnt;

			if (ny < 0 || ny >= h || nx < 0 || nx >= w || arr[ny][nx] == '*')
				continue;
			if (d != i)
				ncnt++;
			// 다음 위치까지 가는 데 필요한 거울의 갯수가 더 작으면 큐에 삽입
			if (visited[ny][nx] >= ncnt) {
				visited[ny][nx] = ncnt;
				q.push({ {ny,nx},{ncnt, i} });
			}
		}
	}

	return visited[ed.first][ed.second];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> w >> h;

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> arr[i][j];

			if (arr[i][j] == 'C') {
				if (num == 0) {
					st.first = i;
					st.second = j;

					num++;
				}
				else {
					ed.first = i;
					ed.second = j;
				}
			}

			visited[i][j] = 987654321;
		}
	}

	cout << bfs(st.first, st.second) << '\n';

	return 0;
}