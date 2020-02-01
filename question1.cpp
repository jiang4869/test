#include<bits/stdc++.h>
using namespace std;

/*
n 人数 1<n<1e5
m 项目数 1<m<1e2
*/


const int maxn = 1e5;
const int maxm = 1e2;
long long vec[maxn][maxm];
bool sign[maxn];
int n, m;
long long ans = 0;
long long sum = 0;

void dfs(int cnt) {
	if (cnt == m) {
		ans = max(sum, ans);
		return;
	}
	else {
		int i;
		for (i = 0; i < n; i++) {
			if (sign[i]) {
				sign[i] = false;
				sum += vec[i][cnt];
				dfs(cnt + 1);
				sum -= vec[i][cnt];
				sign[i] = true;
			}
		}
	}
}

int main() {
	
	while (cin >> n >> m) {
		int i, j;
		ans = sum = 0;
		
		for (i = 0; i < n; i++) {
			sign[i] = true;
			for (j = 0; j < m; j++) {
				scanf("%lld", &vec[i][j]);
			}
		}
		dfs(0);
		cout << ans << endl;
	}
	return 0;
}


