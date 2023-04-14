#include<iostream>
#include<stack>
#include<vector>
#include<queue>

using namespace std;

typedef char TElemType;
typedef struct BiTNode
{
	TElemType date;
	struct BiTNode *Lchild,*rchild;//左右孩子指针 
}BiTNode,*BiTree;

void CreateBiTree(BiTree &T)//先序遍历创建二叉树 
{
	char ch;
	cout<<"请你输入节点的权值"<<endl;
	cin>>ch;
	
	if(ch=='#')//# 是结束符
	T=nullptr;
	else
	{
		T=new(nothrow) BiTNode;if(!T){cerr<<"分配内存错误！"<<endl;abort();}
		T->Lchild=T->rchild=nullptr;//避免 乱指
		T->date=ch;//根 
		
		CreateBiTree(T->Lchild);//左 
		cout<<"进入右子树"<<endl;
		CreateBiTree(T->rchild);//右 
	} 
}

void InOrderTraverse(BiTree T) //递归中序遍历 
{
	if(T)
	{
		InOrderTraverse(T->Lchild);
		cout<<T->date<<"  ";
		InOrderTraverse(T->rchild);
	}
}

void InOrderTraverse_stack(BiTree T) //非递归算法
{
	stack<BiTNode> S;
	BiTNode *p=T,*q=new(nothrow) BiTNode;if(!q){cerr<<"分配内存错误！"<<endl;abort();}
	
	while(p||!S.empty())
	{
		if(p)
		{
			S.push(*p);
			p=p->Lchild;//遍历左子树 
		}
		else
		{
			*q=S.top();//获取栈顶的元素 给q让其访问右子树 
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
		newT=new(nothrow) BiTNode;if(!newT){cerr<<"内存分配失败！"<<endl;abort();}
		newT->Lchild=newT->rchild=nullptr;
		newT->date=T->date;
		
		Copy(T->Lchild,newT->Lchild);//递归复制左子树 
		Copy(T->rchild,newT->rchild);//递归复制右子树 
	}
	
}

int Depth(BiTree T)//求二叉树的深度
{
	if(T==nullptr)return 0;//找到了最后一个节点的后一个位置是空
	else
	{
		int m=Depth(T->Lchild);//递归计算左子树的深度
		int n=Depth(T->rchild);//递归计算右子树的深度
		return m>n?m+1:n+1;//二叉树的深度为m于n较大者加1  
	} 
}
 
int NodeCount(BiTree T)
{
	if(T==nullptr)
	return 0;
	else
	return NodeCount(T->Lchild)+NodeCount(T->rchild)+1;//+1是+每个二叉树的根节点 
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
	BiTNode *p=new BiTNode ;//必须分配内存 
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
	InOrderTraverse_stack(newT);//非递归中序遍历访问 
	cout.put('\n'); 
	
	levelOrder(T);//层次遍历 
	cout<<endl<<"二叉树的深度为: "<<Depth(T)<<endl;
	cout<<"二叉树一共有几个节点: "<<NodeCount(T)<<endl;
	cout<<"二叉树一共有几个叶子节点："<<LeafCount(T)<<endl;     
} 
