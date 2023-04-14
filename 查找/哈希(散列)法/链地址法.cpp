#include<iostream>
#include<cmath>

using namespace std;

typedef int KeyType;

typedef struct Vnode
{
	int data;//数据域
	struct Vnode *next; 
}Vnode;

typedef struct Headnode//头结点 
{
	int pos;//下标 
	Vnode *next;
}Headnode,*LinkList;
int n;//数据的个数 

int H(int key)//散列函数 
{

	return abs(key)%13;//这个例子而言 
}

void CreateLink_Hash(LinkList &HN)
{
	cout<<"请你输入数据一共有多少个\n";
	cin>>n;
	HN=new Headnode[n];if(!HN){cerr<<"分配内存失败！\n";abort();} 
	
	for(int i=0;i<n;i++)//头节点初始化 
	{
		HN[i].pos=i;
		HN[i].next=nullptr;
	}
	
	cout<<"请你输入关键字key: ";
	Vnode *p=nullptr,*r=nullptr;
	for(int i=0;i<n;i++)
	{
		p=new(nothrow) Vnode;if(!p){cerr<<"分配内存失败！\n";abort();}
		p->next=nullptr;
		cin>>p->data;
		int pos=H(p->data);//计算出散列地址 
		
//		p->next=HN[pos].next; 
//			HN[pos].next=p;	
//这里用了尾插法 

		r=HN[pos].next;
		if(r==nullptr)
		HN[pos].next=p;
		else
		{
			for(;r->next;r=r->next);//找到尾巴结 
				r->next=p;	
		}
			 
	} //for
	
} 	

void print(LinkList L)
{
	for(int i=0;i<n;i++)
	{
		cout<<"pos=[ "<<L[i].pos<<"|-]->";
		if(L[i].next)
		{
			Vnode *p=L[i].next;
			while(p)
			{
				cout<<"[ "<<p->data<<"|-]->";
				p=p->next;
			}
			cout.put('\n');
		}//if 
		else
		cout.put('\n');
	}//for
} 

int main()
{
	LinkList HN;
	CreateLink_Hash(HN);

	print(HN);
	return 0;
}
/*
12
19 14 23 1 68 20 84 27 55 11 10 79*/
