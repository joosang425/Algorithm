#include <bits/stdc++.h>
using namespace std;

int n, q, l, result, large, Size, arr[64][64], temp[64][64];
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

bool visited[64][64];

void copy(int arr1[][64], int arr2[][64]) {
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
			arr1[i][j] = arr2[i][j];
		}
	}
}

void ice_move(int y, int x, int board_size) {
	int cnt = x + board_size - 1;

	for (int i = y; i < y + board_size; i++) {
		int idx = y;

		for (int j = x; j < x + board_size; j++) {
			temp[idx++][cnt] = arr[i][j];
		}

		cnt--;
	}
}

void melt_ice() {
	copy(temp, arr);

	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			if (arr[i][j] == 0)
				continue;
			else {
				int cnt = 0;

				for (int t = 0; t < 4; t++) {
					int ny = i + dir[t][0];
					int nx = j + dir[t][1];

					if (ny >= 0 && ny < Size && nx >= 0 && nx < Size && arr[ny][nx] != 0)
						cnt++;
				}

				if (cnt < 3)
					temp[i][j]--;
			}
		}
	}

	copy(arr, temp);
}

int bfs(int y, int x) {
	int cnt = 1;

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

			if (ny < 0 || ny >= Size || nx < 0 || nx >= Size)
				continue;
			if (visited[ny][nx] || arr[ny][nx] == 0)
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

	Size = pow(2, n);
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			cin >> arr[i][j];
		}
	}

	while (q--) {
		cin >> l;

		int board_size = pow(2, l);
		int board = pow(4, l);
		int y = 0, x = 0;
		int total = Size * Size / board;

		while (total--) {
			ice_move(y, x, board_size);

			x += board_size;

			if (x == Size) {
				x = 0;
				y += board_size;
			}

		}

		copy(arr, temp);

		melt_ice();
	}

	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++) {
			result += arr[i][j];

			if (arr[i][j] != 0 && !visited[i][j])
				large = max(large, bfs(i, j));
		}
	}

	cout << result << '\n';
	cout << large;

	return 0;
}