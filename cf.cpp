#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n;
	int i, num, li, j;
	cin >> n;
	vector<int>  v;
	vector<int> maxx;
	int num1, num2;
	int cnt = 0;
	for (i = 0; i < n; i++) {
		cin >> li;
		bool flag = false;
		cin >> num;
		num1 = num2 = num;
		for (j = 1; j < li; j++) {
			cin >> num;
			if (num > num2)
				flag = true;
			num2 = min(num2, num);
			num1 = max(num1, num);
		}
		if (flag) {
			maxx.push_back(maxn);
			v.push_back(-1);
		}
		else {
			maxx.push_back(num1);
			v.push_back(num2);
		}
	}
	sort(maxx.begin(), maxx.end());
	long long ans = 0;
	for (i = 0; i < v.size(); i++) {
		ans += (maxx.end() - upper_bound(maxx.begin(), maxx.end(), v[i]));
	}
	cout << ans << endl;
	return 0;
}