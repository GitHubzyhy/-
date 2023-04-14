#include<iostream>

#define MAXSize 100

using namespace std;

typedef struct 
{
	int *base;//ջ��ָ�� 
	int *top;//ջ��ָ�� 
	int stacksize;//˳��ջ������ 
}Sqstack;

void create(Sqstack &s)//˳��ջ�Ĵ��� 
{
	s.base=new int[MAXSize];if(!s.base){cerr<<"�����ڴ����\n";abort();}
	s.top=s.base;//��ջbase==top
	s.stacksize=MAXSize; 
}

bool Push(Sqstack &s,int e)//��ջ 
{
	if(s.top-s.base==MAXSize){cout<<"ջ�Ѿ����ˣ�\n";return false;}
	*s.top++=e;
	return true;
}

bool Pop(Sqstack &s,int &e)//��ջ 
{
	if(s.top==s.base){cout<<"ջΪ�ղ���ɾ����\n";return false;}
	e=*--s.top;
	return true;
}

int GetTop(Sqstack s)//����ջ��Ԫ��
{
	 if(s.top!=s.base)//�ж�ջ�յ���� 
     return *(s.top-1);
} 

void clear(Sqstack &s)
{
	if(s.base) s.top=s.base;//��ջ��ָ���ջ��ָ����� 
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
	Push(s,i);//ѹ��ջ
	
	int e=0;
	for(int i=0;i<4;i++)
	{
	Pop(s,e);cout<<e<<" ";
	}
	
	cout<<GetTop(s)<<endl;//����ջ��Ԫ��
	clear(s);//��ղ��� 
   	
    for(int i=10;i<15;i++)
   	Push(s,i);//ѹ��ջ
   	
	for(int i=10;i<14;i++)
   	{
   	  Pop(s,e);cout<<e<<" ";
   	}
	cout<<GetTop(s);//����ջ��Ԫ��
	
	return 0;
}
