#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int arr[51][51];
bool visit[51][51];

int T, M, N, K;
int x, y;
int dir_y[4] = { -1,1,0,0 };
int dir_x[4] = { 0,0,-1,1 };

bool IsCheck(int y, int x) {
	if (y < 0 || y >= N || x < 0 || x >= M)
		return false;

	return true;
}

void Dfs(int y, int x) {
	visit[y][x] = true;

	for (int i = 0; i < 4; i++) {
		int next_y = y + dir_y[i];
		int next_x = x + dir_x[i];

		if (arr[next_y][next_x] && !visit[next_y][next_x] && IsCheck(next_y, next_x))
			Dfs(next_y, next_x);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);	cout.tie(NULL);

	cin >> T;

	while (T--) {
		cin >> M >> N >> K;

		for (int i = 0; i < K; i++) {
			cin >> x >> y;
			arr[y][x] = 1;
		}

		int re = 0;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (arr[i][j]) {
					if (!visit[i][j]) {
						re++;
						Dfs(i, j);
					}
				}
			}
		}

		cout << re << '\n';
		memset(arr, 0, sizeof(arr));
		memset(visit, false, sizeof(visit));
	}

	return 0;
}