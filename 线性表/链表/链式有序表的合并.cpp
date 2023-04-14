#include<iostream>
using namespace std;//��ʽ�����ĺϲ� 

typedef struct Lnode
{
	int data;	
	struct Lnode *next;	
}Lnode,*LinkList;

void create(LinkList &L,int n)//�����Ľ��� 
{
	L=new(nothrow) Lnode;
	Lnode *next=nullptr;//���õ�βָ�� 
	Lnode *pre=nullptr,*q=nullptr;//���ҵ�ǰ���ͺ�� 
	
	if(!L){cerr<<"�����ڴ����\n";abort();}
	L->next=nullptr;//����ͷ�ڵ�
	
	for(int i=0;i<=n-1;i++)
	{
		next=new(nothrow) Lnode;	if(!next){cerr<<"�����ڴ����\n";abort();}
	    
		cout<<"����data��ֵ�� "; 
		cin>>next->data;
		cout.put('\n');
		
		pre=L;//pre��������q��ǰ������ֵΪͷ�ڵ�
		q=L->next;//q��ʼ��ָ����Դ�ڵ� 
		while(q&&q->data<next->data)
		{
			pre=q;
			q=q->next;
		} 
		
		next->next=q;//�����ڲ��� 
		pre->next=next;
	} 
}

void display(LinkList p)
{
	Lnode *q=p->next;
	while(1)
	{
		cout<<"p->data:"<<q->data<<"  ";
		if(q->next)
		q=q->next;
		else break;
	}
}

void distroy(LinkList &L)
{
	Lnode *p=nullptr;
	while(L)
	{
		p=L;
		L=L->next;
		delete p;
	}
	L=nullptr;
}
void MergeList_L(LinkList &L1,LinkList &L2,LinkList &L3)
{
	Lnode *p1=L1->next,*p2=L2->next;
	L3=L1;//L3ָ��L1��ͷ�ڵ�
	Lnode *p3=L3;
	
	while(p1&&p2)
	{
		if(p1->data<=p2->data)
		{
			p3->next=p1;//�������� 
			p3=p1;
			p1=p1->next;
		}
		else
		{
			p3->next=p2;
			p3=p2;
			p2=p2->next;
		}
	} 
	p3->next=p1?p1:p2;//��Ŀ����Ƚ���һ��û�е��������ĩβ 
	delete L2;//ȫ�����ӵ���һ�����У�ɾ��L2 
}

int main()
{
	LinkList L1=nullptr,L2=nullptr,L3=nullptr;

	cout<<"������һ�������\n";
		create(L1,4);
	
	cout<<"�����ڶ��������\n";
		create(L2,7);
	
	MergeList_L(L1,L2,L3);
	display(L1);
	distroy(L1);
	
	return 0;
}
