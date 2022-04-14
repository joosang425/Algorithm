#include <bits/stdc++.h>
using namespace std;

int n, m, result = 987654321;

char arr[10][10], temp[10][10];
pair<int, int> red, blue;

int dir[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1,0} };

// 바로 전 기울기 방향과 현재 방향을 비교하기 위한 함수
int reverse_d(int num) {
	if (num == 0)
		return 1;
	else if (num == 1)
		return 0;
	else if (num == 2)
		return 3;
	else
		return 2;
}

// 구슬을 굴리는 함수
void solve(int ry, int rx, int by, int bx, int direction, int cnt) {
	// 10번 이하로만 진행
	if (cnt > 10)
		return;
	// 현재 횟수가 result보다 작을 시에 진행 할 필요X 
	if (cnt >= result)
		return;

	bool red_flag = false;
	bool blue_flag = false;

	int nry = ry + dir[direction][0];
	int nrx = rx + dir[direction][1];

	// 빨간 구슬 움직임
	while (1) {
		if (arr[nry][nrx] == '#') {
			nry -= dir[direction][0];
			nrx -= dir[direction][1];
			break;
		}
		else if (arr[nry][nrx] == 'O') {
			red_flag = true;
			break;
		}

		nry += dir[direction][0];
		nrx += dir[direction][1];
	}

	int nby = by + dir[direction][0];
	int nbx = bx + dir[direction][1];

	// 파란 구슬 움직임
	while (1) {
		if (arr[nby][nbx] == '#') {
			nby -= dir[direction][0];
			nbx -= dir[direction][1];
			break;
		}
		else if (arr[nby][nbx] == 'O') {
			blue_flag = true;
			break;
		}

		nby += dir[direction][0];
		nbx += dir[direction][1];
	}

	// 파란 구슬이 구멍에 빠졌을 경우
	if (blue_flag)
		return;
	else {
		// 빨간 구슬만 빠진 경우
		if (red_flag) {
			result = min(result, cnt);
			return;
		}
	}

	// 현재 칸에 빨간색, 파란색 구슬이 같이 존재하는 경우 처리하는 함수
	if (nry == nby && nrx == nbx) {
		// 움직인 거리를 통해 많이 움직였다는 것은 더 멀리 있었다는 뜻이므로
		int rdist = abs(ry - nry) + abs(rx - nrx);
		int bdist = abs(by - nby) + abs(bx - nbx);

		if (rdist > bdist) {
			nry -= dir[direction][0];
			nrx -= dir[direction][1];
		}
		else {
			nby -= dir[direction][0];
			nbx -= dir[direction][1];
		}
	}

	for (int i = 0; i < 4; i++) {
		// 이전 방향과 반대 방향은 진행 X
		if (direction == reverse_d(i))
			continue;

		solve(nry, nrx, nby, nbx, i, cnt + 1);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	string str;
	for (int i = 0; i < n; i++) {
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			arr[i][j] = str[j];

			if (arr[i][j] == 'R') {
				red.first = i;
				red.second = j;
				arr[i][j] = '.';
			}
			else if (arr[i][j] == 'B') {
				blue.first = i;
				blue.second = j;
				arr[i][j] = '.';
			}
		}
	}

	for (int i = 0; i < 4; i++)
		solve(red.first, red.second, blue.first, blue.second, i, 1);

	if (result > 10 || result == 987654321)
		cout << -1 << '\n';
	else
		cout << result << '\n';

	return 0;
}
