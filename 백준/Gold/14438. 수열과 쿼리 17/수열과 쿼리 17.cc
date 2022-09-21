#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

const int MAX = 100001;
const int INF = 1000000001;

int n, m, a, b, c, arr[MAX];
vector<long long> min_tree;

void init(int node, int start, int end) {
	if (start == end) {
		min_tree[node] = arr[start];
		return;
	}

	int mid = (start + end) / 2;
	init(node * 2, start, mid);
	init(node * 2 + 1, mid + 1, end);

	min_tree[node] = min(min_tree[node * 2], min_tree[node * 2 + 1]);
}

void update(int node, int start, int end, int idx, int val) {
	if (idx < start || idx > end)
		return;
	if (start == end) {
		min_tree[node] = val;
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, idx, val);
	update(node * 2 + 1, mid + 1, end, idx, val);

	min_tree[node] = min(min_tree[node * 2], min_tree[node * 2 + 1]);
}

int cal(int node, int start, int end, int left, int right) {
	if (start > right || end < left)
		return INF;
	if (left <= start && end <= right)
		return min_tree[node];

	int mid = (start + end) / 2;
	return min(cal(node * 2, start, mid, left, right), cal(node * 2 + 1, mid + 1, end, left, right));
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n;

	int tree_height = (int)ceil(log2(n));
	int tree_size = (1 << (tree_height + 1));

	min_tree.resize(tree_size);

	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	init(1, 1, n);

	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> c;

		if (a == 1)
			update(1, 1, n, b, c);
		else
			cout << cal(1, 1, n, b, c) << '\n';
	}

	return 0;
}