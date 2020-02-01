
#include<cstdio>
#include<iostream>

using namespace std;
int m, n;
int w[31], c[31], p[31];
int f[201];
int max(int x, int y)
{
	if (x < y)return y;
	else return x;
}
int main() {
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d%d", &w[i], &c[i], &p[i]);

	for (int i = 1; i <= n; i++) {
		if (p[i] == 0)     //完全背包
		{
			for (int j = w[i]; j <= m; j++)
				f[j] = max(f[j], f[j - w[i]] + c[i]);
		}
		else
		{
			for (int j = 1; j <= p[i]; j++)     //01背包和多重背包
				for (int k = m; k >= w[i]; k--)
					f[k] = max(f[k], f[k - w[i]] + c[i]);
		}
	}
	printf("%d", f[m]);
	return 0;
}
