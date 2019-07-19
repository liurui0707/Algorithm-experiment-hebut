#include<iostream>
using namespace std;

#define C 10
int V[6][11];
int x[5];
int KnapSack(int n, int w[], int v[]);
int maxnumber(int x, int y);
void printV();
/*int main()
{
	int w[] = { 2, 2, 6, 5, 4 };
	int v[] = { 6, 3, 5, 4, 6 };
	
	cout << "����������ֵΪ:" << KnapSack(5, w, v) << endl;
	cout << "װ�뱳������Ʒ��:";
	for (int i = 0; i < 5; i++)
	{
		if (x[i]==1)
		{
			cout << "��Ʒ" << i + 1;
		}
		
	}
	printf("\n");
	printV();
	cout << endl;
	return 0;
}*/

int maxnumber(int x, int y){
	if (x>y)
	{
		return x;
	}
	else
	{
		return y;
	}
}

int KnapSack(int n, int w[], int v[]){
	int i, j;

	//1.��ʼ����0��
	for ( i = 0; i <=n; i++)
	{
		V[i][0] = 0;
	}

	//2.��ʼ����0��
	for ( j = 0; j <=C; j++)
	{
		V[0][j] = 0;
	}

	//3.��ʼ����i�У�����i�ε���
	for (i = 1; i <=n; i++)
	{
		for ( j = 1; j <= C; j++)
		{
			if (j<w[i-1])
			{
				//��j����Ʒ������Ӳ���ȥ
				V[i][j] = V[i - 1][j];
			}
			else
			{
				V[i][j] = max(V[i - 1][j], V[i-1][j-w[i-1]]+v[i-1]);
			}
		}
	}

	//4.��װ�����Ʒ
	for ( j = C,i=n; i>0; i--)
	{
		if (V[i][j]>V[i-1][j])
		{
			x[i-1] = 1;
			j = j - w[i-1];
		}
		else
		{
			x[i-1] = 0;
		}
	}

	//5.���ر���������ֵ
	return V[n][C];
}

void printV(){
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < C+1; j++)
		{
			if (j==0)
			{
				printf("%d\t", i);
			}
			else
			{
				printf("%d\t", V[i][j - 1]);
			}
		}
		printf("\n");
	}
}