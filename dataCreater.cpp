#include<bits/stdc++.h>
using namespace std;

int n, asdfadfazzzxx;

int main()
{
	
	freopen("data.in", "w", stdout);
	srand(time(0));
	n = 100;
	printf("%d\n", n);
	for (int i = 1; i <= n; i++)
	{
		asdfadfazzzxx = rand() << 15;
		asdfadfazzzxx += rand();
		asdfadfazzzxx %= 1000000000;
		printf("%d ", asdfadfazzzxx);
	}
}
