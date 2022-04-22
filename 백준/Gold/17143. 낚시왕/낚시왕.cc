#include <bits/stdc++.h>
using namespace std;

int R, C, M, r, c, s, d, z, result, shark_cnt;

struct Shark {
	bool exist;
	int speed;
	int direction;
	int size;
};

Shark arr[101][101], temp[101][101];

// 1: 위, 2: 아래, 3: 오른쪽, 4: 왼쪽

void shark_move() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (arr[i][j].exist) {
				int move_cnt = arr[i][j].speed;
				int dir = arr[i][j].direction;
				int y = i;
				int x = j;

				while (move_cnt--) {
					if (dir == 1 && y == 1)
						dir = 2;
					else if (dir == 2 && y == R)
						dir = 1;
					else if (dir == 3 && x == C)
						dir = 4;
					else if (dir == 4 && x == 1)
						dir = 3;

					switch (dir) {
					case 1:
						y--;
						break;
					case 2:
						y++;
						break;
					case 3:
						x++;
						break;
					case 4:
						x--;
						break;
					}
				}

				if (temp[y][x].exist) {
					if (temp[y][x].size < arr[i][j].size) {
						temp[y][x].direction = dir;
						temp[y][x].size = arr[i][j].size;
						temp[y][x].speed = arr[i][j].speed;
					}
				}
				else {
					temp[y][x].exist = true;
					temp[y][x].direction = dir;
					temp[y][x].size = arr[i][j].size;
					temp[y][x].speed = arr[i][j].speed;
				}
			}
		}
	}

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			arr[i][j] = temp[i][j];

			if (temp[i][j].exist) {
				temp[i][j].exist = false;
				temp[i][j].direction = 0;
				temp[i][j].size = 0;
				temp[i][j].speed = 0;
			}
		}
	}
}

void solve(int cur) {
	if (cur == C)
		return;

	cur += 1;
	for (int i = 1; i <= R; i++) {
		if (arr[i][cur].exist) {
			result += arr[i][cur].size;

			arr[i][cur].exist = false;
			arr[i][cur].speed = 0;
			arr[i][cur].direction = 0;
			arr[i][cur].size = 0;

			shark_cnt--;
			break;
		}
	}
	if (shark_cnt != 0)
		shark_move();

	solve(cur);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> R >> C >> M;

	// r,c: 상어의 위치, s: 속력, d: 이동 방향, z: 크기
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> s >> d >> z;

		arr[r][c].exist = true;
		arr[r][c].speed = s;
		arr[r][c].direction = d;
		arr[r][c].size = z;
		shark_cnt++;
	}

	solve(0);

	cout << result << '\n';

	return 0;
}