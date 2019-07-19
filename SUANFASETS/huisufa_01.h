#include<stdio.h>
#define MAXLENGTH 10
//���屳������
int c;
//������Ʒ����
int wupinn;
//��Ʒ����
int weight[MAXLENGTH];
//��Ʒ��ֵ
int value[MAXLENGTH];
//��ǰ����
int currentWeight = 0;
//��ǰ��ֵ
int currentValue = 0;
//���Ž�
int bestAnswer[MAXLENGTH];
//���ż�ֵ
int bestPrice = 0;
//�������յ�����ֵ
int bp = 0;
//���յ�����ֵ
int bA[MAXLENGTH];
int times = 0;
//�������·������
int number = 0;
//���������ԭ������
void Print();
//���ݷ�ԭ������
void Backtracking(int i);


//�����������
void Print(){
	printf("·��%d:\t", ++number);
	int i;
	for (i = 1; i < wupinn; i++)
	{
		printf("%d,", bestAnswer[i]);
	}
	printf("%d\t��ֵΪ��%d\n", bestAnswer[i], bestPrice);
}

//������ݺ���
void Backtracking(int i){
	//�ݹ�һ�νڵ�������1
	times++;
	if (i>wupinn)
	{
		//Print();
		if (bestPrice > bp){
			bp = bestPrice;
			for (int j = 1; j <= wupinn; j++)
			{
				bA[j] = bestAnswer[j];
			}
		}
		return;
	}
	//��װ���i����Ʒ��û�дﵽ�������������ʱ
	if (currentWeight+weight[i]<=c)
	{
		//װ���i����Ʒ
		currentWeight += weight[i];
		//currentValue += value[i];
		//��֧��Ϊ0��1
		bestAnswer[i] = 1;
		bestPrice += value[i];
		//����������
		Backtracking(i + 1);
		//Ϊ��������ָ�����
		currentWeight -= weight[i];
		bestPrice -= value[i];
	}
	//��ǰ�ڵ����¿�ʼ������������
	bestAnswer[i] = 0;
	Backtracking(i + 1);
}