#include <bits/stdc++.h>
using namespace std;

int n, result;
int sequence[10];	// 타순 배치를 위한 배열
bool base[3];	// 현재 베이스에 선수가 있는지 기록하는 배열
bool selected[10];	// 조합을 위한 배열

int arr[50][10];

void start_game() {
	int score = 0;
	int cur_player = 1;

	for (int i = 0; i < n; i++) {
		int out_cnt = 0;
		bool flag = true;
		memset(base, false, sizeof(base));

		while (1) {
			for (int j = cur_player; j <= 9; j++) {
				int player = arr[i][sequence[j]];

				// 1루타
				if (player == 1) {
					for (int b = 2; b >= 0; b--) {
						// 3루에 주자가 있었을 경우
						if (b == 2 && base[b]) {
							score++;
							base[b] = false;
						}
						else if (base[b]) {
							base[b + 1] = true;
							base[b] = false;
						}
					}

					base[0] = true;
				}
				// 2루타
				else if (player == 2) {
					for (int b = 2; b >= 0; b--) {
						// 3루, 2루에 주자가 있을 경우
						if (b >= 1 && base[b]) {
							score++;
							base[b] = false;
						}
						else if (base[b]) {
							base[b + 2] = true;
							base[b] = false;
						}
					}
					
					base[1] = true;
				}
				// 3루타
				else if (player == 3) {
					for (int b = 2; b >= 0; b--) {
						if (b >= 0 && base[b]) {
							score++;
							base[b] = false;
						}
					}

					base[2] = true;
				}
				// 홈런
				else if (player == 4) {
					for (int b = 0; b <= 2; b++) {
						if (base[b]) {
							score++;
							base[b] = false;
						}
					}

					score++;
				}
				// 아웃
				else 
					out_cnt++;

				if (out_cnt == 3) {
					cur_player = j + 1;

					if (cur_player == 10)
						cur_player = 1;

					flag = false;
					break;
				}
			}

			if (!flag) break;
			cur_player = 1;
		}
	}

	result = max(result, score);
}

void dfs(int cnt) {
	if (cnt == 10) {
		start_game();
		return;
	}

	for (int i = 1; i <= 9; i++) {
		if (selected[i])
			continue;

		selected[i] = true;
		sequence[i] = cnt;
		dfs(cnt + 1);
		selected[i] = false;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= 9; j++) {
			cin >> arr[i][j];
		}
	}

	selected[4] = true;
	sequence[4] = 1;	// 4번 타자는 1번

	dfs(2);

	cout << result << '\n';

	return 0;
}