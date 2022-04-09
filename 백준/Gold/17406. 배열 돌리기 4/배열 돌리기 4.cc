#include <bits/stdc++.h>
using namespace std;

struct info {
	int r;
	int c;
	int s;
};

int n, m, k, r, c, s, arr[50][50], board_temp[50][50];
int result = 987654321;
bool selected[6];

vector<info> v;

void board_rotate(int y, int x, int size) {
	int sy = y, sx = x;

	for (int s = size; s > 1; s -= 2) {
		int temp = board_temp[sy][sx];

		for (int i = sy; i < sy + s - 1; i++)
			board_temp[i][sx] = board_temp[i + 1][sx];
		for (int j = sx; j < sx + s - 1; j++)
			board_temp[sy + s - 1][j] = board_temp[sy + s - 1][j + 1];
		for (int i = sy + s - 1; i > sy; i--)
			board_temp[i][sx + s - 1] = board_temp[i - 1][sx + s - 1];
		for (int j = sx + s - 1; j > sx; j--)
			board_temp[sy][j] = board_temp[sy][j - 1];

		board_temp[sy][sx + 1] = temp;

		sy++;
		sx++;
	}
}

int calc() {
	int value = 987654321;

	for (int i = 0; i < n; i++) {
		int sum = 0;
		for (int j = 0; j < m; j++) {
			sum += board_temp[i][j];
		}

		value = min(value, sum);
	}

	return value;
}

void copy(int arr1[][50], int arr2[][50]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			arr1[i][j] = arr2[i][j];
		}
	}
}

// 모든 조합 구하기
void dfs(string str) {
	if (str.length() == v.size()) {
		copy(board_temp, arr);

		// 구해놓은 조합순으로 진행
		for (int i = 0; i < str.length(); i++) {
			int num = str[i] - '0';

			board_rotate(v[num].r - v[num].s - 1, v[num].c - v[num].s - 1, v[num].s * 2 + 1);
		}

		// 가장 작은 값 저장
		result = min(result, calc());

		return;
	}

	for (int i = 0; i < v.size(); i++) {
		if (selected[i])
			continue;

		selected[i] = true;
		dfs(str + to_string(i));
		selected[i] = false;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		cin >> r >> c >> s;

		v.push_back({ r,c,s });
	}

	dfs("");

	cout << result << '\n';

	return 0;
}