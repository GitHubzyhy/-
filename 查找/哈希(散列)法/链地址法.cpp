#include<iostream>
#include<cmath>

using namespace std;

typedef int KeyType;

typedef struct Vnode
{
	int data;//������
	struct Vnode *next; 
}Vnode;

typedef struct Headnode//ͷ��� 
{
	int pos;//�±� 
	Vnode *next;
}Headnode,*LinkList;
int n;//���ݵĸ��� 

int H(int key)//ɢ�к��� 
{

	return abs(key)%13;//������Ӷ��� 
}

void CreateLink_Hash(LinkList &HN)
{
	cout<<"������������һ���ж��ٸ�\n";
	cin>>n;
	HN=new Headnode[n];if(!HN){cerr<<"�����ڴ�ʧ�ܣ�\n";abort();} 
	
	for(int i=0;i<n;i++)//ͷ�ڵ��ʼ�� 
	{
		HN[i].pos=i;
		HN[i].next=nullptr;
	}
	
	cout<<"��������ؼ���key: ";
	Vnode *p=nullptr,*r=nullptr;
	for(int i=0;i<n;i++)
	{
		p=new(nothrow) Vnode;if(!p){cerr<<"�����ڴ�ʧ�ܣ�\n";abort();}
		p->next=nullptr;
		cin>>p->data;
		int pos=H(p->data);//�����ɢ�е�ַ 
		
//		p->next=HN[pos].next; 
//			HN[pos].next=p;	
//��������β�巨 

		r=HN[pos].next;
		if(r==nullptr)
		HN[pos].next=p;
		else
		{
			for(;r->next;r=r->next);//�ҵ�β�ͽ� 
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
