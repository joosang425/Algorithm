#include <bits/stdc++.h>
using namespace std;

string str;
int k;

bool check[4];
int remem[4];
int chain[4][8];

void turn(int cur) {
	int temp = chain[cur][7];

	for (int i = 6; i >= 0; i--)
		chain[cur][i + 1] = chain[cur][i];

	chain[cur][0] = temp;
}

void re_turn(int cur) {
	int temp = chain[cur][0];

	for (int i = 1; i < 8; i++)
		chain[cur][i - 1] = chain[cur][i];

	chain[cur][7] = temp;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 4; i++) {
		cin >> str;

		for (int j = 0; j < 8; j++)
			chain[i][j] = str[j] - '0';
	}

	cin >> k;
	int num1, num2;

	//	1 = 시계 방향, -1 = 반시계 방향

	for (int i = 0; i < k; i++) {
		memset(check, false, sizeof(check));
		memset(remem, 0, sizeof(remem));

		cin >> num1 >> num2;

		num1--;

		remem[num1] = num2;
		check[num1] = true;

		for (int j = num1 - 1; j >= 0; j--) {
			if (!check[j + 1])
				continue;
			if (chain[j + 1][6] == chain[j][2])
				continue;

			remem[j] = remem[j + 1] * -1;
			check[j] = true;
		}

		for (int j = num1 + 1; j < 4; j++) {
			if (!check[j - 1])
				continue;
			if (chain[j - 1][2] == chain[j][6])
				continue;

			remem[j] = remem[j - 1] * -1;
			check[j] = true;
		}

		for (int j = 0; j < 4; j++) {
			if (!check[j])
				continue;

			if (remem[j] == 1) 
				turn(j);
			else
				re_turn(j);
		}
	}

	//	N = 0, S = 1

	int result = 0;
	for (int i = 0; i < 4; i++) {
		if (chain[i][0])
			result += pow(2, i);
	}

	cout << result << '\n';

	return 0;
}