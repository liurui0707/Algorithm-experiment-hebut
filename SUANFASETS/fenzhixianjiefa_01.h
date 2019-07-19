#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
//��Ʒ����
int fenzhi01n;
//��������
int fenzhi01c;
int *fenzhi01x = new int[fenzhi01n];
//������Ʒ�ṹ��
struct Item
{
	//��Ʒ���
	int ItemID;
	//��Ʒ��ֵ
	int value;
	//��Ʒ����
	int weight;
	//����/����
	int ratio;
};

//���������ڵ�
struct Node
{
	Node(){
		value = 0;
		weight = 0;
		level = 0;
		parent = 0;
		bound = 0;
	}
	//�������ýڵ�ļ�ֵ
	int value;
	//�������ýڵ��������
	int weight;
	//�����Ըýڵ�Τ���������ܴﵽ�ļ�ֵ�Ͻ�
	int bound;
	//���
	int level;
	//���ڵ�
	struct Node *parent;
};

//���մ󶥶ѵ���ʽ���
struct cmp
{
	bool operator()(Node *a, Node *b){
		return a->bound < b->bound;
	}
};

//�ȽϺ���
bool Itemcmp(Item item1, Item item2);
//��֧�޽編
int branchAndBound(Item items[], int c);
int searchCount = 0;
int maxSize = 0;
//�޽纯��
float maxBound(Node *node, Item items[], int c);

/*int main(){
	int maxValue;
	cout << "��������Ʒ�ĸ���:";
	cin >> n;
	cout << "�����뱳������:";
	cin >> c;
	int *w = new int[n];
	int *v = new int[n];
	cout << "������" << n << "����Ʒ������:" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> w[i];
	}
	cout << "������" << n << "����Ʒ�ļ�ֵ:" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}

	//������Ʒ�ṹ��
	Item *items = new Item[n];
	//��ʼ���ṹ������
	for (int i = 0; i < n; i++)
	{
		items[i].ItemID = i;
		items[i].value = v[i];
		items[i].weight = w[i];
		items[i].ratio = 1.0*v[i] / w[i];
	}
	//����ֵ������
	sort(items, items + n, Itemcmp);
	cout << "��Ʒ�ļ�ֵ����Ϊ:";
	for (int i = 0; i < n; i++)
	{
		cout << v[i] << "  ";
	}
	cout << endl;
	cout << "��Ʒ�������ֱ�Ϊ:";
	for (int i = 0; i < n; i++)
	{
		cout << w[i] << " ";
	}
	cout << endl;
	cout << "ѡȡ����Ϊ:" << endl;
	maxValue = branchAndBound(items, c);
	cout << "����ֵΪ:" << maxValue;
	getchar();
	getchar();
	getchar();
	delete []w;
	delete []v;
}*/

//�ȽϺ���
bool Itemcmp(Item item1, Item item2){
	return item1.ratio > item2.ratio;
}

//��֧�޽纯��
int branchAndBound(Item items[], int c){
	int i;
	for (i = 0; i < fenzhi01n; i++)
	{
		fenzhi01x[i] = 0;
	}
	//��������ֵ
	int maxValue;
	//���浱ǰ����ֵ�ڵ�
	Node *maxNode = new Node();
	//����ֵ���ȶ���
	priority_queue<Node *, vector<Node *>, cmp> maxQueue;
	Node *firstNode, *curNode;
	
	searchCount = 1;
	firstNode = new Node();
	firstNode->bound = maxBound(firstNode, items, c);
	firstNode->parent = NULL;
	maxQueue.push(firstNode);
	maxValue = 0;
	maxNode = firstNode;
	while (!maxQueue.empty()){
		curNode = maxQueue.top();
		maxQueue.pop();
		//��չ����
		if (curNode->weight + items[curNode->level].weight <= c){
			Node *leftNode = new Node();
			leftNode->value = curNode->value + items[curNode->level].value;
			leftNode->weight = curNode->weight + items[curNode->level].weight;
			leftNode->level = curNode->level + 1;
			leftNode->parent = curNode;
			leftNode->bound = curNode->bound;
			if (leftNode->level<fenzhi01n)
			{
				maxQueue.push(leftNode);
				searchCount++;
			}
			if (maxValue<leftNode->value)
			{
				maxValue = leftNode->value;
				maxNode = leftNode;
			}
		}

		//��չ�Һ��ӽڵ�
		if (maxBound(curNode, items, c)>maxValue){
			Node *rightNode = new Node();
			rightNode->value = curNode->value;
			rightNode->weight = curNode->weight;
			rightNode->level = curNode->level + 1;
			rightNode->parent = curNode;
			rightNode->bound = maxBound(rightNode, items, c);
			if (rightNode->level<fenzhi01n)
			{
				maxQueue.push(rightNode);
				searchCount++;
			}
		}
		if (maxQueue.size()>maxSize)
		{
			maxSize = maxQueue.size();
		}
	}
	curNode = maxNode;
	while (curNode)
	{
		int tempValue = curNode->value;
		curNode = curNode->parent;
		if (curNode&&curNode->value != tempValue){
			fenzhi01x[items[curNode->level].ItemID] = 1;
		}
	}
	/*for (i = 0; i < fenzhi01n; i++)
	{
		cout << x[i] << "  ";
	}
	cout << endl;*/
	return maxValue;
}

//�޽纯��
float maxBound(Node *node, Item items[], int c){
	float maxValue;
	//����ʣ������
	int restCapacity;
	int i;

	maxValue = node->value;
	restCapacity = c - node->weight;
	i = node->level;

	while (i<fenzhi01n&&restCapacity>items[i].weight)
	{
		maxValue += items[i].value;
		restCapacity -= items[i].weight;
		i++;
	}
	if (restCapacity!=0)
	{
		maxValue += restCapacity*items[i].ratio;
	}
	return maxValue;
}