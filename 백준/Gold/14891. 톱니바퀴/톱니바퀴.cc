#include <bits/stdc++.h>
using namespace std;

// N -> 0, S -> 1
// -1 -> 반시계, 1 -> 시계

string str;
int arr[4][8], k, num, dir, result;
int isTurn[4];

// 톱니바퀴가 도는지 확인하는 함수
void check(int idx) {
	int cur = idx;

	// 현재 톱니바퀴에서 오른쪽으로
	for (int i = idx + 1; i < 4; i++) {
		// 같은 값을 가지면 그 즉시 종료
		if (arr[cur][2] == arr[i][6]) 
			break;

		// 아닌 경우 현재 톱니바퀴 반대 방향을 저장
		isTurn[i] = isTurn[cur] * -1;
		cur = i;
	}

	// 현재 톱니바퀴에서 왼쪽으로
	cur = idx;
	for (int i = idx - 1; i >= 0; i--) {
		if (arr[cur][6] == arr[i][2])
			break;

		isTurn[i] = isTurn[cur] * -1;
		cur = i;
	}
}

void move_(int idx) {
	int dir = isTurn[idx];

	// 회전 방향이 반시계
	if (dir == -1) {
		int temp = arr[idx][0];

		for (int i = 0; i < 7; i++)
			arr[idx][i] = arr[idx][i + 1];

		arr[idx][7] = temp;
	}
	// 회전 방향이 시계
	else {
		int temp = arr[idx][7];

		for (int i = 7; i > 0; i--)
			arr[idx][i] = arr[idx][i - 1];

		arr[idx][0] = temp;
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	for (int i = 0; i < 4; i++) {
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			arr[i][j] = str[j] - '0';
		}
	}

	cin >> k;
	for (int i = 0; i < k; i++) {
		cin >> num >> dir;

		memset(isTurn, 0, sizeof(isTurn));

		isTurn[num - 1] = dir;
		check(num - 1);

		// 0이 아닌 경우에는 회전한다는 뜻
		for (int j = 0; j < 4; j++) {
			if (isTurn[j] != 0)
				move_(j);
		}
	}

	for (int i = 0; i < 4; i++) {
		if (arr[i][0] == 1)
			result += pow(2, i);
	}

	cout << result << '\n';

	return 0;
}
