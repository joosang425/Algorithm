#include <bits/stdc++.h>
using namespace std;

int r, c;
char arr[25][25];
bool connected[25][25][4];

int dir[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

pair<int, int> st, ed;

void find_pipe(int cy, int cx) {
	int temp[4] = { 0, };

	for (int i = 0; i < 4; i++) {
		int ny = cy + dir[i][0];
		int nx = cx + dir[i][1];

		if (i == 0) {
			if (arr[ny][nx] == '|' || arr[ny][nx] == '+' || arr[ny][nx] == '1' || arr[ny][nx] == '4')
				temp[i] = 1;
		}
		else if (i == 1) {
			if (arr[ny][nx] == '|' || arr[ny][nx] == '+' || arr[ny][nx] == '2' || arr[ny][nx] == '3')
				temp[i] = 1;
		}
		else if (i == 2) {
			if (arr[ny][nx] == '-' || arr[ny][nx] == '+' || arr[ny][nx] == '1' || arr[ny][nx] == '2')
				temp[i] = 1;
		}
		else if (i == 3) {
			if (arr[ny][nx] == '-' || arr[ny][nx] == '+' || arr[ny][nx] == '3' || arr[ny][nx] == '4')
				temp[i] = 1;
		}
	}

	cy++, cx++;

	if (temp[0] && temp[1] && temp[2] && temp[3])
		cout << cy << ' ' << cx << ' ' << '+' << '\n';
	else if (temp[0] && temp[1] && !temp[2] && !temp[3])
		cout << cy << ' ' << cx << ' ' << '|' << '\n';
	else if (!temp[0] && !temp[1] && temp[2] && temp[3])
		cout << cy << ' ' << cx << ' ' << '-' << '\n';
	else if (!temp[0] && temp[1] && !temp[2] && temp[3])
		cout << cy << ' ' << cx << ' ' << '1' << '\n';
	else if (temp[0] && !temp[1] && !temp[2] && temp[3])
		cout << cy << ' ' << cx << ' ' << '2' << '\n';
	else if (temp[0] && !temp[1] && temp[2] && !temp[3])
		cout << cy << ' ' << cx << ' ' << '3' << '\n';
	else if (!temp[0] && temp[1] && temp[2] && !temp[3])
		cout << cy << ' ' << cx << ' ' << '4' << '\n';
}

void solve(int sy, int sx, int d) {
	if (arr[sy][sx] == '.')
		find_pipe(sy, sx);

	if (arr[sy][sx] == '|') {
		if (d == 0)
			solve(sy - 1, sx, d);
		else
			solve(sy + 1, sx, d);
	}
	else if (arr[sy][sx] == '-') {
		if (d == 2)
			solve(sy, sx - 1, d);
		else
			solve(sy, sx + 1, d);
	}
	else if (arr[sy][sx] == '+') {
		if (d == 0)
			solve(sy - 1, sx, d);
		else if (d == 1)
			solve(sy + 1, sx, d);
		else if (d == 2)
			solve(sy, sx - 1, d);
		else
			solve(sy, sx + 1, d);
	}
	else if (arr[sy][sx] == '1') {
		if (d == 0)
			solve(sy, sx + 1, 3);
		else
			solve(sy + 1, sx, 1);
	}
	else if (arr[sy][sx] == '2') {
		if (d == 1)
			solve(sy, sx + 1, 3);
		else
			solve(sy - 1, sx, 0);
	}
	else if (arr[sy][sx] == '3') {
		if (d == 1)
			solve(sy, sx - 1, 2);
		else
			solve(sy - 1, sx, 0);
	}
	else if (arr[sy][sx] == '4') {
		if (d == 0)
			solve(sy, sx - 1, 2);
		else
			solve(sy + 1, sx, 1);
	}
}

int ch_dir(int sy, int sx) {
	int d = -1;

	for (int i = 0; i < 4; i++) {
		int ny = sy + dir[i][0];
		int nx = sx + dir[i][1];

		if (ny < 0 || ny >= r || nx < 0 || nx >= c)
			continue;
		if (arr[ny][nx] == '.')
			continue;

		if (i == 0) {
			if (arr[ny][nx] == '|' || arr[ny][nx] == '+' || arr[ny][nx] == '1' || arr[ny][nx] == '4')
				d = 0;
		}
		else if (i == 1) {
			if (arr[ny][nx] == '|' || arr[ny][nx] == '+' || arr[ny][nx] == '2' || arr[ny][nx] == '3')
				d = 1;
		}
		else if (i == 2) {
			if (arr[ny][nx] == '-' || arr[ny][nx] == '+' || arr[ny][nx] == '1' || arr[ny][nx] == '2')
				d = 2;
		}
		else if (i == 3) {
			if (arr[ny][nx] == '-' || arr[ny][nx] == '+' || arr[ny][nx] == '3' || arr[ny][nx] == '4')
				d = 3;
		}
	}

	return d;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> r >> c;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cin >> arr[i][j];

			if (arr[i][j] == 'M') {
				st.first = i;
				st.second = j;
			}
			else if (arr[i][j] == 'Z') {
				ed.first = i;
				ed.second = j;
			}
		}
	}

	int temp_d = ch_dir(st.first, st.second);

	if (temp_d == -1) {
		temp_d = ch_dir(ed.first, ed.second);

		ed.first += dir[temp_d][0];
		ed.second += dir[temp_d][1];

		solve(ed.first, ed.second, temp_d);
	}
	else {
		st.first += dir[temp_d][0];
		st.second += dir[temp_d][1];

		solve(st.first, st.second, temp_d);
	}

	return 0;
}