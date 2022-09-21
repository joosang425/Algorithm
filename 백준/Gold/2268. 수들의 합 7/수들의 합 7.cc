#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int MAX = 1000001;

int n, m, a, b, c, arr[MAX];
vector<long long> sum_tree;

long long cal(int node, int start, int end, int left, int right) {
	if (start > right || end < left)
		return 0;
	if (left <= start && end <= right)
		return sum_tree[node];

	int mid = (start + end) / 2;
	return cal(node * 2, start, mid, left, right) + cal(node * 2 + 1, mid + 1, end, left, right);
}

void update(int node, int start, int end, int idx, int val) {
	if (idx < start || idx > end)
		return;
	if (start == end) {
		sum_tree[node] = val;
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, idx, val);
	update(node * 2 + 1, mid + 1, end, idx, val);

	sum_tree[node] = sum_tree[node * 2] + sum_tree[node * 2 + 1];
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;

	int tree_height = (int)ceil(log2(n));
	int tree_size = (1 << (tree_height + 1));

	sum_tree.resize(tree_size);

	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;

		if (a == 0) {
			if (b < c)
				cout << cal(1, 1, n, b, c) << '\n';
			else
				cout << cal(1, 1, n, c, b) << '\n';
		}
		else
			update(1, 1, n, b, c);
	}

	return 0;
}