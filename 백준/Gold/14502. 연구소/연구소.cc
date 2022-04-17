#include <bits/stdc++.h>
#define MAX 8
using namespace std;

int N, M, MAP[MAX][MAX], Temp_MAP[MAX][MAX], Result;

vector<pair<int, int>> Virus;
int Dir_Y[4] = { -1,1,0,0 };
int Dir_X[4] = { 0,0,-1,1 };

bool CanGo(int Y, int X) {
	if (Y < 0 || Y >= N || X < 0 || X >= M)
		return false;

	return true;
}

void Bfs(int Y, int X) {
	queue<pair<int, int>> q;
	q.push({ Y,X });

	while (!q.empty()) {
		int Cur_Y = q.front().first;
		int Cur_X = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int next_Y = Cur_Y + Dir_Y[i];
			int next_X = Cur_X + Dir_X[i];

			if (CanGo(next_Y, next_X) && Temp_MAP[next_Y][next_X] == 0) {
				q.push({ next_Y,next_X });
				Temp_MAP[next_Y][next_X] = 2;
			}
		}
	}
}

void Select(int Idx, int Cnt, int MAP[][8]) {
	if (Cnt == 3) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				Temp_MAP[i][j] = MAP[i][j];
			}
		}

		int Count = 0;
		for (int i = 0; i < Virus.size(); i++)
			Bfs(Virus[i].first, Virus[i].second);

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				if (Temp_MAP[i][j] == 0)
					Count++;
			}
		}

		Result = max(Result, Count);
		return;
	}

	for (int i = Idx; i < N * M; i++) {
		if (MAP[i / M][i % M] == 0) {
			MAP[i / M][i % M] = 1;
			Select(i, Cnt + 1, MAP);
			MAP[i / M][i % M] = 0;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);	cout.tie(0);

	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> MAP[i][j];
			if (MAP[i][j] == 2)
				Virus.push_back({ i,j });
		}
	}

	Select(0, 0, MAP);
	cout << Result;

	return 0;
}