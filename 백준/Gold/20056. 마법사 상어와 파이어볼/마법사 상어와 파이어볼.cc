#include <bits/stdc++.h>
using namespace std;

// 파이어볼 정보
struct info {
	int m;
	int s;
	int d;
};

int dir[8][2] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };

int n, M, k, r, c, m, s, d, result;
vector<info> arr[50][50];

// 파이어볼 이동
void fireball_move() {
	vector<info> temp[50][50];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int f = 0; f < arr[i][j].size(); f++) {
				int m = arr[i][j][f].m;
				int s = arr[i][j][f].s;
				int d = arr[i][j][f].d;

				int y = i, x = j;

				for (int q = 0; q < s; q++) {
					y = y + dir[d][0];
					if (y == -1)
						y = n - 1;
					if (y == n)
						y = 0;

					x = x + dir[d][1];
					if (x == -1)
						x = n - 1;
					if (x == n)
						x = 0;
				}

				temp[y][x].push_back({ m, s, d });
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (temp[i][j].size() < 2)
				continue;

			int m_sum = 0, s_sum = 0, f_dir = temp[i][j][0].d % 2;
			int size = temp[i][j].size();
			bool same = true;

			for (int f = 0; f < temp[i][j].size(); f++) {
				m_sum += temp[i][j][f].m;
				s_sum += temp[i][j][f].s;
				
				if (f_dir != (temp[i][j][f].d % 2))
					same = false;
			}

			temp[i][j].clear();

			if (m_sum / 5 > 0) {
				if (same) {
					temp[i][j].push_back({ m_sum / 5, s_sum / size, 0 });
					temp[i][j].push_back({ m_sum / 5, s_sum / size, 2 });
					temp[i][j].push_back({ m_sum / 5, s_sum / size, 4 });
					temp[i][j].push_back({ m_sum / 5, s_sum / size, 6 });
				}
				else {
					temp[i][j].push_back({ m_sum / 5, s_sum / size, 1 });
					temp[i][j].push_back({ m_sum / 5, s_sum / size, 3 });
					temp[i][j].push_back({ m_sum / 5, s_sum / size, 5 });
					temp[i][j].push_back({ m_sum / 5, s_sum / size, 7 });
				}
			}
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

	cin >> n >> M >> k;
	for (int i = 0; i < M; i++) {
		cin >> r >> c >> m >> s >> d;

		r--, c--;
		arr[r][c].push_back({ m , s, d });
	}

	for (int i = 0; i < k; i++)
		fireball_move();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int f = 0; f < arr[i][j].size(); f++) {
				result += arr[i][j][f].m;
			}
		}
	}

	cout << result << '\n';

	return 0;
}
