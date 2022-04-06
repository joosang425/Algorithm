#include <bits/stdc++.h>
using namespace std;

int n, ans = -987654321;
char c;

vector<int> num;
vector<char> oper;

int calc(int num1, char oper, int num2) {
	if (oper == '+')
		return num1 + num2;
	else if (oper == '*')
		return num1 * num2;
	else if (oper == '-')
		return num1 - num2;
}

void dfs(int idx, int result) {
	if (idx >= oper.size()) {
		ans = max(ans, result);
		return;
	}

	// 현재 연산자에서 괄호를 추가한 경우
	int cur = calc(result, oper[idx], num[idx + 1]);
	dfs(idx + 1, cur);

	// 현재 연산자가 아닌 다음 연산자에 괄호를 추가한 경우
	if (idx + 1 < oper.size()) {
		int next = calc(num[idx + 1], oper[idx + 1], num[idx + 2]);
		int cur = calc(result, oper[idx], next);
		dfs(idx + 2, cur);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> c;

		if (c >= '0' && c <= '9')
			num.push_back((c - '0'));
		else
			oper.push_back(c);
	}

	dfs(0, num[0]);

	cout << ans << '\n';

	return 0;
}