#include<iostream>
using namespace std;

typedef struct Pnode//两个多项式[有序表]相加 
{
	float coef;//系数	
	int expn;//指数
	struct Pnode *next;	
}Pnode,*Polynomial;

void create(Polynomial &L,int n)
{
	Pnode *s=nullptr,*pre=nullptr,*q=nullptr;//pre指向第一个大于输入项指数的结点的前驱 
	L=new(nothrow) Pnode;
	L->next=nullptr;//建立带头节点的单链表
    
	for(int i=1;i<=n;i++)
	 {
		s=new(nothrow) Pnode;
		
		cout<<"输入系数和指数:";
		cin>>s->coef>>s->expn;
		
		pre=L;//用于保存q的前驱初值为头节点
		q=L->next;//q的初值为首元节点[每一次循环都是这样]
		
		while(q&&q->expn<s->expn)//一个个比较找到第一个大于输入项指数的项(值非递减)
		{pre=q; q=q->next;}//循环结束的时候pre是比第一个大的前驱节点，q则是第一个大于的节点 
		
		s->next =q;
		pre->next= s;//将输入项s插入到q和前驱pre之间 
	 }
}

void display(Polynomial L)
{
	Pnode *p=L->next;//指向首元节点
	while(1)
	{
		cout<<"p->coef:"<<p->coef<<" p->expn:"<<p->expn<<" ";
		if(p->next)
		p=p->next;
		else break;
	} 
	cout.put('\n');
}

void clear(Polynomial &L)//清空操作 
{
	Pnode *p=L->next,*q=nullptr;
	while(p)
	{
		q=p->next;
		delete p;
		p=q;
	}
}

void destory(Polynomial &L)//销毁操作
{
	Pnode *p=nullptr;
	while(L)
	{
		p=L;
		L=L->next; 
		delete p;
	}
	L=nullptr;
}
 
void merge(Polynomial &L1,Polynomial &L2)//多项式的相加类似于有序表的合并
{
	Pnode *p1=L1->next,*p2=L2->next,*p3=L1,*temp=nullptr;//p1,p2指向首元节点p3已L1的头节点作为开始 
	double sum=0;
	
	while(p1&&p2)//p1和p2非空
	{
		if(p1->expn==p2->expn)//第一种情况(指数相同则相加)
		{
		sum=p1->coef+p2->coef;//系数相加 
		
			if(sum)//和不是0 
			{
				p1->coef=sum;//赋值 
				p3->next=p1;//p1链接到p3{已p1的头节点作为起始}中去 
				p3=p1;//p3移动 
				p1=p1->next;
				temp=p2; p2=p2->next; delete temp;//删除p2当前节点 
			}
			else//一旦系数相加为0 
			{
				temp=p1;p1=p1->next;delete temp;//p1节点删除加移动 
				temp=p2;p2=p2->next;delete temp;//p2节点删除加移动 
			}
			
		} 
		else if(p1->expn<p2->expn)//p1的指数小于p2的指数 
		{
			p3->next=p1;//指数小的链接 
			p3=p1;p1=p1->next;
		}
		else//p1的指数大于p2的指数 
		{
			p3->next=p2;//指数小的链接 
			p3=p2;p2=p2->next;
		}
	} 
	
	p3->next=p1?p1:p2;//判断还有哪个链表是非空状态全部进行链接{两个表都是有序表} 
	delete L2;//删除L2的头节点(其他已经被连接或者被删除) 
} 

int main()
{
	Polynomial L1=nullptr,L2=nullptr;
	
	cout<<"p1的创建\n"; 
	create(L1,2);
	cout<<"p2的创建\n"; 
	create(L2,5);
	
	merge(L1,L2);
	display(L1);
	destory(L1);
	return 0;
}
