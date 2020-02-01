#include<bits/stdc++.h>
using namespace std;

const int maxn = 1000;
int dp[maxn];
int val[maxn], w[maxn];

int main()
{
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	while (t--)	{
		int n, m, p, h, c;
		cin >> n >> m;
		int i, j;
		int cnt = 0;
		memset(val, 0, sizeof(val));
		memset(w, 0, sizeof(w));
		for (i = 0; i < m; i++){
			cin >> p >> h >> c;
			for (j = 1; j <= c; j *= 2){
				val[cnt] = p * j;
				w[cnt] = h * j;
				c -= j;
				cnt++;
			}
			if (c > 0){
				val[cnt] = c * p;
				w[cnt] = h * c;
				cnt++;
			}
		}
		memset(dp, 0, sizeof(dp));
		for (i = 0; i < cnt; i++) {
			for (j = n; j >= val[i]; j--)
				dp[j] = max(dp[j], dp[j - val[i]] + w[i]);
		}
		cout << dp[n] << endl;
	}
	return 0;
}