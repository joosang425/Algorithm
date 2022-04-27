#include <bits/stdc++.h>
using namespace std;

int n, num, result, arr[400][400];
int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

vector<int> student;
bool connected[401][401];

void batch_student(int sequence) {
	int can_y = n - 1, can_x = n - 1, favo = 0, empty = 0;

	// 배열을 탐색하면서 조건에 만족하는 칸 찾기
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			// 이미 학생이 있는 경우 진행 X
			if (arr[i][j])
				continue;

			int temp_fa = 0, temp_em = 0;

			// 네 방향 탐색
			for (int d = 0; d < 4; d++) {
				int ny = i + dir[d][0];
				int nx = j + dir[d][1];

				if (ny < 0 || ny >= n || nx < 0 || nx >= n)
					continue;

				// 현재 학생이 좋아하는 학생 수 구하기
				if (connected[sequence][arr[ny][nx]])
					temp_fa++;
				// 비어있는 칸인지 확인
				if (arr[ny][nx] == 0)
					temp_em++;
			}

			// 조건 1
			if (favo < temp_fa) {
				can_y = i, can_x = j;
				favo = temp_fa, empty = temp_em;
			}
			// 조건 2
			else if (favo == temp_fa) {
				if (empty < temp_em) {
					can_y = i, can_x = j;
					favo = temp_fa, empty = temp_em;
				}
				// 조건 3
				else if (empty == temp_em) {
					if (can_y > i) {
						can_y = i, can_x = j;
						favo = temp_fa, empty = temp_em;
					}
					else if (can_y == i) {
						if (can_x > j) {
							can_y = i, can_x = j;
							favo = temp_fa, empty = temp_em;
						}
					}
				}
			}
		}
	}

	arr[can_y][can_x] = sequence;
}

int favorite_check(int y, int x) {
	int cnt = 0;

	for (int i = 0; i < 4; i++) {
		int ny = y + dir[i][0];
		int nx = x + dir[i][1];

		if (ny < 0 || ny >= n || nx < 0 || nx >= n)
			continue;

		if (connected[arr[y][x]][arr[ny][nx]])
			cnt++;
	}

	return cnt;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n * n; i++) {
		cin >> num;

		student.push_back(num);
		int a;
		for (int j = 0; j < 4; j++) {
			cin >> a;

			// 좋아하는 학생인 경우 true로 저장
			connected[num][a] = true;
		}
	}

	// 학생의 번호대로 반복문 진행
	for (int i = 0; i < student.size(); i++)
		batch_student(student[i]);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int cnt = favorite_check(i, j);

			if (cnt == 1)
				result += 1;
			else if (cnt == 2)
				result += 10;
			else if (cnt == 3)
				result += 100;
			else if (cnt == 4)
				result += 1000;
		}
	}

	cout << result << '\n';

	return 0;
}