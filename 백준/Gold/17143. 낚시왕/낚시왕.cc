#include <bits/stdc++.h>
using namespace std;

struct shark {
	int speed;
	int direction;
	int size;
	bool live;
};

shark arr[101][101], temp[101][101];
int R, C, m, r, c, s, d, z, result;
int dir[5][2] = { {0, 0}, {-1,0},{1,0},{0,1},{0, -1} };

void find_shark(int col) {
	// 현재 열에서 상어를 찾으면 false로 표시
	for (int i = 1; i <= R; i++) {
		if (arr[i][col].live) {
			result += arr[i][col].size;
			arr[i][col].live = false;

			break;
		}
	}
}

void move_shark() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (arr[i][j].live) {
				int y = i;
				int x = j;
				int speed = arr[i][j].speed;
				int direction = arr[i][j].direction;

				// 상어 이동 
				while (speed--) {
					// 끝에 온 경우 방향을 바꿔줌
					if (direction == 1 && y == 1)
						direction = 2;
					else if (direction == 2 && y == R)
						direction = 1;
					else if (direction == 3 && x == C)
						direction = 4;
					else if (direction == 4 && x == 1)
						direction = 3;

					y += dir[direction][0];
					x += dir[direction][1];
				}

				// 현재 위치에 이미 상어가 있는 경우 크기를 비교
				if (temp[y][x].live) {
					if (temp[y][x].size < arr[i][j].size) {
						temp[y][x].size = arr[i][j].size;
						temp[y][x].speed = arr[i][j].speed;
						temp[y][x].direction = direction;
					}
				}
				else {
					temp[y][x].size = arr[i][j].size;
					temp[y][x].speed = arr[i][j].speed;
					temp[y][x].direction = direction;
					temp[y][x].live = true;
				}
			}
		}
	}

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			arr[i][j] = temp[i][j];

			if (temp[i][j].live) {
				temp[i][j].live = false;
				temp[i][j].direction = 0;
				temp[i][j].speed = 0;
				temp[i][j].size = 0;
			}
		}
	}
}



int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> R >> C >> m;
	for (int i = 0; i < m; i++) {
		cin >> r >> c >> s >> d >> z;

		if (d == 1 || d == 2)
			arr[r][c].speed = s % ((R - 1) * 2);
		else if (d == 3 || d == 4) 
			arr[r][c].speed = s % ((C - 1) * 2);

		arr[r][c].direction = d;
		arr[r][c].size = z;
		arr[r][c].live = true;
	}

	// 열 만큼 for문 진행
	for (int i = 1; i <= C; i++) {
		find_shark(i);
		move_shark();
	}

	cout << result << '\n';

	return 0;
}