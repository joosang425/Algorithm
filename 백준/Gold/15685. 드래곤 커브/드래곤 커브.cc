#include <bits/stdc++.h>
using namespace std;

int n, y, x, d, g, result, arr[101][101];
int dir[4][2] = { {0, 1}, {-1,0},{0,-1},{1,0} };

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> x >> y >> d >> g;

		vector<int> v;
		v.push_back(d);

		// 세대 크기만큼 진행
		for (int j = 0; j < g; j++) {
			// 계속해서 추가되기 때문에 원래의 크기 저장
			int size = v.size();

			// 커브가 끝점에서 이루어지므로 끝에서 진행
			for (int t = size - 1; t >= 0; t--) {
				int cur = v[t];

				v.push_back((cur + 1) % 4);
			}
		}

		arr[y][x] = 1;
		// 저장해놓은 벡터의 방향대로 진행
		for (int j = 0; j < v.size(); j++) {
			y += dir[v[j]][0];
			x += dir[v[j]][1];

			arr[y][x] = 1;
		}
	}

	// 네 꼭짓점이므로 최대크기의 -1만큼만 진행
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (arr[i][j] && arr[i][j + 1] && arr[i + 1][j] && arr[i + 1][j + 1])
				result++;
		}
	}

	cout << result << '\n';

	return 0;
}