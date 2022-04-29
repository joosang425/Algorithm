#include <bits/stdc++.h>
using namespace std;

int n, m, d, s, arr[55][55], result[3];

bool crack[55 * 55];
int sequence[55][55];
vector<pair<int, int>> marble(55 * 55, { 0, 0 });

int dir[4][2] = { {-1,0}, {1,0},{0,-1},{0,1} };

int next_dir(int num) {
	if (num == 0)
		return 2;
	else if (num == 1)
		return 3;
	else if (num == 2)
		return 1;
	else
		return 0;
}

// 구슬 격자 안에 추가 및 vector 안에 삽입
void make_marble() {
	int idx = 0;

	sequence[(n - 1) / 2][(n - 1) / 2] = idx;
	marble[idx++] = { (n - 1) / 2, (n - 1) / 2 };
	sequence[(n - 1) / 2][(n - 1) / 2 - 1] = idx;
	marble[idx++] = { (n - 1) / 2, (n - 1) / 2 - 1 };

	int sy = (n - 1) / 2 + 1;
	int sx = (n - 1) / 2 - 1;
	int direction = 3;

	for (int i = 2; i < n; i++) {
		for (int x = 0; x < i; x++) {
			sequence[sy][sx] = idx;
			marble[idx++] = { sy, sx };

			sy += dir[direction][0];
			sx += dir[direction][1];
		}

		direction = next_dir(direction);

		for (int y = 0; y < i; y++) {
			sequence[sy][sx] = idx;
			marble[idx++] = { sy,sx };

			sy += dir[direction][0];
			sx += dir[direction][1];
		}

		direction = next_dir(direction);
	}

	for (int i = 0; i < n; i++) {
		sequence[sy][sx] = idx;
		marble[idx++] = { sy,sx };

		sy += dir[direction][0];
		sx += dir[direction][1];
	}
}

// 얼음 파편으로 인한 구슬 파괴
void marble_crack(int direction, int speed) {
	memset(crack, false, sizeof(crack));

	int y = (n - 1) / 2;
	int x = (n - 1) / 2;

	for (int i = 0; i < speed; i++) {
		y = y + dir[direction][0];
		x = x + dir[direction][1];

		crack[sequence[y][x]] = true;
	}
}

// 구슬 이동
void marble_move() {
	int cnt = 0;
	bool flag = false;

	for (int i = 1; i < n * n; i++) {
		// 얼음 파편에 의해 부서진 칸 cnt++만 해주고 넘어감
		if (crack[i]) {
			cnt++;
			flag = true;
		}
		else {
			// 0을 만났다는 것은 존재하는 구슬의 범위를 넘어간 경우
			if (arr[marble[i].first][marble[i].second] == 0) {
				// 구슬의 위치가 줄었기 때문에 끝에 존재하던 구슬의 위치를 0으로 변경
				for (int j = 1; j <= cnt; j++)
					arr[marble[i - j].first][marble[i - j].second] = 0;
				flag = false;
				break;
			}
			else
				arr[marble[i - cnt].first][marble[i - cnt].second] = arr[marble[i].first][marble[i].second];
		}
	}

	// 격자 안에 구슬이 꽉 차있을 경우 해당
	if (flag) {
		int i = n * n - 1;
		for (int j = 0; j < cnt; j++, i--)
			arr[marble[i].first][marble[i].second] = 0;
	}
}

// 연속된 구술이 있는지 확인
bool check() {
	memset(crack, false, sizeof(crack));

	bool flag = false;
	int cur = arr[marble[1].first][marble[1].second];
	int start = 1;
	int cnt = 1;
	int i;

	for (i = 2; i < n * n; i++) {
		int next = arr[marble[i].first][marble[i].second];

		if (next == 0)
			break;

		if (cur != next) {
			if (cnt >= 4) {
				flag = true;
				for (int j = start; j < i; j++)
					crack[j] = true;
				result[cur - 1] += cnt;
			}

			cur = next;
			start = i;
			cnt = 1;
		}
		else
			cnt++;
	}

	if (cnt >= 4) {
		flag = true;
		for (int j = start; j < i; j++)
			crack[j] = true;
		result[cur - 1] += cnt;
	}

	return flag;
}

// 격자 안 구슬 변경
void remake_marble() {
	memset(crack, false, sizeof(crack));

	int temp[50][50] = { 0, };

	int cur = arr[marble[1].first][marble[1].second];
	int cnt = 1;
	int cur_num = 1;
	bool flag = true;

	for (int i = 2; i < n * n; i++) {
		if (cur_num >= n * n) {
			flag = false;
			break;
		}

		int next = arr[marble[i].first][marble[i].second];
		if (next == 0)
			break;

		if (cur != next) {
			temp[marble[cur_num].first][marble[cur_num].second] = cnt;
			temp[marble[cur_num + 1].first][marble[cur_num + 1].second] = cur;
			cur = next;
			cnt = 1;
			cur_num += 2;
		}
		else
			cnt++;
	}

	if (flag) {
		if (cur_num != 1) {
			temp[marble[cur_num].first][marble[cur_num].second] = cnt;
			temp[marble[cur_num + 1].first][marble[cur_num + 1].second] = cur;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = temp[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	make_marble();

	for (int i = 0; i < m; i++) {
		cin >> d >> s;

		d--;
		marble_crack(d, s);
		marble_move();

		// 연속된 구슬이 없을 때까지 반복
		while (1) {
			if (!check())
				break;

			marble_move();
		}

		remake_marble();
	}

	int sum = result[0] + (result[1] * 2) + (result[2] * 3);
	cout << sum << '\n';

	return 0;
}