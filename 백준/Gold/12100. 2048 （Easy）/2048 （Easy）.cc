#include <bits/stdc++.h>
using namespace std;

int n, arr[20][20], temp[20][20], result;
int selected[5];
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

// 조합을 위한 배열 복사 함수
void copy(int arr1[][20], int arr2[][20]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr1[i][j] = arr2[i][j];
		}
	}
}

// 격자 안에 있는 숫자를 옮기는 함수(방향의 따라 for문의 시작점이 틀림)
void board_move(int direction) {
	// 숫자를 한 번만 옮길 수 있는 조건을 처리하기 위한 배열
	bool visited[20][20] = { false, };
	
	// 상
	if (direction == 0) {
		// 격자 안에서 숫자를 옮기는 for문 
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!temp[i][j])
					continue;

				int y = i, x = j;

				bool flag = false;

				while (1) {
					y = y + dir[direction][0];
					x = x + dir[direction][1];

					if (y < 0)
						break;
					if (temp[y][x] == temp[i][j]) {
						// 같은 숫자로 인해 합쳐지는 경우 한 번뿐
						if (visited[y][x])
							break;
						else {
							flag = true;
							break;
						}
					}
					else if(temp[y][x] != 0 && (temp[y][x] != temp[i][j]))
						break;
				}

				if (flag) {
					// 숫자가 합쳐지는 경우를 기록하기 위해 true로 변경
					visited[y][x] = true;

					temp[y][x] *= 2;
					temp[i][j] = 0;
				}
			}
		}
		// 숫자를 합친 뒤 해당 direction 방향으로 숫자를 옮기는 for문 
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (!temp[i][j])
					continue;

				int y = i, x = j;

				while (1) {
					y = y + dir[direction][0];
					x = x + dir[direction][1];
					
					if (temp[y][x] != 0 || y < 0)
						break;
				}

				int num = temp[i][j];
				temp[i][j] = 0;

				temp[y + 1][x] = num;
			}
		}
	}
	// 하
	else if (direction == 1) {
		for (int i = n - 2; i >= 0; i--) {
			for (int j = 0; j < n; j++) {
				if (!temp[i][j])
					continue;

				int y = i, x = j;

				bool flag = false;

				while (1) {
					y = y + dir[direction][0];
					x = x + dir[direction][1];

					if (y >= n)
						break;
					if (temp[y][x] == temp[i][j]) {
						if (visited[y][x])
							break;
						else {
							flag = true;
							break;
						}
					}
					else if (temp[y][x] != 0 && (temp[y][x] != temp[i][j]))
						break;
				}

				if (flag) {
					visited[y][x] = true;

					temp[y][x] *= 2;
					temp[i][j] = 0;
				}
			}
		}
		for (int i = n - 2; i >= 0; i--) {
			for (int j = 0; j < n; j++) {
				if (!temp[i][j])
					continue;

				int y = i, x = j;

				while (1) {
					y = y + dir[direction][0];
					x = x + dir[direction][1];

					if (temp[y][x] != 0 || y > n - 1)
						break;
				}

				int num = temp[i][j];
				temp[i][j] = 0;

				temp[y - 1][x] = num;
			}
		}
	}
	// 좌
	else if (direction == 2) {
		for (int i = 0; i < n; i++) {
			for (int j = 1; j < n; j++) {
				if (!temp[i][j])
					continue;

				int y = i, x = j;

				bool flag = false;

				while (1) {
					y = y + dir[direction][0];
					x = x + dir[direction][1];

					if (x < 0)
						break;
					if (temp[y][x] == temp[i][j]) {
						if (visited[y][x])
							break;
						else {
							flag = true;
							break;
						}
					}
					else if (temp[y][x] != 0 && (temp[y][x] != temp[i][j]))
						break;
				}

				if (flag) {
					visited[y][x] = true;

					temp[y][x] *= 2;
					temp[i][j] = 0;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 1; j < n; j++) {
				if (!temp[i][j])
					continue;

				int y = i, x = j;

				while (1) {
					y = y + dir[direction][0];
					x = x + dir[direction][1];

					if (temp[y][x] != 0 || x < 0)
						break;
				}

				int num = temp[i][j];
				temp[i][j] = 0;

				temp[y][x + 1] = num;
			}
		}
	}
	// 우
	else {
		for (int i = 0; i < n; i++) {
			for (int j = n - 2; j >= 0; j--) {
				if (!temp[i][j])
					continue;

				int y = i, x = j;

				bool flag = false;

				while (1) {
					y = y + dir[direction][0];
					x = x + dir[direction][1];

					if (x >= n)
						break;
					if (temp[y][x] == temp[i][j]) {
						if (visited[y][x])
							break;
						else {
							flag = true;
							break;
						}
					}
					else if (temp[y][x] != 0 && (temp[y][x] != temp[i][j]))
						break;
				}

				if (flag) {
					visited[y][x] = true;

					temp[y][x] *= 2;
					temp[i][j] = 0;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = n - 2; j >= 0; j--) {
				if (!temp[i][j])
					continue;

				int y = i, x = j;

				while (1) {
					y = y + dir[direction][0];
					x = x + dir[direction][1];

					if (temp[y][x] != 0 || x > n - 1)
						break;
				}

				int num = temp[i][j];
				temp[i][j] = 0;

				temp[y][x - 1] = num;
			}
		}
	}
}

// 모든 방향의 조합을 만드는 함수
void solve() {
	for (int i = 0; i < 5; i++) {
		int direction = selected[i];

		board_move(direction);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result = max(result, temp[i][j]);
		}
	}
}

void dfs(int cnt) { 
	if (cnt == 5) {
		copy(temp, arr);
		solve();

		return;
	}

	for (int i = 0; i < 4; i++) {
		selected[cnt] = i;
		dfs(cnt + 1);
	}
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

	dfs(0);

	cout << result << '\n';

	return 0;
}
