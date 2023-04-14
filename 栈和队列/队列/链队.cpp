#include<iostream>
using namespace std;

typedef struct Qnode
{
	int data;//������
	struct Qnode *next;//ָ����	
}Qnode,*QueuePtr;

typedef struct
{
	QueuePtr front;//����ͷָ��
	QueuePtr rear;//����βָ�� 
}LinkQueue;

void InitQueue(LinkQueue &Q)
{
	Q.front=Q.rear=new Qnode;if(!Q.front){cerr<<"�����ڴ����"<<endl;abort();}//�����µĽڵ���Ϊͷ�ڵ� 
	Q.front->next=nullptr;//ͷ�ڵ��ָ����Ϊ �� 
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

void EnQueue(LinkQueue &Q,int e)//��Ӳ���
{
	Qnode *p=new Qnode;if(!p){cerr<<"�����ڴ����"<<endl;abort();}
	
	p->data=e;
	p->next=nullptr;
	Q.rear->next=p;
	Q.rear=p;//������ 
} 

void DeQueue(LinkQueue &Q,int &e)
{
	if(Q.front==Q.rear){clog<<"����Ϊ�գ����ܽ���ɾ��"<<endl;return;}
	
	Qnode *temp=Q.front->next;//����ͷ�ڵ��
	e=temp->data;
	Q.front->next=temp->next;//�����˸���ָ����
	
	if(Q.rear==temp){Q.rear=Q.front;}//���һ��Ԫ�ر�ɾʱ����βָ��ָ��ͷ�ڵ�
	delete temp; 
}

int GetElem(LinkQueue Q)
{
	if(Q.front!=Q.rear)//���зǿյ�������
	return Q.front->next->data;//���ض�ͷԪ�ص�ֵ����ͷָ�벻�� 
}

int main()
{
     LinkQueue Q;
	 
	 InitQueue(Q);//��ʼ������
	 for(int i=0;i<=5;i++)
	 { EnQueue(Q,i);}//��Ӳ��� 
	 
	 for(int i=0;i<=4;i++)
	 {
	 	int e;
		DeQueue(Q,e);//���еĳ��Ӳ��� 
	    cout<<e<<" ";
	 }
	 cout.put('\n');
	 
	 cout<<"�������е�ͷԪ�أ�"<<GetElem(Q)<<endl;
	 
    return 0;
}
