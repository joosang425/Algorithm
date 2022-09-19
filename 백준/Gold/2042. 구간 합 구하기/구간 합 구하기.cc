#include <iostream>
using namespace std;

const int MAX = 1000001;
typedef long long ll;

ll arr[MAX], n, m, k;
ll sum[MAX], a, b, c;

void update(ll idx, ll val) {
	while (idx <= n) {
		sum[idx] += val;

		idx += (idx & -idx);
	}
}

ll cal_sum(ll idx) {
	ll temp = 0;

	while (idx > 0) {
		temp += sum[idx];

		idx -= (idx & -idx);
	}

	return temp;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		cin >> arr[i];

		update(i, arr[i]);
	}

	for (int i = 0; i < m + k; i++) {
		cin >> a >> b >> c;

		if (a == 1) {
			ll diff = c - arr[b];

			update(b, diff);
			arr[b] = c;
		}	// update
		else
			cout << cal_sum(c) - cal_sum(b - 1) << '\n';	// sum 구하기
	}

	return 0;
}