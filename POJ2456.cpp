#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int n, m;
vector<int> v;

bool judge(int k) {
	int cnt = v[0], num = 1;
	for (int i = 1; i < n; i++) {
		if (v[i] - cnt >= k) {
			cnt = v[i];
			num++;
		}
		if (num >= m)return true;
	}
	return false;
}


void slove() {
	int l = 1, r = v[n - 1] - v[0];
	while (l < r) {
		int mid = (r + l) >> 1;
		if (judge(mid))l = mid + 1;
		else r = mid;
	}
	cout << (r - 1) << endl;
}


int main() {
	ios::sync_with_stdio(false);
	while (cin >> n >> m) {
		v.clear();
		v.resize(n);
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}
		sort(v.begin(), v.end());
		slove();
	}
	return 0;
}