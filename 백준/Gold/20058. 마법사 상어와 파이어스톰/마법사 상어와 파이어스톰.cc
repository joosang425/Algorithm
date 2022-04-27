#include <bits/stdc++.h>
using namespace std;

int n, q, l, total_ice, large, arr[64][64], temp[64][64];

bool visited[64][64], check[64][64];
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int arr_size;

void arr_rotate(int divide) {
	memset(temp, 0, sizeof(temp));

	int plus = pow(2, divide);

	for (int i = 0; i < arr_size; i += plus) {
		for (int j = 0; j < arr_size; j += plus) {
			for (int y = 0; y < plus; y++) {
				for (int x = 0; x < plus; x++) {
					temp[y][x] = arr[i + plus - 1 - x][j + y];
				}
			}

			for (int y = 0; y < plus; y++) {
				for (int x = 0; x < plus; x++) {
					arr[i + y][j + x] = temp[y][x];
				}
			}
		}
	}
}

void ice_melt() {
	memset(check, false, sizeof(check));

	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			if (!arr[i][j])
				continue;

			int cnt = 0;
			for (int d = 0; d < 4; d++) {
				int y = i + dir[d][0];
				int x = j + dir[d][1];

				if (y < 0 || y >= arr_size || x < 0 || x >= arr_size)
					continue;
				if (arr[y][x] > 0)
					cnt++;
			}

			if (cnt < 3)
				check[i][j] = true;
		}
	}

	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			if (check[i][j])
				arr[i][j]--;
		}
	}
}

int bfs(int y, int x) {
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

			if (ny < 0 || ny >= arr_size || nx < 0 || nx >= arr_size || visited[ny][nx] || !arr[ny][nx])
				continue;

			cnt++;
			q.push({ ny,nx });
			visited[ny][nx] = true;
		}
	}

	return cnt;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> q;
	for (int i = 0; i < pow(2, n); i++) {
		for (int j = 0; j < pow(2, n); j++) {
			cin >> arr[i][j];
		}
	}

	arr_size = pow(2, n);

	for (int i = 0; i < q; i++) {
		cin >> l;

		arr_rotate(l);
		ice_melt();
	}

	for (int i = 0; i < arr_size; i++) {
		for (int j = 0; j < arr_size; j++) {
			total_ice += arr[i][j];

			if (arr[i][j] && !visited[i][j])
				large = max(large, bfs(i, j));
		}
	}

	cout << total_ice << '\n';
	cout << large << '\n';

	return 0;
}
