#include <bits/stdc++.h>
using namespace std;

int n, m, result = 987654321;

bool selected[13];
vector<pair<int, int>> chicken, house;

int dis_cal(vector<int> choose) {
	int sum = 0;

	// 각 집별로 가까운 치킨집 구하기
	for (int i = 0; i < house.size(); i++) {
		int dis = 987654321;

		for (int j = 0; j < choose.size(); j++) {
			int idx = choose[j];

			int temp_dis = abs(house[i].first - chicken[idx].first) + abs(house[i].second - chicken[idx].second);
			
			dis = min(dis, temp_dis);
		}

		sum += dis;
	}

	return sum;
}

void dfs(int idx, int cnt) {
	// 총 m개가 선택이 되면 치킨 거리 구하기
	if (cnt == m) {
		vector<int> choose;

		for (int i = 0; i < chicken.size(); i++) {
			if (selected[i])
				choose.push_back(i);
		}

		result = min(result, dis_cal(choose));
		return;
	}

	for (int i = idx; i < chicken.size(); i++) {
		if (selected[i])
			continue;

		selected[i] = true;
		dfs(i, cnt + 1);
		selected[i] = false;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	int num;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> num;

			// 치킨집, 집의 위치 저장
			if (num == 2)
				chicken.push_back({ i,j });
			else if (num == 1)
				house.push_back({ i,j });
		}
	}

	// 조합
	dfs(0, 0);

	cout << result << '\n';

	return 0;
}