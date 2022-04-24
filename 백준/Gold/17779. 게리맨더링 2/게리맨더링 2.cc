#include <bits/stdc++.h>
using namespace std;

int n, arr[21][21], temp[21][21], result = 987654321;

vector<pair<int, int>> v;

int calc() {
	int score[6] = { 0, };

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			score[temp[i][j]] += arr[i][j];
		}
	}

	sort(score, score + 6);
	
	int result = score[5] - score[1];

	return result;
}

void marking() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			temp[i][j] = 5;
		}
	}

	//	1번 선거구
	int cnt = 0;
	for (int i = 1; i < v[1].first; i++) {
		if (i >= v[0].first)
			cnt++;
		for (int j = 1; j <= v[0].second - cnt; j++)
			temp[i][j] = 1;
	}

	//	2번 선거구
	cnt = 0;
	for (int i = 1; i <= v[2].first; i++) {
		if (i > v[0].first)
			cnt++;
		for (int j = v[0].second + 1 + cnt; j <= n; j++)
			temp[i][j] = 2;
	}

	//	3번 선거구
	cnt = 0;
	for (int i = n; i >= v[1].first; i--) {
		if (i < v[3].first)
			cnt++;
		for (int j = 1; j < v[3].second - cnt; j++)
			temp[i][j] = 3;
	}

	//	4번 선거구
	cnt = 0;
	for (int i = n; i > v[2].first; i--) {
		if (i <= v[3].first)
			cnt++;
		for (int j = v[3].second + cnt; j <= n; j++)
			temp[i][j] = 4;
	}
}

bool isTrue(int x, int y, int d1, int d2) {
	if (x + d1 > n || y - d1 < 1)
		return false;
	if (x + d2 > n || y + d2 > n)
		return false;
	if (x + d1 + d2 > n || y + d2 - d1 < 1)
		return false;

	return true;
}

// 기준점 정하기 
void solve() {
	for (int x = 1; x <= n - 2; x++) {
		for (int y = 2; y <= n - 2; y++) {
			for (int d1 = 1; d1 <= n; d1++) {
				for (int d2 = 1; d2 <= n; d2++) {
					if (isTrue(x, y, d1, d2)) {
						v.clear();

						v.push_back({ x,y });
						v.push_back({ x + d1, y - d1 });
						v.push_back({ x + d2, y + d2 });
						v.push_back({ x + d1 + d2, y + d2 - d1 });

						marking();

						result = min(result, calc());
					}
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> arr[i][j];
		}
	}

	solve();

	cout << result << '\n';

	return 0;
}