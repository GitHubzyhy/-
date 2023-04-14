#include<iostream>
using namespace std;

typedef struct Stacknode//�洢�ṹ 
{
	int data;
	struct Stacknode *next;
}Stacknode ,*LinkStack;

void initStack(LinkStack &s)
{	s=nullptr;}//û�и���ͷ�ڵ� 

void Push(LinkStack &s,int e)//��ջ
{
	Stacknode *p=new Stacknode;if(!p){cerr<<"�����ڴ�ʧ�ܣ�"<<endl;abort();}
	
	p->data=e;
	p->next=s;
	s=p;//�޸�ջ��ָ��Ϊp; 
} 

void Pop(LinkStack &s,int &e)//��ջ
{
	if(s==nullptr){cerr<<"Ϊ��ջ,��ջ����ʧ��\n";return;}
	Stacknode *temp=nullptr;
	
	e=s->data;
	temp=s;//Ϊ����sָ����׼�� 
	s=s->next;//�޸�ջ��ָ��
	delete temp;
} 

int GetTop(LinkStack s)
{
	if(s!=nullptr)//��ջ��Ϊ��ʱ
	return s->data; //����ջ��Ԫ�أ�ջ��ָ�벻�� 
}

void destroy(LinkStack &s)
{
	Stacknode *p=nullptr;
	while(s)
	{
		p=s;
		s=s->next;
		delete p;
	}
	s=nullptr;
}

int main()
{

	LinkStack s;
	initStack(s); int e;
	
	for(int i=1;i<=5;i++)
	Push(s,i);
	
	for(int i=1;i<=4;i++)
	{
		Pop(s,e);cout<<e<<" ";
	}	
	cout<<"ջ��Ԫ��Ϊ��"<<GetTop(s)<<endl;
	
	return 0;
}
