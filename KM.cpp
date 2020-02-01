#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;
#include <cstring>
#define maxsize 310
#define inf 0x3fffff
#define min(x,y) x>y?y:x;
#define max(x,y) x>y?x:y;

//�洢Ȩֵ
int map[maxsize][maxsize];

//lx�൱��Ů���øжȣ�ly�൱�������øж�
int lx[maxsize], ly[maxsize];

//Ů�������Ƿ���ʵı��
int visx[maxsize], visy[maxsize];

//���Ҳ�����Ϊ���գ���Ҫ���͵����ٺøж�
int slack[maxsize];

//��¼��Ů��ƥ���ϵ
int link[maxsize];

//���������������������һ��
int num;


//Ϊ��x�������ҹ���
int dfs(int x)
{

	//��һ�ָõ���ʹ�
	visx[x] = 1;
	int i;

	for (i = 1; i <= num; i++)
	{

		//ÿһ������ֻ����һ��
		if (visy[i] == 1) continue;

		//����ҵ�����ı�
		if (visy[i] == 0 && map[x][i] - lx[x] - ly[i] == 0)
		{

			//�������ʹ����
			visy[i] = 1;

			//�����������㷨��Ϊǰ���ƥ�����°���
			if (link[i] == -1 || dfs(link[i]))
			{
				link[i] = x;
				return 1;
			}
		}

		//�ؼ����ˣ���һ����N�Ĵη��ĸ��ӶȽ�ΪN���η�
		//���ڲ�������øж���ӵ���Ȩֵ�ĵ㣬Ӧ�����������Ƿ�����ƥ��ɹ���������ֵ
		//�����ͷ��ʼ���㣬��ôҪ��n���㶼���������Ӷ�����
		//������һ������ÿ���ҵ�������ߵ�ͬʱ������Ҫ��С���͵�����ֵ�������и��£���ʡ��ʱ��
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
	//�����øжȳ�ʼΪ0
	memset(ly, 0, sizeof(ly));

	//ƥ���ϵ��ʼ��
	memset(link, -1, sizeof(link));

	//��Ϊ����Ů�������ߵ����ֵ����ʼ��Ϊһ����С����
	for (i = 1; i <= num; i++)
	{
		lx[i] = -inf;
	}
	for (i = 1; i <= num; i++)
	{
		for (j = 1; j <= num; j++)
		{
			//ΪŮ����ʼ���øж�
			lx[i] = max(lx[i], map[i][j]);
		}
	}

	//Ϊ���������ˣ�Ȩֵ���Ǽ۸���Ϊ���۰��շ��ӵ�˳�����Է��������У��൱�����ĵ�Ů��
	for (i = 1; i <= num; i++)
	{
		//ÿ��ƥ�䣬��Ҫ�Ȱ���С����ֵ��ʼ��Ϊһ��������������㲻����С���Ҿ���Ϊ����ÿ�γ�ʼ�������˺þ�
		for (j = 1; j <= num; j++)
			slack[j] = inf;

		//ֱ����ǰ�ҵ�һ�����з����Ż�Ѱ����һ�����ӵĹ���
		//���⣬�����������ֵ���ͣ��ұ����ߣ����Ժ�����ƥ���ҵ��Ļ������������Ϊ���������״ﵽ
		while (1)
		{
			//���ʹ���
			memset(visx, 0, sizeof(visx));
			memset(visy, 0, sizeof(visy));

			//����ҵ����з���������ѭ����������һ������
			if (dfs(i)) break;

			//����
			int m = inf;
			//���ҵ����н���ֵ�е���Сֵ
			for (j = 1; j <= num; j++)
			{
				if (!visy[j])
					m = min(m, slack[j]);
			}

			//�������ģ������ʵ㽵�ͣ��Ҳ���ʵ����ߣ��Ҳ�δ���ʵ���������ֵ��С
			for (j = 1; j <= num; j++)
			{
				if (visx[j]) lx[j] -= m;
				if (visy[j]) ly[j] += m;
				else slack[j] -= m;
			}
		}
	}
	int res = 0;

	//ֻ�ۼ�����ƥ��ߵ�Ȩֵ
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