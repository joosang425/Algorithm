#include <bits/stdc++.h>
using namespace std;

string n;
int m, result;
bool visited[1000001][8];

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	queue<pair<string, int>> q;

	q.push({ n, 0 });

	while (!q.empty()) {
		string str = q.front().first;
		int ck = q.front().second;
		q.pop();

		if (ck == m) {
			result = max(result, stoi(str));
			continue;
		}

		string cur_str = str;
		for (int i = 0; i < cur_str.length() - 1; i++) {
			for (int j = i + 1; j < cur_str.length(); j++) {
				swap(cur_str[i], cur_str[j]);

				if (cur_str[0] == '0' || visited[stoi(cur_str)][ck + 1]) {
					swap(cur_str[j], cur_str[i]);
					continue;
				}

				q.push({ cur_str, ck + 1 });
				visited[stoi(cur_str)][ck + 1] = true;
				swap(cur_str[j], cur_str[i]);
			}
		}
	}

	if (result == 0)
		cout << -1 << '\n';
	else
		cout << result << '\n';

	return 0;
}