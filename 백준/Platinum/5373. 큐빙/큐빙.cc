#include <bits/stdc++.h>
using namespace std;

vector<char> v[7];
int tc, n;

int check(char type)
{
	if (type == 'U') return 1;
	else if (type == 'D') return 2;
	else if (type == 'F') return 3;
	else if (type == 'B') return 4;
	else if (type == 'L') return 5;
	else if (type == 'R') return 6;
}

//	solve에서는 해당되는 앞, 뒤 면을 빼고 계산
//	하지만 큐브를 돌리면 해당되는 면도 변화가 생기기 때문에
void remain(char type, char d)
{
	int idx = check(type);

	if (d == '+')
	{
		int temp = v[idx][0];
		v[idx][0] = v[idx][6];
		v[idx][6] = v[idx][8];
		v[idx][8] = v[idx][2];
		v[idx][2] = temp;

		int temp1 = v[idx][1];
		v[idx][1] = v[idx][3];
		v[idx][3] = v[idx][7];
		v[idx][7] = v[idx][5];
		v[idx][5] = temp1;
	}
	else if (d == '-')
	{
		int temp = v[idx][0];
		v[idx][0] = v[idx][2];
		v[idx][2] = v[idx][8];
		v[idx][8] = v[idx][6];
		v[idx][6] = temp;

		int temp1 = v[idx][1];
		v[idx][1] = v[idx][5];
		v[idx][5] = v[idx][7];
		v[idx][7] = v[idx][3];
		v[idx][3] = temp1;
	}
}

void solve(char type, char d) {
	if (type == 'U') {
		if (d == '+') {
			char temp = v[3][0];
			char temp1 = v[3][1];
			char temp2 = v[3][2];

			v[3][0] = v[6][0];
			v[3][1] = v[6][1];
			v[3][2] = v[6][2];

			v[6][0] = v[4][0];
			v[6][1] = v[4][1];
			v[6][2] = v[4][2];

			v[4][0] = v[5][0];
			v[4][1] = v[5][1];
			v[4][2] = v[5][2];

			v[5][0] = temp;
			v[5][1] = temp1;
			v[5][2] = temp2;
		}
		else {
			char temp = v[3][0];
			char temp1 = v[3][1];
			char temp2 = v[3][2];

			v[3][0] = v[5][0];
			v[3][1] = v[5][1];
			v[3][2] = v[5][2];

			v[5][0] = v[4][0];
			v[5][1] = v[4][1];
			v[5][2] = v[4][2];

			v[4][0] = v[6][0];
			v[4][1] = v[6][1];
			v[4][2] = v[6][2];

			v[6][0] = temp;
			v[6][1] = temp1;
			v[6][2] = temp2;
		}
	}
	else if (type == 'D') {
		if (d == '+') {
			char temp = v[6][6];
			char temp1 = v[6][7];
			char temp2 = v[6][8];

			v[6][6] = v[3][6];
			v[6][7] = v[3][7];
			v[6][8] = v[3][8];

			v[3][6] = v[5][6];
			v[3][7] = v[5][7];
			v[3][8] = v[5][8];

			v[5][6] = v[4][6];
			v[5][7] = v[4][7];
			v[5][8] = v[4][8];

			v[4][6] = temp;
			v[4][7] = temp1;
			v[4][8] = temp2;
		}
		else {
			char temp = v[6][6];
			char temp1 = v[6][7];
			char temp2 = v[6][8];

			v[6][6] = v[4][6];
			v[6][7] = v[4][7];
			v[6][8] = v[4][8];

			v[4][6] = v[5][6];
			v[4][7] = v[5][7];
			v[4][8] = v[5][8];

			v[5][6] = v[3][6];
			v[5][7] = v[3][7];
			v[5][8] = v[3][8];

			v[3][6] = temp;
			v[3][7] = temp1;
			v[3][8] = temp2;
		}
	}
	else if (type == 'F') {
		if (d == '+') {
			char temp = v[1][6];
			char temp1 = v[1][7];
			char temp2 = v[1][8];

			v[1][6] = v[5][8];
			v[1][7] = v[5][5];
			v[1][8] = v[5][2];

			v[5][8] = v[2][2];
			v[5][5] = v[2][1];
			v[5][2] = v[2][0];

			v[2][2] = v[6][0];
			v[2][1] = v[6][3];
			v[2][0] = v[6][6];

			v[6][0] = temp;
			v[6][3] = temp1;
			v[6][6] = temp2;
		}
		else {
			char temp = v[1][6];
			char temp1 = v[1][7];
			char temp2 = v[1][8];

			v[1][6] = v[6][0];
			v[1][7] = v[6][3];
			v[1][8] = v[6][6];

			v[6][0] = v[2][2];
			v[6][3] = v[2][1];
			v[6][6] = v[2][0];

			v[2][2] = v[5][8];
			v[2][1] = v[5][5];
			v[2][0] = v[5][2];

			v[5][8] = temp;
			v[5][5] = temp1;
			v[5][2] = temp2;
		}
	}
	else if (type == 'B') {
		if (d == '+') {
			char temp = v[1][0];
			char temp1 = v[1][1];
			char temp2 = v[1][2];

			v[1][0] = v[6][2];
			v[1][1] = v[6][5];
			v[1][2] = v[6][8];

			v[6][2] = v[2][8];
			v[6][5] = v[2][7];
			v[6][8] = v[2][6];

			v[2][8] = v[5][6];
			v[2][7] = v[5][3];
			v[2][6] = v[5][0];

			v[5][6] = temp;
			v[5][3] = temp1;
			v[5][0] = temp2;
		}
		else {
			char temp = v[1][0];
			char temp1 = v[1][1];
			char temp2 = v[1][2];

			v[1][0] = v[5][6];
			v[1][1] = v[5][3];
			v[1][2] = v[5][0];

			v[5][6] = v[2][8];
			v[5][3] = v[2][7];
			v[5][0] = v[2][6];

			v[2][8] = v[6][2];
			v[2][7] = v[6][5];
			v[2][6] = v[6][8];

			v[6][2] = temp;
			v[6][5] = temp1;
			v[6][8] = temp2;
		}
	}
	else if (type == 'L') {
		if (d == '+') {
			char temp = v[3][0];
			char temp1 = v[3][3];
			char temp2 = v[3][6];

			v[3][0] = v[1][0];
			v[3][3] = v[1][3];
			v[3][6] = v[1][6];

			v[1][0] = v[4][8];
			v[1][3] = v[4][5];
			v[1][6] = v[4][2];

			v[4][8] = v[2][0];
			v[4][5] = v[2][3];
			v[4][2] = v[2][6];

			v[2][0] = temp;
			v[2][3] = temp1;
			v[2][6] = temp2;
		}
		else {
			char temp = v[3][0];
			char temp1 = v[3][3];
			char temp2 = v[3][6];

			v[3][0] = v[2][0];
			v[3][3] = v[2][3];
			v[3][6] = v[2][6];

			v[2][0] = v[4][8];
			v[2][3] = v[4][5];
			v[2][6] = v[4][2];

			v[4][8] = v[1][0];
			v[4][5] = v[1][3];
			v[4][2] = v[1][6];

			v[1][0] = temp;
			v[1][3] = temp1;
			v[1][6] = temp2;
		}
	}
	else if (type == 'R') {
		if (d == '+') {
			char temp = v[3][2];
			char temp1 = v[3][5];
			char temp2 = v[3][8];

			v[3][2] = v[2][2];
			v[3][5] = v[2][5];
			v[3][8] = v[2][8];

			v[2][2] = v[4][6];
			v[2][5] = v[4][3];
			v[2][8] = v[4][0];

			v[4][6] = v[1][2];
			v[4][3] = v[1][5];
			v[4][0] = v[1][8];

			v[1][2] = temp;
			v[1][5] = temp1;
			v[1][8] = temp2;
		}
		else {
			char temp = v[3][2];
			char temp1 = v[3][5];
			char temp2 = v[3][8];

			v[3][2] = v[1][2];
			v[3][5] = v[1][5];
			v[3][8] = v[1][8];

			v[1][2] = v[4][6];
			v[1][5] = v[4][3];
			v[1][8] = v[4][0];

			v[4][6] = v[2][2];
			v[4][3] = v[2][5];
			v[4][0] = v[2][8];

			v[2][2] = temp;
			v[2][5] = temp1;
			v[2][8] = temp2;
		}
	}

	remain(type, d);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> tc;

	while (tc--) {
		cin >> n;

		for (int i = 1; i < 7; i++)
			v[i].clear();

		//	1: 위, 2: 아래, 3: 앞, 4: 뒤, 5: 왼, 6: 오
		for (int i = 1; i < 7; i++) {
			for (int j = 0; j < 9; j++) {
				switch (i) {
				case 1:
					v[i].push_back('w');
					break;
				case 2:
					v[i].push_back('y');
					break;
				case 3:
					v[i].push_back('r');
					break;
				case 4:
					v[i].push_back('o');
					break;
				case 5:
					v[i].push_back('g');
					break;
				case 6:
					v[i].push_back('b');
					break;
				}
			}
		}

		string str;

		for (int i = 0; i < n; i++) {
			cin >> str;

			char rotate = str[0];
			char d = str[1];

			solve(rotate, d);
		}

		int cnt = 0;
		for (int i = 0; i < 9; i++) {
			cout << v[1][i];
			cnt++;

			if (cnt == 3) {
				cout << '\n';
				cnt = 0;
			}
		}
	}

	return 0;
}