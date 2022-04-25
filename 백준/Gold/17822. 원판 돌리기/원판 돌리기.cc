#include <bits/stdc++.h>
using namespace std;

int n, m, t, x, d, k, sum, cnt, result;
deque<int> arr[51];

void circle_move(int idx, int dir) {
	// 시계 방향
	if (dir == 0) {
		int num = arr[idx].back();
		arr[idx].pop_back();

		arr[idx].push_front(num);
	}
	// 반시계 방향
	else {
		int num = arr[idx].front();
		arr[idx].pop_front();

		arr[idx].push_back(num);
	}
}

bool near_remove() {
	bool flag = false;
	sum = cnt = 0;

	deque<int> temp[51];

	for (int i = 1; i <= n; i++)
		temp[i] = arr[i];

	// 인접한 숫자가 있는 경우 true 반환
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (!arr[i][j])
				continue;

			if (arr[i][j] == arr[i][(j + 1) % m]) {
				temp[i][j] = temp[i][(j + 1) % m] = 0;
				flag = true;
			}
			if (arr[i][j] == arr[i + 1][j]) {
				temp[i][j] = temp[i + 1][j] = 0;
				flag = true;
			}
		}
	}

	// 마지막 행 원판
	for (int j = 0; j < m; j++) {
		if (!arr[n][j])
			continue;

		if (arr[n][j] == arr[n][(j + 1) % m]) {
			temp[n][j] = temp[n][(j + 1) % m] = 0;
			flag = true;
		}
	}

	// 원판에 적힌 숫자의 합과 갯수 구하기
	for (int i = 1; i <= n; i++) {
		arr[i] = temp[i];

		for (int j = 0; j < m; j++) {
			sum += temp[i][j];

			if (temp[i][j])
				cnt++;
		}
	}

	return flag;
}

// 평균과 비교하여 숫자 변경
void turn_circle(double num) {
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			if (!arr[i][j])
				continue;

			if ((double)arr[i][j] < num)
				arr[i][j]++;
			else if ((double)arr[i][j] > num)
				arr[i][j]--;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> t;

	int num;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> num;

			arr[i].push_back(num);
		}
	}

	for (int i = 0; i < t; i++) {
		cin >> x >> d >> k;

		int temp_x = x;

		// x의 배수에 해당하는 원판 돌리기
		for (int j = x; j <= n; j += temp_x) {
			for (int s = 0; s < k; s++)
				circle_move(j, d);
		}

		// 인접한 숫자가 있는지 확인
		if (!near_remove()) {
			double value = (double)sum / cnt;

			turn_circle(value);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			result += arr[i][j];
		}
	}

	cout << result << '\n';

	return 0;
}
