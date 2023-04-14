#include<iostream>
using namespace std;

typedef struct Stacknode//存储结构 
{
	int data;
	struct Stacknode *next;
}Stacknode ,*LinkStack;

void initStack(LinkStack &s)
{	s=nullptr;}//没有附加头节点 

void Push(LinkStack &s,int e)//入栈
{
	Stacknode *p=new Stacknode;if(!p){cerr<<"分配内存失败！"<<endl;abort();}
	
	p->data=e;
	p->next=s;
	s=p;//修改栈顶指针为p; 
} 

void Pop(LinkStack &s,int &e)//出栈
{
	if(s==nullptr){cerr<<"为空栈,出栈操作失败\n";return;}
	Stacknode *temp=nullptr;
	
	e=s->data;
	temp=s;//为销毁s指针做准备 
	s=s->next;//修改栈顶指针
	delete temp;
} 

int GetTop(LinkStack s)
{
	if(s!=nullptr)//链栈不为空时
	return s->data; //返回栈顶元素，栈顶指针不变 
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
	cout<<"栈顶元素为："<<GetTop(s)<<endl;
	
	return 0;
}
