#include <bits/stdc++.h>
using namespace std;

struct fireball {
	int weight;
	int speed;
	int direction;
};

struct temp_fireball {
	int y;
	int x;
	int weight;
	int speed;
	int direction;
};

int n, m, k, r, c, md, s, d;
int dir[8][2] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };

// 총 질량 기록을 위한 배열
int total_weight[50][50];
// 총 속도 기록을 위한 배열
int total_speed[50][50];
vector<fireball> v[50][50];

void fireball_move() {
	vector<temp_fireball> temp;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (v[i][j].empty())
				continue;
		
			int Size = v[i][j].size();

			for (int s = 0; s < Size; s++) {
				int m = v[i][j].front().weight;
				int sp = v[i][j].front().speed;
				int d = v[i][j].front().direction;
				total_weight[i][j] -= m;
				total_speed[i][j] -= sp;
				v[i][j].erase(v[i][j].begin());

				int ny = i, nx = j;
				
				for (int i = 0; i < sp; i++) {
					ny += dir[d][0];

					if (ny < 0)
						ny = n - 1;
					else if (ny == n)
						ny = 0;

					nx += dir[d][1];

					if (nx < 0)
						nx = n - 1;
					else if (nx == n)
						nx = 0;
				}

				temp.push_back({ ny,nx,m,sp,d });
			}
		}
	}

	for (int s = 0; s < temp.size(); s++) {
		v[temp[s].y][temp[s].x].push_back({ temp[s].weight,temp[s].speed,temp[s].direction });
		total_weight[temp[s].y][temp[s].x] += temp[s].weight;
		total_speed[temp[s].y][temp[s].x] += temp[s].speed;
	}
}

void single_check() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (v[i][j].size() >= 2) {
				int dir_check = v[i][j][0].direction % 2;
				bool check = true;

				for (int s = 0; s < v[i][j].size(); s++) {
					if (dir_check != (v[i][j][s].direction % 2))
						check = false;
				}

				int nw = total_weight[i][j] / 5;
				int ns = total_speed[i][j] / v[i][j].size();
				
				if (nw == 0) {
					v[i][j].clear();
					total_weight[i][j] = 0;
					total_speed[i][j] = 0;
				}
				else {
					v[i][j].clear();

					// 모두 홀수 or 짝수
					if (check) {
						v[i][j].push_back({ nw, ns, 0 });
						v[i][j].push_back({ nw, ns, 2 });
						v[i][j].push_back({ nw, ns, 4 });
						v[i][j].push_back({ nw, ns, 6 });

						total_weight[i][j] = nw * 4;
						total_speed[i][j] = ns * 4;
					}
					// 아닌 경우
					else {
						v[i][j].push_back({ nw, ns, 1 });
						v[i][j].push_back({ nw, ns, 3 });
						v[i][j].push_back({ nw, ns, 5 });
						v[i][j].push_back({ nw, ns, 7 });

						total_weight[i][j] = nw * 4;
						total_speed[i][j] = ns * 4;
					}
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	// 정보 입력
	cin >> n >> m >> k;

	for (int i = 0; i < m; i++) {
		cin >> r >> c >> md >> s >> d;

		v[r - 1][c - 1].push_back({ md,s,d });
		total_weight[r - 1][c - 1] += md;
		total_speed[r - 1][c - 1] += s;
	}

	while (k--) {
		fireball_move();
		single_check();
	}

	int result = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			result += total_weight[i][j];
		}
	}

	cout << result << '\n';

	return 0;
}