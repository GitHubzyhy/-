#include<iostream>
using namespace std;//链式有序表的合并 

typedef struct Lnode
{
	int data;	
	struct Lnode *next;	
}Lnode,*LinkList;

void create(LinkList &L,int n)//有序表的建立 
{
	L=new(nothrow) Lnode;
	Lnode *next=nullptr;//设置的尾指针 
	Lnode *pre=nullptr,*q=nullptr;//查找的前驱和后继 
	
	if(!L){cerr<<"分配内存错误！\n";abort();}
	L->next=nullptr;//建立头节点
	
	for(int i=0;i<=n-1;i++)
	{
		next=new(nothrow) Lnode;	if(!next){cerr<<"分配内存错误！\n";abort();}
	    
		cout<<"输入data的值： "; 
		cin>>next->data;
		cout.put('\n');
		
		pre=L;//pre用来保存q的前驱，初值为头节点
		q=L->next;//q初始化指向受源节点 
		while(q&&q->data<next->data)
		{
			pre=q;
			q=q->next;
		} 
		
		next->next=q;//类似于插入 
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
	L3=L1;//L3指向L1的头节点
	Lnode *p3=L3;
	
	while(p1&&p2)
	{
		if(p1->data<=p2->data)
		{
			p3->next=p1;//重新连接 
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
	p3->next=p1?p1:p2;//三目运算比较哪一个没有到达链表的末尾 
	delete L2;//全部连接到第一个表中，删除L2 
}

int main()
{
	LinkList L1=nullptr,L2=nullptr,L3=nullptr;

	cout<<"创建第一个有序表\n";
		create(L1,4);
	
	cout<<"创建第二个有序表\n";
		create(L2,7);
	
	MergeList_L(L1,L2,L3);
	display(L1);
	distroy(L1);
	
	return 0;
}
