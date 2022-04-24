#include <bits/stdc++.h>
using namespace std;

struct info {
	int y;
	int x;
	int d;
};

int n, k, y, x, d, result, MAP[12][12];

int dir[4][2] = { {0,1},{0,-1},{-1,0},{1,0} };

vector<int> arr[12][12];
vector<info> chess;


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

// 0: 흰색, 1: 빨간색, 2: 파란색
void chess_move(int y, int x, int ny, int nx, int idx) {
	int cur = 0;
	int num = MAP[ny][nx];
	int size = arr[y][x].size();

	if (ny < 0 || ny >= n || nx < 0 || nx >= n)
		num = 2;

	// 해당하는 말의 위치 찾기
	for (int s = 0; s < size; s++) {
		if (arr[y][x][s] == idx) {
			cur = s;
			break;
		}
	}

	// 파란색인 경우
	if (num == 2) {
		int d = chess[idx].d;

		int nd = reverse_d(d);	
		chess[idx].d = nd;

		int nny = y + dir[nd][0];
		int nnx = x + dir[nd][1];

		// 바꾸고 난 뒤 파란색이 아니면 한 칸 이동
		if (MAP[nny][nnx] != 2 && nny >= 0 && nny < n && nnx >= 0 && nnx < n)
			chess_move(y, x, nny, nnx, idx);
	}
	else if (num == 0) {
		int cnt = 0;

		// 해당하는 말과 그 위에 있는 모든 말 이동
		for (int j = cur; j < size; j++) {
			arr[ny][nx].push_back(arr[y][x][j]);

			chess[arr[y][x][j]].y = ny;
			chess[arr[y][x][j]].x = nx;

			cnt++;
		}

		// 옮긴 말들 기존 위치에서 삭제
		while (cnt--)
			arr[y][x].pop_back();
	}
	else {
		int cnt = 0;

		// 해당하는 말과 그 위에 있는 모든 말 반대로 
		for (int j = size - 1; j >= cur; j--) {
			arr[ny][nx].push_back(arr[y][x][j]);

			chess[arr[y][x][j]].y = ny;
			chess[arr[y][x][j]].x = nx;

			cnt++;
		}

		while (cnt--)
			arr[y][x].pop_back();
	}
}

// 4개가 쌓인지 확인하는 함수
bool chess_check() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j].size() >= 4)
				return true;
		}
	}

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> MAP[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		cin >> y >> x >> d;

		arr[y - 1][x - 1].push_back(i);
		chess.push_back({ y - 1,x - 1,d - 1 });
	}

	bool flag = false;

	while (1) {
		if (result > 1000) {
			result = -1;
			break;
		}

		for (int i = 0; i < chess.size(); i++) {
			int y = chess[i].y;
			int x = chess[i].x;
			int d = chess[i].d;

			int ny = y + dir[d][0];
			int nx = x + dir[d][1];

			chess_move(y, x, ny, nx, i);

			if (chess_check()) {
				flag = true;
				break;
			}
		}

		if (flag)
			break;

		result++;
	}

	if (flag)
		cout << result + 1 << '\n';
	else
		cout << result << '\n';

	return 0;
}