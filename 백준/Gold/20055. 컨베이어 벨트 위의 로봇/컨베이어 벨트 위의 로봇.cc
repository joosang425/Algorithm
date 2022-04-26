#include <bits/stdc++.h>
using namespace std;

int n, k, x, result;
deque <int> robot;
deque <int> arr;

void move() {
	// n - 1이면 내리는 위치
	if (robot[n - 1])
		robot[n - 1] = false;

	for (int i = n - 2; i >= 0; i--) {
		// 현재 위치에 로봇이 없는 경우
		if (!robot[i])
			continue;

		// 다음 위치에 내구성이 1이상 이면서 로봇이 없는 경우
		if (arr[i + 1] >= 1 && !robot[i + 1]) {
			arr[i + 1]--;
			robot[i] = false;
			// n - 2인 경우 +1하면 n - 1 
			// 어차피 내려지기 때문에 내구성 -1만 해주고
			// continue
			if (i == n - 2)
				continue;
			robot[i + 1] = true;
		}
	}

	// 올리는 위치 체크 및 올림
	if (arr[0] >= 1 && !robot[0]) {
		arr[0]--;
		robot[0] = true;
	}
}

bool check() {
	int cnt = 0;

	for (int i = 0; i < arr.size(); i++) {
		if (!arr[i])
			cnt++;

		if (cnt >= k)
			return false;
	}

	return true;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;
	for (int i = 0; i < 2 * n; i++) {
		cin >> x;

		arr.push_back(x);
		robot.push_back(false);
	}

	while (check()) {
		result++;

		// 벨트 회전 및 로봇 회전
		arr.push_front(arr.back());
		arr.pop_back();

		robot.push_front(robot.back());
		robot.pop_back();

		// 로봇 이동
		move();
	}

	cout << result << '\n';

	return 0;
}