#include <bits/stdc++.h>
using namespace std;

int dir[8][2] = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} };

// arr = 추가해야 할 양분, energy = 현재 양분의 양
int n, m, k, arr[10][10], energy[10][10];
vector<int> tree[10][10];

int total_tree;

void spring_summer() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (tree[i][j].empty())
				continue;

			vector<int> v;
			int died = 0;

			// 어린 나무부터 양분을 주기 위한 정렬
			sort(tree[i][j].begin(), tree[i][j].end());

			// 나무의 나이가 적은 경우만 z++
			for (int z = 0; z < tree[i][j].size(); z++) {
				int age = tree[i][j][z];

				// 현재 나무의 나이가 양분보다 클 경우 죽은 나무로 처리
				if (age > energy[i][j]) {
					died += age / 2;
					total_tree--;
				}
				// 아닌 경우 현재 나무의 나이 + 1값을 vector에 저장 및 양분 감소
				else {
					energy[i][j] -= age;
					v.push_back(age + 1);
				}
			}

			tree[i][j].clear();

			for (int z = 0; z < v.size(); z++)
				tree[i][j].push_back(v[z]);

			energy[i][j] += died;
		}
	}
}

void fall() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (tree[i][j].empty())
				continue;

			// 나무의 나이가 5의 배수인 경우 번식
			for (int z = 0; z < tree[i][j].size(); z++) {
				if (tree[i][j][z] % 5 == 0) {
					for (int d = 0; d < 8; d++) {
						int y = i + dir[d][0];
						int x = j + dir[d][1];

						if (y < 0 || y >= n || x < 0 || x >= n)
							continue;

						total_tree++;
						tree[y][x].push_back(1);
					}
				}
			}
		}
	}
}

void winter() {
	// 양분 추가
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			energy[i][j] += arr[i][j];
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];

			energy[i][j] = 5;
		}
	}
	
	int x, y, z;
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> z;

		tree[x - 1][y - 1].push_back(z);
	}

	total_tree = m;

	for (int i = 0; i < k; i++) {
		spring_summer();
		fall();
		winter();
	}

	cout << total_tree;

	return 0;
}