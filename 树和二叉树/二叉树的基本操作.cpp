#include<iostream>
#include<stack>
#include<vector>
#include<queue>

using namespace std;

typedef char TElemType;
typedef struct BiTNode
{
	TElemType date;
	struct BiTNode *Lchild,*rchild;//���Һ���ָ�� 
}BiTNode,*BiTree;

void CreateBiTree(BiTree &T)//����������������� 
{
	char ch;
	cout<<"��������ڵ��Ȩֵ"<<endl;
	cin>>ch;
	
	if(ch=='#')//# �ǽ�����
	T=nullptr;
	else
	{
		T=new(nothrow) BiTNode;if(!T){cerr<<"�����ڴ����"<<endl;abort();}
		T->Lchild=T->rchild=nullptr;//���� ��ָ
		T->date=ch;//�� 
		
		CreateBiTree(T->Lchild);//�� 
		cout<<"����������"<<endl;
		CreateBiTree(T->rchild);//�� 
	} 
}

void InOrderTraverse(BiTree T) //�ݹ�������� 
{
	if(T)
	{
		InOrderTraverse(T->Lchild);
		cout<<T->date<<"  ";
		InOrderTraverse(T->rchild);
	}
}

void InOrderTraverse_stack(BiTree T) //�ǵݹ��㷨
{
	stack<BiTNode> S;
	BiTNode *p=T,*q=new(nothrow) BiTNode;if(!q){cerr<<"�����ڴ����"<<endl;abort();}
	
	while(p||!S.empty())
	{
		if(p)
		{
			S.push(*p);
			p=p->Lchild;//���������� 
		}
		else
		{
			*q=S.top();//��ȡջ����Ԫ�� ��q������������� 
			 S.pop();
			 cout<<q->date<<"  ";
			 p=q->rchild;
		} 
	}
	
} 

void Copy(BiTree T,BiTree &newT)
{
	if(T==nullptr)
	{
		newT=nullptr;
		return;
	}
	else
	{
		newT=new(nothrow) BiTNode;if(!newT){cerr<<"�ڴ����ʧ�ܣ�"<<endl;abort();}
		newT->Lchild=newT->rchild=nullptr;
		newT->date=T->date;
		
		Copy(T->Lchild,newT->Lchild);//�ݹ鸴�������� 
		Copy(T->rchild,newT->rchild);//�ݹ鸴�������� 
	}
	
}

int Depth(BiTree T)//������������
{
	if(T==nullptr)return 0;//�ҵ������һ���ڵ�ĺ�һ��λ���ǿ�
	else
	{
		int m=Depth(T->Lchild);//�ݹ���������������
		int n=Depth(T->rchild);//�ݹ���������������
		return m>n?m+1:n+1;//�����������Ϊm��n�ϴ��߼�1  
	} 
}
 
int NodeCount(BiTree T)
{
	if(T==nullptr)
	return 0;
	else
	return NodeCount(T->Lchild)+NodeCount(T->rchild)+1;//+1��+ÿ���������ĸ��ڵ� 
}

int LeafCount(BiTree T)
{
	if(T==nullptr)
	return 0;
	else if(T->Lchild==nullptr&&T->rchild==nullptr)
	return 1;
	else
	return LeafCount(T->Lchild)+LeafCount(T->rchild);
}

void levelOrder(BiTree T)
{
	queue<BiTNode> Q;
	BiTNode *p=new BiTNode ;//��������ڴ� 
	Q.push(*T);
	
	while(!Q.empty())
	{
		*p=Q.front();
		 Q.pop();
		 cout<<p->date<<"  ";
		if(p->Lchild)Q.push(*p->Lchild);
		if(p->rchild)Q.push(*p->rchild);
	}	
}

int main() 
{
	BiTree T,newT;
	
	CreateBiTree(T); 
	InOrderTraverse(T);
	cout.put('\n');
	
	Copy(T,newT);
	InOrderTraverse_stack(newT);//�ǵݹ������������ 
	cout.put('\n'); 
	
	levelOrder(T);//��α��� 
	cout<<endl<<"�����������Ϊ: "<<Depth(T)<<endl;
	cout<<"������һ���м����ڵ�: "<<NodeCount(T)<<endl;
	cout<<"������һ���м���Ҷ�ӽڵ㣺"<<LeafCount(T)<<endl;     
} 
