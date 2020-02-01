#include<stdio.h>

const int maxn = 1e5 + 5;
long long sum[maxn << 2], add[maxn << 2];

#define lson l, mid, rt << 1
#define rson mid + 1, r, rt << 1 | 1

void pushUp(int rt)
{

	sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
}

void pushDown(int rt, int m)
{
	if (add[rt])
	{
		add[rt << 1] += add[rt];
		add[rt << 1 | 1] += add[rt];
		sum[rt << 1] += (m - (m >> 1)) * add[rt];
		sum[rt << 1 | 1] += (m >> 1) * add[rt];
		add[rt] = 0;




		add[rt] = 0;
	}
}


void build(int l, int r, int rt)
{
	add[rt] = 0;
	if (l == r)
	{
		scanf("%lld", &sum[rt]);
		return;
	}
	int mid = (l + r) >> 1;
	build(lson);
	build(rson);
	pushUp(rt);
}


void update(int a, int b, long long c, int l, int r, int rt)
{
	if (a <= l && b >= r)
	{
		sum[rt] += (r - l + 1) * c;
		add[rt] += c;
		return;
	}
	pushDown(rt, r - l + 1);
	int mid = (l + r) >> 1;
	if (a <= mid) update(a, b, c, lson);
	if (b > mid)update(a, b, c, rson);
	pushUp(rt);
}

long long query(int a, int b, int l, int r, int rt)
{
	if (a <= l && b >= r)
		return sum[rt];
	pushDown(rt, r - l + 1);
	int mid = (l + r) >> 1;
	long long ans = 0;
	if (a <= mid)ans += query(a, b, lson);
	if (b > mid)ans += query(a, b, rson);
	return ans;
}


int main()
{

	int n, m;
	scanf("%d%d", &n, &m);
	build(1, n, 1);
	while (m--)
	{
		char cmd[2];
		int a, b;
		long long c;
		scanf("%s", cmd);
		if (cmd[0] == 'C') {
			scanf("%d%d%lld", &a, &b, &c);
			update(a, b, c, 1, n, 1);
		}
		else
		{
			scanf("%d%d", &a, &b);
			printf("%lld\n", query(a, b, 1, n, 1));
		}
	}
	return 0;
}