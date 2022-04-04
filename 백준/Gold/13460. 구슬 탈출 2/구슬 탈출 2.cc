#include <bits/stdc++.h>
using namespace std;

int n, m, result = 987654321;
char MAP[11][11];

int dir[4][2] = { {0,-1}, {0,1}, {-1,0},{1,0} };

pair<int, int> red, blue;

int reverse_dir(int num) {
	if (num == 0)
		return 1;
	else if (num == 1)
		return 0;
	else if (num == 2)
		return 3;
	else
		return 2;
}

void solve(int ry, int rx, int by, int bx, int cnt, int d) {
	if (cnt > 10)
		return;
	if (cnt >= result)
		return;

	bool red_flag = false;
	bool blue_flag = false;

	int nry = ry + dir[d][0];
	int nrx = rx + dir[d][1];
	while (1) {
		if (MAP[nry][nrx] == '#')
			break;
		else if (MAP[nry][nrx] == 'O') {
			red_flag = true;
			break;
		}

		nry = nry + dir[d][0];
		nrx = nrx + dir[d][1];
	}
	nry = nry - dir[d][0];
	nrx = nrx - dir[d][1];

	int nby = by + dir[d][0];
	int nbx = bx + dir[d][1];
	while (1) {
		if (MAP[nby][nbx] == '#')
			break;
		else if (MAP[nby][nbx] == 'O') {
			blue_flag = true;
			break;
		}

		nby = nby + dir[d][0];
		nbx = nbx + dir[d][1];
	}
	nby = nby - dir[d][0];
	nbx = nbx - dir[d][1];

	if (blue_flag)
		return;
	else {
		if (red_flag) {
			result = min(result, cnt);
			return;
		}
	}

	if (nry == nby && nrx == nbx) {
		int red_dist = abs(ry - nry) + abs(rx - nrx);
		int blue_dist = abs(by - nby) + abs(bx - nbx);

		if (red_dist > blue_dist) {
			nry = nry - dir[d][0];
			nrx = nrx - dir[d][1];
		}
		else {
			nby = nby - dir[d][0];
			nbx = nbx - dir[d][1];
		}
	}

	for (int i = 0; i < 4; i++) {
		if (i == d)
			continue;
		if (i == reverse_dir(d))
			continue;

		solve(nry, nrx, nby, nbx, cnt + 1, i);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	string str;
	for (int i = 0; i < n; i++) {
		cin >> str;
		for (int j = 0; j < str.size(); j++) {
			MAP[i][j] = str[j];

			if (MAP[i][j] == 'R') {
				red.first = i;
				red.second = j;
				MAP[i][j] = '.';
			}
			else if (MAP[i][j] == 'B') {
				blue.first = i;
				blue.second = j;
				MAP[i][j] = '.';
			}
		}
	}

	for (int i = 0; i < 4; i++) {
		int y = red.first;
		int x = red.second;
		int yy = blue.first;
		int xx = blue.second;

		solve(y, x, yy, xx, 1, i);
	}

	if (result > 10 || result == 987654321)
		cout << -1 << '\n';
	else
		cout << result << '\n';

	return 0;
}