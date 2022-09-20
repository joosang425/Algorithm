#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 100001;
const int INF = 1000000001;

int arr[MAX];
vector<int> min_tree, max_tree;

int n, m, a, b;

void init(int node, int start, int end) {
	if (start == end) {
		min_tree[node] = arr[start];
		max_tree[node] = arr[start];

		return;
	}

	int mid = (start + end) / 2;
	init(node * 2, start, mid);
	init(node * 2 + 1, mid + 1, end);

	min_tree[node] = min(min_tree[node * 2], min_tree[node * 2 + 1]);
	max_tree[node] = max(max_tree[node * 2], max_tree[node * 2 + 1]);
}

pair<int,int> cal_tree(int node, int start, int end, int left, int right) {
	if (end < left || start > right)
		return { INF, 0 };
	if (left <= start && right >= end)
		return { min_tree[node], max_tree[node] };

	int mid = (start + end) / 2;
	pair<int, int> left_tree, right_tree;

	left_tree = cal_tree(node * 2, start, mid, left, right);
	right_tree = cal_tree(node * 2 + 1, mid + 1, end, left, right);

	int left_temp = min(left_tree.first, right_tree.first);
	int right_temp = max(left_tree.second, right_tree.second);

	return { left_temp, right_temp };
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	int tree_height = (int)ceil(log2(n));
	int tree_size = (1 << (tree_height + 1));

	min_tree.resize(tree_size);
	max_tree.resize(tree_size);

	init(1, 1, n);

	for (int i = 0; i < m; i++) {
		cin >> a >> b;

		pair<int, int> temp = cal_tree(1, 1, n, a, b);

		cout << temp.first << ' ' << temp.second << '\n';
	}

	return 0;
}