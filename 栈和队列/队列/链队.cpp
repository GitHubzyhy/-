#include<iostream>
using namespace std;

typedef struct Qnode
{
	int data;//数据域
	struct Qnode *next;//指针域	
}Qnode,*QueuePtr;

typedef struct
{
	QueuePtr front;//队列头指针
	QueuePtr rear;//对列尾指针 
}LinkQueue;

void InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=new Qnode;if(!Q.front){cerr<<"分配内存错误！"<<endl;abort();}//生成新的节点作为头节点 
	Q.front->next=nullptr;//头节点的指针域为 空 
}

void destroy(LinkQueue &Q)
{
	while(Q.front)
	{
		Q.rear=Q.front->next;
		delete Q.front;
		Q.front=Q.rear;
	}
}

void EnQueue(LinkQueue &Q,int e)//入队操作
{
	Qnode *p=new Qnode;if(!p){cerr<<"分配内存错误！"<<endl;abort();}
	
	p->data=e;
	p->next=nullptr;
	Q.rear->next=p;
	Q.rear=p;//入队完毕 
} 

void DeQueue(LinkQueue &Q,int &e)
{
	if(Q.front==Q.rear){clog<<"对列为空！不能进行删除"<<endl;return;}
	
	Qnode *temp=Q.front->next;//是有头节点的
	e=temp->data;
	Q.front->next=temp->next;//经行了更改指针域
	
	if(Q.rear==temp){Q.rear=Q.front;}//最后一个元素被删时，队尾指针指向头节点
	delete temp; 
}

int GetElem(LinkQueue Q)
{
	if(Q.front!=Q.rear)//队列非空的条件下
	return Q.front->next->data;//返回对头元素的值，对头指针不变 
}

int main()
{
     LinkQueue Q;
	 
	 InitQueue(Q);//初始化操作
	 for(int i=0;i<=5;i++)
	 { EnQueue(Q,i);}//入队操作 
	 
	 for(int i=0;i<=4;i++)
	 {
	 	int e;
		DeQueue(Q,e);//进行的出队操作 
	    cout<<e<<" ";
	 }
	 cout.put('\n');
	 
	 cout<<"最后队列中的头元素："<<GetElem(Q)<<endl;
	 
    return 0;
}
