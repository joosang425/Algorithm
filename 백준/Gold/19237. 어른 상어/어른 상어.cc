#include <bits/stdc++.h>
using namespace std;

struct info {
	int y;
	int x;
	int dir;
	bool live;
};

int d[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

// shark_arr: 상어의 현재 위치를 저장하는 배열, shark_dir: 상어의 이동 방향별로 우선 순위 저장하는 배열
int n, m, k, result, shark_arr[20][20], shark_dir[401][4][4];
// 현재 격자에 남아 있는 상어의 냄새와 번호
pair<int, int> smell[20][20];

// 상어의 정보 저장
info shark[401];

// 1번 상어만 남아있는지 확인하는 함수
bool live_check() {
	if (!shark[1].live)
		return false;

	for (int i = 2; i <= m; i++) {
		if (shark[i].live)
			return false;
	}

	return true;
}

// 상어 이동
void shark_move() {
	// 동시에 이동을 처리하기 위한 배열
	int temp[20][20] = { 0, };

	for (int i = 1; i <= m; i++) {
		// 상어가 격자에 없으면 진행 x
		if (!shark[i].live)
			continue;

		int y = shark[i].y;
		int x = shark[i].x;
		int dir = shark[i].dir;

		bool flag = false;
		int temp_dir = -1;

		for (int j = 0; j < 4; j++) {
			int ny = y + d[shark_dir[i][dir][j]][0];
			int nx = x + d[shark_dir[i][dir][j]][1];
			
			// 격자를 벗어나거나 냄새가 남아있다면 갈 수 없음
			if (ny < 0 || ny >= n || nx < 0 || nx >= n)
				continue;
			if (smell[ny][nx].first != 0) {
				// 자신의 냄새가 남아있는 칸을 기록하기 위한 조건문
				if (smell[ny][nx].first == i) {
					if (temp_dir == -1)
						temp_dir = j;
				}

				continue;
			}

			// 여기까지 왔으면 이동할 수 있는 방향을 찾았다는 뜻
			flag = true;

			// 현재 격자에 상어가 있다면 상어 번호를 비교하여 작은 번호의 상어만 남긴다.
			if (temp[ny][nx] != 0) {
				if (temp[ny][nx] > i) {
					shark[i].y = ny;
					shark[i].x = nx;
					shark[i].dir = shark_dir[i][dir][j];

					shark[temp[ny][nx]].live = false;
					temp[ny][nx] = i;
				}
				else 
					shark[i].live = false;
			}
			else {
				shark[i].y = ny;
				shark[i].x = nx;
				shark[i].dir = shark_dir[i][dir][j];

				temp[ny][nx] = i;
			}

			break;
		}

		// 냄새가 없는 칸이 없는 경우 자신의 냄새가 있는 칸으로 이동
		if (!flag) {
			int ny = y + d[shark_dir[i][dir][temp_dir]][0];
			int nx = x + d[shark_dir[i][dir][temp_dir]][1];

			if (temp[ny][nx] != 0) {
				if (temp[ny][nx] > i) {
					shark[i].y = ny;
					shark[i].x = nx;
					shark[i].dir = shark_dir[i][dir][temp_dir];

					shark[temp[ny][nx]].live = false;
					temp[ny][nx] = i;
				}
				else
					shark[i].live = false;
			}
			else {
				shark[i].y = ny;
				shark[i].x = nx;
				shark[i].dir = shark_dir[i][dir][temp_dir];

				temp[ny][nx] = i;
			}
		}
	}

	// 옮겨진 위치에 상어의 냄새 남기기
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (temp[i][j] != 0)
				smell[i][j] = { temp[i][j], k + 1 };

			shark_arr[i][j] = temp[i][j];
		}
	}
}

// 상어의 냄새를 줄여준다.
void smell_down() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (smell[i][j].second != 0) {
				smell[i][j].second--;

				if (smell[i][j].second == 0)
					smell[i][j].first = 0;
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> shark_arr[i][j];

			if (shark_arr[i][j] != 0) {
				shark[shark_arr[i][j]] = { i,j,0,true };

				smell[i][j] = { shark_arr[i][j], k };
			}
		}
	}

	int num;
	for (int i = 1; i <= m; i++) {
		cin >> num;

		shark[i].dir = num - 1;
	}

	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < 4; j++) {
			for (int z = 0; z < 4; z++) {
				cin >> num;

				shark_dir[i][j][z] = num - 1;
			}
		}
	}

	while (1) {
		if (live_check())
			break;
		if (result >= 1000) {
			result = -1;
			break;
		}

		result++;
		shark_move();
		smell_down();
	}

	cout << result << '\n';

	return 0;
}
