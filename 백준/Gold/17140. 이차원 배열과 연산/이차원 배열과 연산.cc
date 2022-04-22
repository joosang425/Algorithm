#include <bits/stdc++.h>
using namespace std;

int r, c, k, r_cnt, c_cnt, result;

int arr[101][101];

bool cmp(pair<int, int> a, pair<int, int> b) {
	if (a.second < b.second)
		return true;
	else if (a.second == b.second) {
		if (a.first < b.first)
			return true;
	}

	return false;
}

void solve() {
	if (r_cnt >= c_cnt) {
		int max_size = 0;

		for (int i = 1; i <= r_cnt; i++) {
			vector<pair<int, int>> v;
			int temp[101] = { 0, };

			for (int j = 1; j <= c_cnt; j++)
				temp[arr[i][j]]++;

			for (int j = 1; j <= 100; j++) {
				if (temp[j] != 0)
					v.push_back({ j, temp[j] });
			}

			sort(v.begin(), v.end(), cmp);

			for (int j = 1; j <= c_cnt; j++)
				arr[i][j] = 0;

			int idx = 1;
			for (int j = 0; j < v.size(); j++) {
				if (idx > 100)
					break;

				arr[i][idx++] = v[j].first;
				arr[i][idx++] = v[j].second;
			}

			max_size = max(max_size, idx - 1);
		}

		c_cnt = max_size;
	}
	else {
		int max_size = 0;

		for (int j = 1; j <= c_cnt; j++) {
			vector<pair<int, int>> v;
			int temp[101] = { 0, };

			for (int i = 1; i <= r_cnt; i++)
				temp[arr[i][j]]++;

			for (int i = 1; i <= 100; i++) {
				if (temp[i] != 0)
					v.push_back({ i, temp[i] });
			}

			sort(v.begin(), v.end(), cmp);

			for (int i = 1; i <= r_cnt; i++)
				arr[i][j] = 0;

			int idx = 1;
			for (int i = 0; i < v.size(); i++) {
				arr[idx++][j] = v[i].first;
				arr[idx++][j] = v[i].second;
			}

			max_size = max(max_size, idx - 1);
		}

		r_cnt = max_size;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> r >> c >> k;

	r_cnt = c_cnt = 3;
	
	for (int i = 1; i <= 3; i++) {
		for (int j = 1; j <= 3; j++) {
			cin >> arr[i][j];
		}
	}

	while (1) {
		if (arr[r][c] == k || result > 100)
			break;

		solve();
		result++;
	}

	if (result > 100)
		cout << -1 << '\n';
	else
		cout << result << '\n';

	return 0;
}