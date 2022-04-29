#include <bits/stdc++.h>
using namespace std;

int m, s, fx, fy, d, sx, sy, result, smell[4][4];

char str[4] = { '1', '2', '3', '4' };
int dir[8][2] = { {0,-1},{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1} };
int s_dir[4][2] = { {-1, 0},{0, -1},{1, 0},{0, 1} };

vector<string> shark_dir;
pair<int, int> shark;
vector<int> arr[4][4];
vector<pair<pair<int, int>, int>> fish;

void dfs(string temp) {
	if (temp.length() == 3) {
		shark_dir.push_back(temp);
		return;
	}

	for (int i = 0; i < 4; i++)
		dfs(temp + str[i]);
}

void fish_move() {
	vector<int> temp[4][4];

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int f = 0; f < arr[i][j].size(); f++) {
				int d = arr[i][j][f];

				bool flag = false;

				for (int dd = 0; dd < 8; dd++) {
					int y = i + dir[d][0];
					int x = j + dir[d][1];

					if (y < 0 || y >= 4 || x < 0 || x >= 4 || smell[y][x] != 0 || (shark.first == y && shark.second == x)) {
						d--;
						if (d == -1)
							d = 7;

						continue;
					}

					flag = true;

					temp[y][x].push_back(d);
					break;
				}

				if (!flag)
					temp[i][j].push_back(arr[i][j][f]);
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			arr[i][j] = temp[i][j];
		}
	}
}

void shark_move() {
	vector<pair<int, int>> route;

	int cnt = 0;

	for (int i = 0; i < shark_dir.size(); i++) {
		vector<pair<int, int>> shark_route;
		int visited[4][4] = { false, };

		int fish_cnt = 0;
		int y = shark.first, x = shark.second;

		bool flag = true;
		string str = shark_dir[i];

		for (int j = 0; j < str.length(); j++) {
			int d = (str[j] - '0') - 1;

			y += s_dir[d][0];
			x += s_dir[d][1];

			if (y < 0 || y >= 4 || x < 0 || x >= 4) {
				flag = false;
				break;
			}

			if(!visited[y][x])
				fish_cnt += arr[y][x].size();

			shark_route.push_back({ y,x });
			visited[y][x] = true;
		}

		if (flag) {
			if (fish_cnt > cnt) {
				cnt = fish_cnt;
				route = shark_route;
			}
			else if (fish_cnt == cnt) {
				if (route.empty())
					route = shark_route;
			}
		}
	}

	for (int i = 0; i < route.size(); i++) {
		int y = route[i].first, x = route[i].second;

		if (!arr[y][x].empty()) {
			arr[y][x].clear();
			smell[y][x] = 3;
		}
	}

	shark.first = route[2].first;
	shark.second = route[2].second;
}

void smell_remove() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (smell[i][j])
				smell[i][j]--;
		}
	}
}

void copy_fish() {
	for (int i = 0; i < fish.size(); i++) {
		int y = fish[i].first.first;
		int x = fish[i].first.second;
		int d = fish[i].second;

		arr[y][x].push_back(d);
	}

	fish.clear();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int f = 0; f < arr[i][j].size(); f++) {
				int d = arr[i][j][f];

				fish.push_back({ {i,j}, d });
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	dfs("");

	cin >> m >> s;
	for (int i = 0; i < m; i++) {
		cin >> fx >> fy >> d;
		fx--, fy--, d--;

		arr[fx][fy].push_back(d);
		fish.push_back({ {fx,fy}, d });
	}

	cin >> sx >> sy;
	sx--, sy--;

	shark.first = sx, shark.second = sy;

	for (int i = 0; i < s; i++) {
		fish_move();
		shark_move();
		smell_remove();
		copy_fish();
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result += arr[i][j].size();
		}
	}

	cout << result << '\n';

	return 0;
}