#include<iostream>
/*��������������������ĵ�һ������ǰ��lchildָ��ͷ��㣬
�����һ�����ĺ��rchildָ��ͷ��㣬ͷ�ڵ��lchildָ������
rchildָ��������������һ�����*/ 

using namespace std;

typedef char TElemType;
typedef struct BiThrNode
{
	TElemType date;
	struct BiThrNode *lchild,*rchild;//���Һ���ָ��
	int LTag,RTag;//���ұ�־ 
}BiThrNode,*BiThrTree;

BiThrTree pre=nullptr;//ȫ�ֱ��� 

void createBiThrTree(BiThrTree &T) //���������������� 
{
	TElemType ch;
	cout<<"����������\n";
	cin>>ch;

	if(ch=='#')
	T=nullptr;
	else
	{
		T=new(nothrow) BiThrNode;if(!T){cerr<<"�����ڴ����\n";abort();}
		T->lchild=T->rchild=nullptr;
		T->date=ch;
		createBiThrTree(T->lchild);
		createBiThrTree(T->rchild);
	} 
} 

void InThreading(BiThrTree p)// �����������޸Ŀ�ָ�� 
{//pre��ʼ��ָ��ͷ�ڵ� pָ��ǰ�ڵ㣬preָ��֮ǰһ���ڵ�[����������]
	if(p)
	{
		InThreading(p->lchild);//�������ݹ�������
		if(!p->lchild)//�������Ϊ��
		{
			p->LTag=1;//��־��Ϊ1��lchildָ�����ǰ��
			p->lchild=pre;//ָ��ǰ�� 
		} 
		else 
		p->LTag=0;
		if(!pre->rchild)//���ǰһ���ڵ���Һ���Ϊ��
		{
			pre->RTag=1;//��־��Ϊ1��rchildָ����ĺ��
			pre->rchild=p; 
		} 
		else
		pre->RTag=0;
		 
		pre=p;//����preָ��p��ǰ��
		InThreading(p->rchild);//�������ݹ������� 
	}
}

void InOrderThreading(BiThrTree &Thrt,BiThrTree T)
{//����ͷ�ڵ� 
	Thrt=new(nothrow) BiThrNode;if(!Thrt){cerr<<"�����ڴ����"<<endl;abort();}
	
	Thrt->LTag=0;//ͷ�ڵ������ӣ������ǿգ���������Ϊ����
	Thrt->RTag=1;//ͷ�ڵ���Һ���ָ��Ϊ������
	Thrt->rchild=Thrt;//��ʼ����ʱ����ָ��ָ���Լ�
	
	if(!T) Thrt->lchild=Thrt;//����Ϊ������ָ��Ҳָ���Լ�
	else
	{
		Thrt->lchild=T;pre=Thrt;//ͷ�ڵ������ָ�����pre��ֵָ��ͷ�ڵ�
		InThreading(T);//ʵ������������
		pre->rchild=Thrt;//������������preΪ���ҽڵ㣬pre��������ָ��ͷ�ڵ�
		pre->RTag=1;
		Thrt->rchild=pre;//ͷ�ڵ��������ָ��pre 
	} 
	
}

void InOrderTraverse(BiThrTree T)
{
	if(T)
	{
		InOrderTraverse(T->lchild);
		cout<<T->date<<" ";
		InOrderTraverse(T->rchild);
	}
}

void InOrderTravese_Thr(BiThrTree T)
{
	//Tָ��ͷ�ڵ㣬ͷ��������lchildָ������
	BiThrNode *p=T->lchild;//�ҵ� ���ڵ� 
	
	while(p!=T)
	{
		while(!p->LTag)p=p->lchild;//�ҵ�����ĵ�һ���ڵ㣬���������½��
		cout<<p->date<<" ";//���
		while(p->RTag&&p->rchild!=T)//p->Rtag==1��ʾ����ָ��ĺ�� 
		{
			p=p->rchild;cout<<p->date<<" ";
		} 
		p=p->rchild;//ת��p�������� 
	} 
}

int main()
{
	BiThrTree T,Thrt;
	
	createBiThrTree(T);
	InOrderTraverse(T);cout.put('\n');
	InOrderThreading(Thrt,T);
	cout<<"������������������"<<endl;
	InOrderTravese_Thr(Thrt);
	
	return 0;
}
