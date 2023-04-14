#include<iostream>

#define Maxsize 100
using namespace std;

typedef struct
{
	int *base;//存储空间的基地址
	int front;//头指针
	int rear;//尾指针 
}sqQueue;

void InitQueue(sqQueue &Q)
{//构造一个空对列 
	Q.base=new int[Maxsize];if(!Q.base){cerr<<"分配内存错误"<<endl;abort();}
	Q.front=Q.rear=0; //头尾指针初始化为0 
}

int QueueLength(sqQueue Q)
{
	return(Q.rear-Q.front+Maxsize)%Maxsize;//尾指针减去头指针 
}

void EnQueue(sqQueue &Q,int e)//入队
{
	if((Q.rear+1)%Maxsize==Q.front){cerr<<"队列已经满了"<<endl;return;}
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%Maxsize;//队尾指针++ 
}
 
void DeQueue(sqQueue &Q,int &e)//循环对列的出队操作
{//删除对头元素,用e返回

	if(Q.rear==Q.front){cout<<"队列为空"<<endl;return;}
	e=Q.base[Q.front];//从对头删除
	Q.front=(Q.front+1)%Maxsize; 

} 

int Getelem(sqQueue Q)//返回队头元素 
{
	if(Q.front!=Q.rear)//非空的条件下
	return Q.base[Q.front]; 
	else {cout<<"对列为空"<<endl;return 0;}
}

int main()
{
	sqQueue Q;
	InitQueue(Q);//进行初始化
	
	for(int i=0;i<6;i++)
	EnQueue(Q,i);
	
	cout<<"依次出队：";	
	for(int i=0;i<6;i++)
	{
		int e;DeQueue(Q,e);cout<<e<<" ";
	}
	cout.put('\n');
	
	cout<<"出队后的对头元素为 "<<Getelem(Q)<<endl;
	cout<<"此时对列的长度是："<<QueueLength(Q)<<endl;
		
	return 0;
}
