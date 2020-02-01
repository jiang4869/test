#include<bits/stdc++.h>
#define max(a,b)   (a>b?a:b)
#define min(a,b)   (a<b?a:b)
#define swap(a,b)  (a=a+b,b=a-b,a=a-b)
#define memset(a,v)  memset(a,v,sizeof(a))
#define X (sqrt(5)+1)/2.0  //Wythoff
#define Pi acos(-1)
#define e  2.718281828459045
#define eps 1.0e-8
using namespace std;
typedef long long int LL;
typedef pair<int, int>pa;
const int MAXL(1e5);
const int INF(0x3f3f3f3f);
const int mod(1e9 + 7);
int dir[4][2] = { {-1,0},{1,0},{0,1},{0,-1} };
int tree[20][MAXL + 50];
int toLeft[20][MAXL + 50];
int sorted[MAXL + 50];
void Build_tree(int level, int left, int right)
{
	if (left == right)
		return;
	int mid = (left + right) >> 1;
	int suppose = mid - left + 1;
	for (int i = left; i <= right; i++)
		if (tree[level][i] < sorted[mid])
			suppose--;
	int subLeft = left, subRight = mid + 1;
	for (int i = left; i <= right; i++)
	{
		if (i == left)
			toLeft[level][i] = 0;
		else
			toLeft[level][i] = toLeft[level][i - 1];
		if (tree[level][i] < sorted[mid] || tree[level][i] == sorted[mid] && suppose>0)
		{
			tree[level + 1][subLeft++] = tree[level][i];
			toLeft[level][i]++;
			if (tree[level][i] == sorted[mid])
				suppose--;
		}
		else
			tree[level + 1][subRight++] = tree[level][i];
	}
	Build_tree(level + 1, left, mid);
	Build_tree(level + 1, mid + 1, right);
}

int Query(int level, int qLeft, int qRight, int left, int right, int k)
{
	int mid = (left + right) >> 1;
	if (qLeft == qRight)
		return tree[level][qLeft];
	int lef;
	int toLef;
	if (qLeft == left)
		lef = 0, toLef = toLeft[level][qRight];
	else
		lef = toLeft[level][qLeft - 1], toLef = toLeft[level][qRight] - lef;
	if (k <= toLef)
	{
		int newLeft = left + lef;
		int newRight = left + lef + toLef - 1;
		return Query(level + 1, newLeft, newRight, left, mid, k);
	}
	else
	{
		int newLeft = mid + qLeft - left - lef + 1;
		int newRight = mid + qRight - left - toLef - lef + 1;
		return Query(level + 1, newLeft, newRight, mid + 1, right, k - toLef);
	}
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &tree[0][i]);
		sorted[i] = tree[0][i];
	}
	sort(sorted + 1, sorted + n + 1);
	Build_tree(0, 1, n);
	while (m--)
	{
		int ql, qr, k;
		scanf("%d%d%d", &ql, &qr, &k);
		int ans = Query(0, ql, qr, 1, n, k);
		cout << ans << endl;
	}
}