#include<iostream>

using namespace std;

typedef int ElemType; 

typedef struct BSTNode//Binary Search Tree
{
	ElemType data;
	struct BSTNode *lchild,*rchild;//左右孩子 
}BSTNode,*BSTree;

void InsertBST(BSTree &T,ElemType e)
{//当二叉排序树不存在关键字=e的时候，才插入 
	if(!T)//为空 
	{
	   T=new(nothrow) BSTNode;//新插入的结点一定是一个叶子结点
	   T->data=e;
	   T->lchild=T->rchild=nullptr;
	}
	else if(e<T->data)
	InsertBST(T->lchild,e);//go to lchild
	else if(e>T->data)
	InsertBST(T->rchild,e);//go to rchild 
}

void CreateBST(BSTree &T)//创建
{
	T=nullptr;
	int e;//数据
	cout<<"请你输入关键字序列\n"; 
	while(cin>>e)//输入流结束才停止
	{
		if(e==-1)
		break;
		InsertBST(T,e);
	} 
} 
BSTree SearchBST(BSTree T,ElemType key)//在二叉排序树中的查找
{//从根指针T所指二叉排序树中 递归 的查找某关键字=key的数据元素
//如果找到了，返回指向该数据元素结点的指针，否则返回空指针 
	if((!T)||key==T->data) return T;
	else if(key<T->data) return SearchBST(T->lchild,key);// 在左子树中查找 
	else return SearchBST(T->rchild,key);//在右子树中查找 
}
void DeleteBST(BSTree &T,ElemType key)//找到所在的关键字将那个结点删除
{
	BSTNode *p=T,*father=nullptr,*Inorder_grandpa=nullptr,*Inorder_father=nullptr;//工作指针和待删结点的双亲结点
	/*-----------------下面的while循环从根开始查找关键字=key的结点*----------------*/
	while(p)
	{
		if(p->data==key) break;//找到了
		father=p;
		if(p->data<key) p=p->rchild;
		else p=p->lchild; 
	}
	if(!p) return;//没有找到
	
	/*------考虑三种情况实现p所指子树内部的处理，1.*p左右都不为空，2.无左子树/右子树，3.为叶子结点-----*/ 
	 Inorder_grandpa=p;
	 if((p->lchild)&&(p->rchild))//左右子树都不为空的情况！
	 {
	 	Inorder_father=p->lchild;//准备开始找中序遍历的前驱结点，左子树的最右边 
	 	while(Inorder_father->rchild)
	 	{
		Inorder_grandpa=Inorder_father;
		Inorder_father=Inorder_father->rchild; 	//一致往最右边找 
		}
		
		p->data=Inorder_father->data;//开始替换
		//找到的前驱结点一定没有右子树！！一定一定！！
		if(Inorder_grandpa!=p) Inorder_grandpa->rchild=Inorder_father->lchild; //替换右子树 
	    else Inorder_grandpa->lchild= Inorder_father->lchild;//替换左子树 
	   //删除前驱结点，因为已经替换成功 
	    delete Inorder_father;
	    Inorder_father=nullptr;
	    return; 
	 } //if
	 else if(!p->rchild)//无右子树 
	 p=p->lchild;
	 else if(!p->lchild)//无左子树 
	 p=p->rchild;
	 /*------将p所指向的子树拼接到双亲结点*f的相应位置上去----------*/
	//这里 有无左右子树 和  叶子结点的情况   一起算的 
	
	if(!father) T=p;//被删结点为根节点
	//这个时候的Inorder_grandpa=p; ，因为没有进入第一个if条件， Inorder_grandpa=p仍然为初始值 
	else if(Inorder_grandpa==father->lchild)
	father->lchild=p;//拼接到*f的左子树的位置上去 
	else 
	father->rchild=p;//拼接到*f的右子树的位置上去 

	delete Inorder_grandpa;
	Inorder_grandpa=nullptr;
} 

void Inordering_Traverse(BSTNode *T)
{
	if(T)
	{
		Inordering_Traverse(T->lchild);
		cout<<T->data<<" ";
		Inordering_Traverse(T->rchild);
	}
} 

void print(BSTree result)
{
		 if(result)
		 	cout<<"返回的指针指向的元素是："<<result->data<<'\n';
		 else
		 cout<<"没有找到！\n";
}

int main()
{
	BSTree T=nullptr,result=nullptr;
	
	CreateBST(T);
	ElemType key;
	cout<<"请你输入key: ";cin>>key;
	result=SearchBST(T,key);
	print(result);

	cout<<"请你输入要删除的key：";cin>>key;
	cout<<"被删之前：";
	Inordering_Traverse(T); 
	 
	DeleteBST(T,key);
	result=SearchBST(T,key);
	cout<<"\n被删之后：";
	Inordering_Traverse(T);
	print(result);
		
	return 0;
}
/*45 24 53 12 37 93 -1*/
