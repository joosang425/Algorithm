#include <bits/stdc++.h>
using namespace std;

int n, k, result;
vector<int> v[101];

int dir[2][2] = { {0,1},{-1,0} };

// 물고기의 수가 가장 적은 어항에 물고기 추가
void fishbowl_plus() {
	int cnt = 10001;
	vector<int> lower;

	for (int i = 0; i < v[0].size(); i++) {
		if (cnt > v[0][i]) {
			cnt = v[0][i];
			lower.clear();
			lower.push_back(i);
		}
		else if (cnt == v[0][i])
			lower.push_back(i);
	}

	for (int i = 0; i < lower.size(); i++)
		v[0][lower[i]]++;
}

// 어항 공중 부양 시키기
int fishbowl_move() {
	int width = 1;
	int height = 1;
	bool flag = false;

	while (1) {
		// 쌓인 어항의 높이보다 0 인덱스의 어항의 수가 적은 경우 더 이상 진행불가
		int remain = v[0].size() - width;
		if (height > remain)
			break;

		int tmpwidth = width;
		for (int i = 0; i < width; i++, tmpwidth--) {
			int idx = 0;
			for (int j = 0; j < height; j++, idx++) {
				v[tmpwidth].push_back(v[idx][i]);
			}
		}

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				v[i].erase(v[i].begin());
			}
		}

		if (!flag) {
			height++;
			flag = true;
		}
		else {
			width++;
			flag = false;
		}
	}

	return height;
}

// 물고기의 수를 조절
void fish_control(int height) {
	vector<int> temp[101];

	for (int i = 0; i < height; i++)
		temp[i] = v[i];

	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < v[i].size(); j++) {
			// 계산했던 곳을 다시 하지 않기 위해 아래, 오른쪽만 실행
			for (int t = 0; t < 2; t++) {
				int y = i + dir[t][0];
				int x = j + dir[t][1];

				if (y < 0 || x >= v[i].size())
					continue;

				int value = abs(v[i][j] - v[y][x]);
				value /= 5;

				if (value <= 0)
					continue;
				else {
					if (v[i][j] < v[y][x]) {
						temp[y][x] -= value;
						temp[i][j] += value;
					}
					else {
						temp[i][j] -= value;
						temp[y][x] += value;
					}
				}
			}
		}
	}

	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < v[i].size(); j++) {
			v[i][j] = temp[i][j];
		}
	}
}

// 어항을 바닥에 일렬로 
void fishbowl_back(int height) {
	int width = v[height - 1].size();

	vector<int> temp;

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			temp.push_back(v[j][i]);
		}
	}
	for (int i = width; i < v[0].size(); i++)
		temp.push_back(v[0][i]);

	v[0] = temp;

	for (int i = 1; i < height; i++)
		v[i].clear();
}

// 공중 부양 작업
void fishbowl_move2() {
	int Size = v[0].size();

	// 왼쪽 n/2개 공중 부양
	for (int i = Size / 2 - 1; i >= 0; i--)
		v[1].push_back(v[0][i]);
	for (int i = 0; i < Size / 2; i++)
		v[0].erase(v[0].begin());

	// 왼쪽 n/4개 공중 부양
	for (int i = Size / 4 - 1; i >= 0; i--) {
		v[2].push_back(v[1][i]);
		v[3].push_back(v[0][i]);
	}
	for (int i = 0; i < Size / 4; i++) {
		v[0].erase(v[0].begin());
		v[1].erase(v[1].begin());
	}
}

// 어항 물고기의 수 차이 구하기
bool fish_check() {
	int large = 0, small = 10001;

	for (int i = 0; i < v[0].size(); i++) {
		large = max(large, v[0][i]);
		small = min(small, v[0][i]);
	}

	if (large - small <= k)
		return true;

	return false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> k;

	int num;
	for (int i = 0; i < n; i++) {
		cin >> num;

		v[0].push_back(num);
	}

	while (1) {
		if (fish_check())
			break;

		fishbowl_plus();
		int height = fishbowl_move();
		fish_control(height);
		fishbowl_back(height);
		fishbowl_move2();
		fish_control(4);
		fishbowl_back(4);

		result++;
	}

	cout << result << '\n';

	return 0;
}