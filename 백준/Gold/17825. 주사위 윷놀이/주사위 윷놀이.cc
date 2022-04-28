#include <bits/stdc++.h>
using namespace std;

int board[33][6] = {
	{0, 1, 2, 3, 4, 5},
	{2, 2, 3, 4, 5, 6},
	{4, 3, 4, 5, 6, 7},
	{6, 4, 5, 6, 7 ,8},
	{8, 5, 6, 7, 8, 9},
	{10, 21, 22, 23, 24, 25},
	{12, 7, 8, 9, 10, 11},
	{14, 8, 9, 10, 11, 12},
	{16, 9, 10, 11, 12, 13},
	{18, 10, 11, 12, 13, 14},
	{20, 27, 28, 24, 25, 26},
	{22, 12, 13, 14, 15, 16},
	{24, 13, 14, 15, 16, 17},
	{26, 14, 15, 16, 17, 18},
	{28, 15, 16, 17, 18, 19},
	{30, 29, 30, 31, 24, 25},
	{32, 17, 18, 19, 20, 32},
	{34, 18, 19, 20, 32, 32},
	{36, 19, 20, 32, 32, 32},
	{38, 20, 32, 32, 32, 32},
	{40, 32, 32, 32, 32, 32},
	{13, 22, 23, 24, 25, 26},
	{16, 23, 24, 25, 26, 20},
	{19, 24, 25, 26, 20, 32},
	{25, 25, 26, 20, 32, 32},
	{30, 26, 20, 32, 32, 32},
	{35, 20, 32, 32, 32, 32},
	{22, 28, 24, 25, 26, 20},
	{24, 24, 25, 26, 20, 32},
	{28, 30, 31, 24, 25, 26},
	{27, 31, 24, 25, 26, 20},
	{26, 24, 25, 26, 20, 32},
	{0, 32, 32, 32, 32, 32}
};

int arr[10], locate[4], result;
bool visited[33];

void solve(int idx, int sum) {
	if (idx == 10) {
		result = max(result, sum);
		return;
	}

	for (int i = 0; i < 4; i++) {
		int prev = locate[i];
		int move = board[prev][arr[idx]];

		if (visited[move] && move != 32)
			continue;

		visited[prev] = false;
		visited[move] = true;
		locate[i] = move;

		solve(idx + 1, sum + board[move][0]);

		locate[i] = prev;
		visited[prev] = true;
		visited[move] = false;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 10; i++)
		cin >> arr[i];

	solve(0, 0);

	cout << result << '\n';

	return 0;
}