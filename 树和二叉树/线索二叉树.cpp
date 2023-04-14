#include<iostream>
/*线索二叉树：中序遍历的第一个结点的前驱lchild指向头结点，
和最后一个结点的后继rchild指向头结点，头节点的lchild指向根结点
rchild指向中序遍历的最后一个结点*/ 

using namespace std;

typedef char TElemType;
typedef struct BiThrNode
{
	TElemType date;
	struct BiThrNode *lchild,*rchild;//左右孩子指针
	int LTag,RTag;//左右标志 
}BiThrNode,*BiThrTree;

BiThrTree pre=nullptr;//全局变量 

void createBiThrTree(BiThrTree &T) //先序遍历创造二叉树 
{
	TElemType ch;
	cout<<"输入数据域\n";
	cin>>ch;

	if(ch=='#')
	T=nullptr;
	else
	{
		T=new(nothrow) BiThrNode;if(!T){cerr<<"分配内存错误！\n";abort();}
		T->lchild=T->rchild=nullptr;
		T->date=ch;
		createBiThrTree(T->lchild);
		createBiThrTree(T->rchild);
	} 
} 

void InThreading(BiThrTree p)// 遍历过程中修改空指针 
{//pre初始化指向头节点 p指向当前节点，pre指向之前一个节点[中序线索化]
	if(p)
	{
		InThreading(p->lchild);//左子树递归线索化
		if(!p->lchild)//如果左孩子为空
		{
			p->LTag=1;//标志域为1：lchild指向结点的前驱
			p->lchild=pre;//指向前驱 
		} 
		else 
		p->LTag=0;
		if(!pre->rchild)//如果前一个节点的右孩子为空
		{
			pre->RTag=1;//标志域为1：rchild指向结点的后继
			pre->rchild=p; 
		} 
		else
		pre->RTag=0;
		 
		pre=p;//保持pre指向p的前驱
		InThreading(p->rchild);//右子树递归线索化 
	}
}

void InOrderThreading(BiThrTree &Thrt,BiThrTree T)
{//建立头节点 
	Thrt=new(nothrow) BiThrNode;if(!Thrt){cerr<<"分配内存错误！"<<endl;abort();}
	
	Thrt->LTag=0;//头节点有左孩子，若树非空，则其左孩子为树根
	Thrt->RTag=1;//头节点的右孩子指针为右线索
	Thrt->rchild=Thrt;//初始化的时候右指针指向自己
	
	if(!T) Thrt->lchild=Thrt;//若树为空则左指针也指向自己
	else
	{
		Thrt->lchild=T;pre=Thrt;//头节点的左孩子指向根，pre初值指向头节点
		InThreading(T);//实现中序线索化
		pre->rchild=Thrt;//中序线索化后，pre为最右节点，pre的右线索指向头节点
		pre->RTag=1;
		Thrt->rchild=pre;//头节点的右线索指向pre 
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
	//T指向头节点，头结点的左链lchild指向根结点
	BiThrNode *p=T->lchild;//找到 根节点 
	
	while(p!=T)
	{
		while(!p->LTag)p=p->lchild;//找到中序的第一个节点，到达最左下结点
		cout<<p->date<<" ";//输出
		while(p->RTag&&p->rchild!=T)//p->Rtag==1表示右链指向的后继 
		{
			p=p->rchild;cout<<p->date<<" ";
		} 
		p=p->rchild;//转向p的右子树 
	} 
}

int main()
{
	BiThrTree T,Thrt;
	
	createBiThrTree(T);
	InOrderTraverse(T);cout.put('\n');
	InOrderThreading(Thrt,T);
	cout<<"遍历中序线索二叉树"<<endl;
	InOrderTravese_Thr(Thrt);
	
	return 0;
}
