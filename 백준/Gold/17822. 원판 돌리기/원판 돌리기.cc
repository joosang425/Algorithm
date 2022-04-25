#include <bits/stdc++.h>
using namespace std;

int n, m, t, x, d, k, result, arr[51][50], temp[51][50];
bool visited;

void copy(int arr1[][50], int arr2[][50]) {
	for (int i = 1; i <= 50; i++) {
		for (int j = 0; j < 50; j++) {
			arr1[i][j] = arr2[i][j];
		}
	}
}

void move(int idx, int dir, int cnt) {
	//	반시계 방향
	if (dir == 1) {
		for (int i = 0; i < cnt; i++) {
			int temp = arr[idx][0];

			for (int i = 0; i < m - 1; i++)
				arr[idx][i] = arr[idx][i + 1];

			arr[idx][m - 1] = temp;
		}
	}
	//	시계 방향
	else {
		for (int i = 0; i < cnt; i++) {
			int temp = arr[idx][m - 1];

			for (int i = m - 1; i > 0; i--)
				arr[idx][i] = arr[idx][i - 1];

			arr[idx][0] = temp;
		}
	}
}

void remove_num(int cur) {
	for (int i = 0; i < m; i++) {
		if (arr[cur][i] == 0)
			continue;

		if (i == m - 1) {
			if (arr[cur][i] == arr[cur][0]) {
				temp[cur][i] = temp[cur][0] = 0;
				visited = true;
			}
		}
		else {
			if (arr[cur][i] == arr[cur][i + 1]) {
				temp[cur][i] = temp[cur][i + 1] = 0;
				visited = true;
			}
		}
	}

	if (cur < n) {
		for (int i = 0; i < m; i++) {
			if (arr[cur][i] == 0)
				continue;

			if (arr[cur][i] == arr[cur + 1][i]) {
				temp[cur][i] = temp[cur + 1][i] = 0;
				visited = true;
			}
		}
	}
}

void calc(double avg) {
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			if (!temp[i][j])
				continue;

			if (avg < (double)temp[i][j])
				temp[i][j]--;
			else if (avg > (double)temp[i][j])
				temp[i][j]++;
		}
	}
}

void check() {
	double sum = 0;
	int cnt = 0;

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			if (temp[i][j] != 0)
				cnt++;

			sum += (double)temp[i][j];
		}

		remove_num(i);
	}

	if (!visited)
		calc(sum / cnt);

	visited = false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> t;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < t; i++) {
		cin >> x >> d >> k;

		int tempx = x;

		while (x <= n) {
			move(x, d, k);
			x += tempx;
		}

		copy(temp, arr);
		check();
		copy(arr, temp);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < m; j++) {
			result += arr[i][j];
		}
	}

	cout << result << '\n';

	return 0;
}