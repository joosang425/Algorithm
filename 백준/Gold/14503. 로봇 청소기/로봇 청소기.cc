#include <bits/stdc++.h>
using namespace std;

int n, m, result, arr[50][50];
pair<pair<int, int>, int> robot;

// 북, 동, 남, 서
int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };

bool isEmpty(int y, int x, int d) {
	// 4번동안 반복하면서 빈 공간 찾기
	for (int i = 0; i < 4; i++) {
		d = (d + 3) % 4;	// +3한게 왼쪽 방향으로 회전한 것
		int ny = y + dir[d][0];
		int nx = x + dir[d][1];

		if (ny < 0 || ny >= n || nx < 0 || nx >= m)
			continue;

		if (!arr[ny][nx]) {
			robot.first.first = ny;
			robot.first.second = nx;
			robot.second = d;
			return true;
		}
	}

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	cin >> robot.first.first >> robot.first.second >> robot.second;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	while (1) {
		int y = robot.first.first;
		int x = robot.first.second;
		int d = robot.second;

		// 현재 위치를 청소
		if (!arr[y][x]) {
			arr[y][x] = 2;
			result++;
		}

		// 청소하지 않은 빈 공간을 찾지 못한 경우
		if (!isEmpty(y, x, d)) {
			int nd = (d + 2) % 4;
			int ny = y + dir[nd][0];
			int nx = x + dir[nd][1];

			// 뒤가 벽인 경우 반복문 종료
			if (arr[ny][nx] == 1)
				break;
			else {
				robot.first.first = ny;
				robot.first.second = nx;
				robot.second = d; // 기존 방향 유지한 채 저장
			}
		}
	}

	cout << result << '\n';

	return 0;
}
