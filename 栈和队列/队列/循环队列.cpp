#include<iostream>

#define Maxsize 100
using namespace std;

typedef struct
{
	int *base;//�洢�ռ�Ļ���ַ
	int front;//ͷָ��
	int rear;//βָ�� 
}sqQueue;

void InitQueue(sqQueue &Q)
{//����һ���ն��� 
	Q.base=new int[Maxsize];if(!Q.base){cerr<<"�����ڴ����"<<endl;abort();}
	Q.front=Q.rear=0; //ͷβָ���ʼ��Ϊ0 
}

int QueueLength(sqQueue Q)
{
	return(Q.rear-Q.front+Maxsize)%Maxsize;//βָ���ȥͷָ�� 
}

void EnQueue(sqQueue &Q,int e)//���
{
	if((Q.rear+1)%Maxsize==Q.front){cerr<<"�����Ѿ�����"<<endl;return;}
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%Maxsize;//��βָ��++ 
}
 
void DeQueue(sqQueue &Q,int &e)//ѭ�����еĳ��Ӳ���
{//ɾ����ͷԪ��,��e����

	if(Q.rear==Q.front){cout<<"����Ϊ��"<<endl;return;}
	e=Q.base[Q.front];//�Ӷ�ͷɾ��
	Q.front=(Q.front+1)%Maxsize; 

} 

int Getelem(sqQueue Q)//���ض�ͷԪ�� 
{
	if(Q.front!=Q.rear)//�ǿյ�������
	return Q.base[Q.front]; 
	else {cout<<"����Ϊ��"<<endl;return 0;}
}

int main()
{
	sqQueue Q;
	InitQueue(Q);//���г�ʼ��
	
	for(int i=0;i<6;i++)
	EnQueue(Q,i);
	
	cout<<"���γ��ӣ�";	
	for(int i=0;i<6;i++)
	{
		int e;DeQueue(Q,e);cout<<e<<" ";
	}
	cout.put('\n');
	
	cout<<"���Ӻ�Ķ�ͷԪ��Ϊ "<<Getelem(Q)<<endl;
	cout<<"��ʱ���еĳ����ǣ�"<<QueueLength(Q)<<endl;
		
	return 0;
}
