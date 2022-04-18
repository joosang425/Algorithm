#include <bits/stdc++.h>
#define INF 987654321
using namespace std;

int N, Current = 0;
int Operand[101];
int Operator[4];

int Result, Max = -INF, Min = INF;

void Optimal(int Result, int Idx) {
	if (Idx == N) {
		Max = max(Max, Result);
		Min = min(Min, Result);

		return;
	}

	for (int i = 0; i < 4; i++) {
		if (Operator[i] > 0) {
			Operator[i]--;
			switch (i) {
			case 0:
				Optimal(Result + Operand[Idx], Idx + 1);
				break;
			case 1:
				Optimal(Result - Operand[Idx], Idx + 1);
				break;
			case 2:
				Optimal(Result * Operand[Idx], Idx + 1);
				break;
			default:
				Optimal(Result / Operand[Idx], Idx + 1);
				break;
			}
			Operator[i]++;
		}
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);	cout.tie(0);

	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> Operand[i];

	for (int i = 0; i < 4; i++)
		cin >> Operator[i];

	Optimal(Operand[0], 1);

	cout << Max << '\n';
	cout << Min;

	return 0;
}