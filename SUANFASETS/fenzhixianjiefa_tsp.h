/*��֧�޽編���TSP����
*/
#include<iostream>
#include<algorithm>
#include<queue>
#define MAXLENGTH 10
using namespace std;
//���и���
int fenzhitspn;
//���о�����۾���
int fenzhitspvalue[MAXLENGTH][MAXLENGTH];
//������ʱ�ʶ��
bool dfs_visited[MAXLENGTH];
//���庯���Ͻ�
int up;
//�����½�
int down;
//����������������
void Modify();
//��֧�޽編���TSP����
int solve();
//̰�ķ������Ͻ�
void get_up();
//�����½�
void get_down();
//̰���㷨
int dfs(int, int, int);
//������ڵ��
struct  Node2
{
	//�ڵ���ʱ��
	bool visited[MAXLENGTH];
	//����˳��
	int cixu[MAXLENGTH];
	//��һ����
	int start;
	//��һ���ڵ���ڽӽڵ�
	int start_p;
	//���һ���ڵ�
	int end;
	//���һ���ڵ���ڽӽڵ�
	int end_p;
	//�߹��ĵ���
	int k;
	//����·���ľ���
	int sumv;
	//Ŀ�꺯��ֵ
	int lb;
	//���������
	//Ŀ�꺯��ֵС���ȳ�����
	bool operator <(const Node2 &p) const{
		return p.lb < lb;
	}
};
//����Ŀ�꺯��ֵ
int get_lb(Node2);
//����һ�����ȶ���
priority_queue<Node2> pq;

//������������
void Modify2(){
	for (int i = 1; i <= fenzhitspn; i++)
	{
		fenzhitspvalue[i][i] = 999;
	}
}

int result[MAXLENGTH];
//����������
int solve(CString &strData){
	//1.�����νӺ�������Ŀ�꺯�����Ͻ硢�½�
	get_up();
	//cout << "̰�ķ�����Ͻ�Ϊ:" << up << endl;
	get_down();
	//cout << "�½�Ϊ:" << down << endl;
	//2.������ڵ��Ŀ�꺯��ֵ�������������ڵ����
	Node2 star;
	star.start = 1;
	star.end = 1;
	star.k = 1;
	for (int i = 1; i <= fenzhitspn; i++)
	{
		star.visited[i] = false;
		star.cixu[i]=1;
	}
	star.visited[1] = true;
	star.cixu[1]=1;
	//������·������
	star.sumv = 0;
	//�½�
	star.lb = down;
	//����Ľ�
	int ret = 999;
	//�����������
	pq.push(star);
	//cout << "start��lb=" << star.lb << endl;
	//3.ѭ��ֱ��ĳ��Ҷ�ӽڵ��Ŀ�꺯��ֵ�ڶ�����ȡ����Сֵ
	while (pq.size())
	{
		//3.1��þ�����Сֵ�Ľڵ�
		Node2 tmp = pq.top();
		pq.pop();
		//3.2�Խڵ��ÿ�����ӽڵ�ִ�����в���
		//����Ѿ�����n-1���ڵ�
		if (tmp.k==fenzhitspn-1)
		{
			//�����һ��û�߹��Ľڵ�
			int p;
			for (int i = 1; i <= fenzhitspn; i++)
			{
				if (!tmp.visited[i]){
					tmp.cixu[tmp.k+1]=i;
					p = i;
					break;
				}
			}
			//����ȫ����·�����Ⱥ�
			int ans = tmp.sumv + fenzhitspvalue[tmp.end][p] + fenzhitspvalue[p][tmp.start];
			char string[10];
			//�����ǰ��·�������е�Ŀ�꺯��ֵ��С������
			if (ans <= tmp.lb){
				ret = min(ans, ret);
				for (int j = 1; j <= fenzhitspn; j++)
				{
					result[j]=tmp.cixu[j];

					sprintf(string,"%d, ",result[j]);
					strData+=string;
				}
				strData+="\r\n";
				break;
			}
			else
			{
				//�����Ͻ�
				up = min(ret, ans);
				ret = min(ret, ans);
				continue;
			}
		}
		
		Node2 next;
		for (int i = 1; i <= fenzhitspn; i++)
		{
			if (!tmp.visited[i])
			{
				//��㲻��
				next.start = tmp.start;
				//����·����
				next.sumv = tmp.sumv + fenzhitspvalue[tmp.end][i];
				//int tmpstart = tmp.end;
				next.end = i;
				next.k = tmp.k + 1;
				for (int j = 1; j <= fenzhitspn; j++)
				{
					next.visited[j] = tmp.visited[j];
					next.cixu[j]=tmp.cixu[j];
				}
				next.visited[i] = true;
				next.cixu[next.k]=i;
				//3.2.1����ÿ�����ӽڵ��Ŀ�꺯��ֵ
				next.lb = get_lb(next);
				//3.2.2�ж��Ƿ���Ҫ�����ý��
				if (next.lb > up){
					continue;//���������
				}
				pq.push(next);
				//cout << tmpstart << "->" << next.end << ":lb=" << next.lb << endl;
			}
		}
	}
	return ret;
}

//���庯���Ͻ纯��
void get_up(){
	dfs_visited[1] = true;
	//��ʵ�����������һЩ�Ľ�
	up = dfs(1, 1, 0);
}

//����̰���㷨,�����Ͻ�
int dfs(int u, int k, int l){
	int minlen = 999;
	int p;
	if (k==fenzhitspn)
	{
		//������һ���ڵ�Ϳ�ʼ�ڵ�ľ���
		//minlen = value[u][1];
		return l + fenzhitspvalue[u][1];
	}
	for (int i = 1; i <= fenzhitspn; i++)
	{
		if (!dfs_visited[i]&&fenzhitspvalue[u][i]<minlen)
		{
			minlen = fenzhitspvalue[u][i];
			p = i;
		}
	}
	//��ǵ�ǰ������С�ڵ�Ϊ���ʹ�
	dfs_visited[p] = true;
	return dfs(p, k + 1, l + minlen);
}

//�����½纯��
void get_down(){
	//ȡÿ����С������Ԫ������ٳ���2��ֵ��Ϊ�½�
	down = 0;
	for (int i = 1; i <= fenzhitspn; i++)
	{
		//����һ����ʱ���飬���ڴ洢ÿһ�е�����
		int temp[MAXLENGTH];
		for (int j = 1; j <= fenzhitspn; j++)
		{
			temp[j] = fenzhitspvalue[i][j];
		}
		//�������������,�����ֱ�Ϊ��ʼλ�ã�����λ��
		sort(temp + 1,temp + fenzhitspn + 1);
		//������С������ֵ
		down = down + temp[1] + temp[2];
	}
	//��down����2
	down /= 2;
}

//����Ŀ�꺯��ֵ
int get_lb(Node2 p){
	int ret = p.sumv * 2;//·���ϵĵ�ľ���Ķ���
	int min1 = 999, min2 = 999;//�����յ��������ı�
	int i,j;
	for (i = 1; i <= fenzhitspn; i++)
	{
		//cout << p.visited[i] << endl;
		if (!p.visited[i] && min1 > fenzhitspvalue[p.start][i])
		{
			min1 = fenzhitspvalue[p.start][i];
		}
		//cout << min1 << endl;
	}
	ret += min1;
	for (i = 1; i <= fenzhitspn; i++)
	{
		if (!p.visited[i] && min2 > fenzhitspvalue[p.end][i])
		{
			min2 = fenzhitspvalue[p.end][i];
		}
		//cout << min2 << endl;
	}
	ret += min2;
	for (i = 1; i <= fenzhitspn; i++)
	{
		if (!p.visited[i])
		{
			min1 = min2 = 999;
			for (j = 1; j <= fenzhitspn; j++)
			{
				if (min1 > fenzhitspvalue[i][j])
					min1 = fenzhitspvalue [i][j];
			}
			for (j = 1; j <= fenzhitspn; j++)
			{
				/*if (min2 > cost[j][i])
				min2 = cost[j][i];*/
				if (min2>fenzhitspvalue[i][j] && fenzhitspvalue[i][j]>min1)
				{
					min2 = fenzhitspvalue[i][j];
				}
			}
			ret += min1 + min2;
		}
	}
	return ret / 2;
}