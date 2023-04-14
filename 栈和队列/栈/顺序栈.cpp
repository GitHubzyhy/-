#include<iostream>

#define MAXSize 100

using namespace std;

typedef struct 
{
	int *base;//栈底指针 
	int *top;//栈顶指针 
	int stacksize;//顺序栈的容量 
}Sqstack;

void create(Sqstack &s)//顺序栈的创建 
{
	s.base=new int[MAXSize];if(!s.base){cerr<<"分配内存错误\n";abort();}
	s.top=s.base;//空栈base==top
	s.stacksize=MAXSize; 
}

bool Push(Sqstack &s,int e)//入栈 
{
	if(s.top-s.base==MAXSize){cout<<"栈已经满了！\n";return false;}
	*s.top++=e;
	return true;
}

bool Pop(Sqstack &s,int &e)//出栈 
{
	if(s.top==s.base){cout<<"栈为空不能删除！\n";return false;}
	e=*--s.top;
	return true;
}

int GetTop(Sqstack s)//返回栈顶元素
{
	 if(s.top!=s.base)//判断栈空的情况 
     return *(s.top-1);
} 

void clear(Sqstack &s)
{
	if(s.base) s.top=s.base;//让栈顶指针和栈底指针相等 
}

void destroy(Sqstack &s)
{
	if(s.base){delete[] s.base;s.base=nullptr;s.top=nullptr;s.stacksize=0;}
}

int main()
{
	Sqstack s;
	
	create(s); //destroy(s);
	for(int i=0;i<5;i++)
	Push(s,i);//压入栈
	
	int e=0;
	for(int i=0;i<4;i++)
	{
	Pop(s,e);cout<<e<<" ";
	}
	
	cout<<GetTop(s)<<endl;//返回栈顶元素
	clear(s);//清空操作 
   	
    for(int i=10;i<15;i++)
   	Push(s,i);//压入栈
   	
	for(int i=10;i<14;i++)
   	{
   	  Pop(s,e);cout<<e<<" ";
   	}
	cout<<GetTop(s);//返回栈顶元素
	
	return 0;
}
