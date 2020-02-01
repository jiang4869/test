#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#include <cstring>
#define maxsize 310
#define inf 0x3fffff
#define min(x,y) x>y?y:x;
#define max(x,y) x>y?x:y;

//存储权值
int map[maxsize][maxsize];

//lx相当于女生好感度，ly相当于男生好感度
int lx[maxsize], ly[maxsize];

//女、男生是否访问的标记
int visx[maxsize], visy[maxsize];

//以右侧男生为参照，需要降低的最少好感度
int slack[maxsize];

//记录男女生匹配关系
int link[maxsize];

//总数量，村子与村民数量一样
int num;


//为第x个房子找归宿
int dfs(int x)
{

	//这一轮该点访问过
	visx[x] = 1;
	int i;

	for (i = 1; i <= num; i++)
	{

		//每一轮男生只访问一次
		if (visy[i] == 1) continue;

		//如果找到满足的边
		if (visy[i] == 0 && map[x][i] - lx[x] - ly[i] == 0)
		{

			//男生访问过标记
			visy[i] = 1;

			//类似匈牙利算法，为前面的匹配重新安排
			if (link[i] == -1 || dfs(link[i]))
			{
				link[i] = x;
				return 1;
			}
		}

		//关键来了，这一步将N四次方的复杂度将为N三次方
		//对于不能满足好感度相加等于权值的点，应该在最后根据是否重新匹配成功调整期望值
		//如果从头开始计算，那么要把n各点都遍历，复杂度上升
		//利用这一步，在每次找到不满足边的同时计算需要最小降低的期望值，并进行更新，节省了时间
		else
		{
			slack[i] = min(slack[i], fabs(map[x][i] - lx[x] - ly[i]));
		}
	}
	return 0;
}


int km()
{
	int i, j;
	//男生好感度初始为0
	memset(ly, 0, sizeof(ly));

	//匹配关系初始化
	memset(link, -1, sizeof(link));

	//因为是找女生相连边的最大值，初始化为一个极小的数
	for (i = 1; i <= num; i++)
	{
		lx[i] = -inf;
	}
	for (i = 1; i <= num; i++)
	{
		for (j = 1; j <= num; j++)
		{
			//为女生初始化好感度
			lx[i] = max(lx[i], map[i][j]);
		}
	}

	//为房子找主人，权值就是价格，因为出价按照房子的顺序，所以房子在左列，相当于上文的女生
	for (i = 1; i <= num; i++)
	{
		//每次匹配，都要先把最小降低值初始化为一个极大的数，方便不断缩小，我就因为忘了每次初始化，改了好久
		for (j = 1; j <= num; j++)
			slack[j] = inf;

		//直到当前找到一个可行方案才会寻找下一个房子的归宿
		//另外，由于左边期望值降低，右边升高，所以后续找匹配找到的机会会上升，因为条件更容易达到
		while (1)
		{
			//访问归零
			memset(visx, 0, sizeof(visx));
			memset(visy, 0, sizeof(visy));

			//如果找到可行方案，跳出循环，继续下一个房子
			if (dfs(i)) break;

			//否则
			int m = inf;
			//先找到所有降低值中的最小值
			for (j = 1; j <= num; j++)
			{
				if (!visy[j])
					m = min(m, slack[j]);
			}

			//按照上文，左侧访问点降低，右侧访问点升高，右侧未访问点期望降低值减小
			for (j = 1; j <= num; j++)
			{
				if (visx[j]) lx[j] -= m;
				if (visy[j]) ly[j] += m;
				else slack[j] -= m;
			}
		}
	}
	int res = 0;

	//只累加所有匹配边的权值
	for (i = 1; i <= num; i++)
	{
		if (link[i] != -1)
			res += map[link[i]][i];
	}
	return res;
}
int main()
{
	while (cin >> num)
	{
		memset(map, 0, sizeof(map));
		int i, j;
		for (i = 1; i <= num; i++)
		{
			for (j = 1; j <= num; j++)
			{
				scanf("%d", &map[i][j]);
			}
		}
		printf("%d\n", km());
	}
	return 0;
}