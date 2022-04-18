#include <bits/stdc++.h>
using namespace std;

int Ability[21][21], Selected[21], N, Result = 987654321;

void Difference(int Current, int Member) {
	vector<int> Start, Link;
	int Start_Score = 0, Link_Score = 0;

	if (Member == N / 2) {
		for (int i = 0; i < N; i++) {
			if (Selected[i])
				Start.push_back(i);
			else
				Link.push_back(i);
		}

		for (int i = 0; i < N / 2; i++) {
			for (int j = 0; j < N / 2; j++) {
				Start_Score += Ability[Start[i]][Start[j]];
				Link_Score += Ability[Link[i]][Link[j]];
			}
		}

		Result = min(Result, abs(Start_Score - Link_Score));

		return;
	}

	for (int i = Current; i < N; i++) {
		if (!Selected[i]) {
			Selected[i] = true;
			Difference(i, Member + 1);
			Selected[i] = false;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cin >> Ability[i][j];

	Difference(0, 0);

	cout << Result;

	return 0;
}