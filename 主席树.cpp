// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10;
struct Node {
	int l, r, sum;
}T[maxn * 40];

int root[maxn], arr[maxn], n, m, cnt = 0;
vector<int> v;
int getid(int x) {

	return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}

void update(int l, int r, int& x, int y, int pos) {
	T[++cnt] = T[y];
	x = cnt;
	T[x].sum++;
	if (l == r) return;
	int mid = (l + r) >> 1;
	if (pos <= mid) update(l, mid, T[x].l, T[y].l, pos);
	else update(mid + 1, r, T[x].r, T[y].r, pos);
}

int query(int l, int r, int x, int y, int k) {
	if (l == r)return l;
	int sum = T[T[y].l].sum - T[T[x].l].sum;
	int mid = (l + r) >> 1;
	if (sum >= k) return query(l, mid, T[x].l, T[y].l, k);
	else return query(mid + 1, r, T[x].r, T[y].r, k - sum);

}


int main() {
	cin >> n >> m;
	int i;
	for (i = 1; i <= n; i++) {
		cin >> arr[i];
		v.push_back(arr[i]);
	}
	sort(v.begin(), v.end());
	v.erase(unique(v.begin(), v.end()), v.end());
	for (i = 1; i <= n; i++) {
		update(1, n, root[i], root[i - 1], getid(arr[i]));
	}
	int a, b, k;
	for (i = 1; i <= m; i++) {
		cin >> a >> b >> k;
		cout << v[query(1, n, root[a - 1], root[b], k) - 1] << endl;
	}
	return 0;
}