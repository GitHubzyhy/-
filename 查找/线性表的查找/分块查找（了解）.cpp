#include<stdio.h>

//������
typedef struct
{
	int key;	//���ؼ���
	int start;	//�鿪ʼ�±�
	int end;	//������±�
}Node;
typedef struct
{
	Node idx[10];//����
	int len;	//��
}IdxTable;


//�ֿ����
IdxTable table;	//������
int BlockingSearch(int key,int a[])
{
	//�۰����
	int  low, high, mid;
	low = 1;
	high = table.len;
	while (low <= high)
	{
		mid = (low + high) / 2;			//�ҵ��м�λ��
		if (key<=table.idx[mid].key)
		{
			//˳�����
			if (key <= table.idx[mid - 1].key)
			{
				high = mid - 1;//�������ֲ��� 
			}
			else
			{//iΪ�����±� start��end�ǿ�ʼ�ͽ������±� 
						for (int i = table.idx[mid].start; i <= table.idx[mid].end; i++)
						{
							if (key == a[i])
							{
								return (i + 1);	//��1��ʼ����
							}
						}
						return 0;//����û���ҵ� 
			}
			
		}
		else
		{
			low = mid + 1;				//���С�ڲ��ҵļ�¼�����¶�λmidָ��
		}
	}//while 
	
	return 0;
}
/*������������60 ���Ϊ13*/


int main()
{
	int i;
	int a[] = {22,12,13,8,9,20,33,42,44,38,24,48,60,58,74,49,86,53 };
	//������
	table.idx[1].key = 22; table.idx[1].start = 0; table.idx[1].end = 5;
	table.idx[2].key = 48; table.idx[2].start = 6; table.idx[2].end = 11;
	table.idx[3].key = 86; table.idx[3].start = 12; table.idx[3].end = 17;
	table.len = 3;
	
	//���ҽ��
	int key;
	printf("������Ҫ���ҵļ�¼��");
	scanf("%d", &key);
	i = BlockingSearch(key, a);
	printf("���Ҽ�¼�ڱ��е�λ���ǣ���1��ʼ��0Ϊδ�ҵ�����%d\n", i);
}
