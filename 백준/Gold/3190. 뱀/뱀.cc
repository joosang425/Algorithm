#include <bits/stdc++.h>
using namespace std;

// 상, 하, 좌, 우
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
int n, k, y, x, l, arr[100][100];

char trans[10001];
deque<pair<int, int>> snake;

int trans_dir(int idx, int num) {
	char cur = trans[idx];

	if (cur == 'L') {
		if (num == 0) return 2;
		else if (num == 1) return 3;
		else if (num == 2) return 1;
		else return 0;
	}
	else {
		if (num == 0) return 3;
		else if (num == 1) return 2;
		else if (num == 2) return 0;
		else return 1;
	}
}

bool snake_move(int direction) {
	// 현재 뱀의 머리의 위치
	int hy = snake.front().first;
	int hx = snake.front().second;

	// 뱀의 머리를 다음 칸에 위치
	int ny = hy + dir[direction][0];
	int nx = hx + dir[direction][1];

	// 벽 또는 자기 자신의 몸과 부딪힌 경우
	if (ny < 0 || ny >= n || nx < 0 || nx >= n || arr[ny][nx] == 1)
		return false;

	// 현재 위치에 사과가 있는 경우
	if (arr[ny][nx] == 2) {
		arr[ny][nx] = 1;
		snake.push_front({ ny, nx });
	}
	else {
		arr[ny][nx] = 1;

		snake.push_front({ ny,nx });

		arr[snake.back().first][snake.back().second] = 0;
		snake.pop_back();
	}

	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	cin >> k;

	for (int i = 0; i < k; i++) {
		cin >> y >> x;

		arr[y - 1][x - 1] = 2;
	}

	cin >> l;

	memset(trans, '0', sizeof(trans));

	int a;
	char c;
	for (int i = 0; i < l; i++) {
		cin >> a >> c;

		trans[a] = c;
	}

	// 초기 위치 저장
	snake.push_back({ 0,0 });
	arr[0][0] = 1;
	int d = 3;

	int result;
	for (result = 0;; result++) {
		// 현재 시간에서 방향을 바꿔야 하는 경우
		if (trans[result] != '0') {
			d = trans_dir(result, d);

			if (!snake_move(d))
				break;
		}
		else {
			if (!snake_move(d))
				break;
		}
	}

	cout << result + 1 << '\n';

	return 0;
}