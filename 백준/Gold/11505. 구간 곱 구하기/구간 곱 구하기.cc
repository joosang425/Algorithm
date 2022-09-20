#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX = 1000001;
const int MOD = 1000000007;

int n, m, k;
long long a, b, c, arr[MAX]; 

vector<long long> mul_tree;

void init(int node, int start, int end){
	if (start == end) {
		mul_tree[node] = arr[start];
		return;
	}

	int mid = (start + end) / 2;
	init(node * 2, start, mid);
	init(node * 2 + 1, mid + 1, end);

	mul_tree[node] = (mul_tree[node * 2] * mul_tree[node * 2 + 1]) % MOD;
}

void update(int node, int start, int end, int idx, long long val) {
	if (idx < start || idx > end)
		return;
	if (start == end) {
		mul_tree[node] = val;
		return;
	}

	int mid = (start + end) / 2;
	update(node * 2, start, mid, idx, val);
	update(node * 2 + 1, mid + 1, end, idx, val);
	mul_tree[node] = (mul_tree[node * 2] * mul_tree[node * 2 + 1]) % MOD;
}

long long cal(int node, int start, int end, int left, int right) {
	if (start > right || end < left)
		return 1;
	if (left <= start && end <= right)
		return mul_tree[node];

	int mid = (start + end) / 2;
	return (cal(node * 2, start, mid, left, right) * cal(node * 2 + 1, mid + 1, end, left, right)) % MOD;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	cin >> n >> m >> k;

	int tree_height = (int)ceil(log2(n));
	int tree_size = (1 << (tree_height + 1));

	mul_tree.resize(tree_size);

	for (int i = 1; i <= n; i++)
		cin >> arr[i];

	init(1, 1, n);

	for (int i = 0; i < m + k; i++) {
		cin >> a >> b >> c;

		if (a == 1)
			update(1, 1, n, b, c);
		else
			cout << cal(1, 1, n, b, c) << '\n';
	}

	return 0;
}