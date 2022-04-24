#include <bits/stdc++.h>
using namespace std;

int n, result = 987654321, arr[20][20], space[20][20];

int dir[4][2] = { {-1,0}, {0,1},{1,0},{0,-1} };

void dfs(int y, int x, int value) {
	if (y < 0 || y >= n || x < 0 || x >= n)
		return;
	if (space[y][x] != 0)
		return;

	space[y][x] = value;

	dfs(y - 1, x, value);
	dfs(y + 1, x, value);
	dfs(y, x - 1, value);
	dfs(y, x + 1, value);
 }

int find() {
	for (int y = 0; y <= n - 3; y++) {
		for (int x = 0; x <= n - 2; x++) {
			for (int d1 = 1; y + d1 <= n - 2 && x - d1 >= 0; d1++) {
				for (int d2 = 1; y + d1 + d2 < n && x + d2 < n; d2++) {
					memset(space, 0, sizeof(space));

					// 5번 선거구 경계선 기록하기
					for (int d = 0; d <= d1; d++) {
						space[y + d][x - d] = 5;
						space[y + d2 + d][x + d2 - d] = 5;
					}

					for (int d = 0; d <= d2; d++) {
						space[y + d][x + d] = 5;
						space[y + d1 + d][x - d1 + d] = 5;
					}

					// 각 선거구 기록
					for (int i = y - 1; i >= 0; i--)
						space[i][x] = 1;
					for (int j = x + d2 + 1; j < n; j++)
						space[y + d2][j] = 2;
					for (int j = x - d1 - 1; j >= 0; j--)
						space[y + d1][j] = 3;
					for (int i = y + d1 + d2 + 1; i < n; i++)
						space[i][x - d1 + d2] = 4;

					// dfs를 이용하여 선거구 번호 채우기
					dfs(0, 0, 1);
					dfs(0, n - 1, 2);
					dfs(n - 1, 0, 3);
					dfs(n - 1, n - 1, 4);

					int temp[6] = { 0, };

					for (int i = 0; i < n; i++) {
						for (int j = 0; j < n; j++) {
							temp[space[i][j]] += arr[i][j];
						}
					}

					temp[5] += temp[0];
					int large = 0, low = 987654321;

					for (int i = 1; i <= 5; i++) {
						large = max(large, temp[i]);
						low = min(low, temp[i]);
					}

					result = min(result, large - low);
				}
			}
		}
	}

	return result;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	cout << find() << '\n';

	return 0;
}
