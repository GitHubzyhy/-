#include<iostream>

using namespace std;

typedef int ElemType; 

typedef struct BSTNode//Binary Search Tree
{
	ElemType data;
	struct BSTNode *lchild,*rchild;//���Һ��� 
}BSTNode,*BSTree;

void InsertBST(BSTree &T,ElemType e)
{//�����������������ڹؼ���=e��ʱ�򣬲Ų��� 
	if(!T)//Ϊ�� 
	{
	   T=new(nothrow) BSTNode;//�²���Ľ��һ����һ��Ҷ�ӽ��
	   T->data=e;
	   T->lchild=T->rchild=nullptr;
	}
	else if(e<T->data)
	InsertBST(T->lchild,e);//go to lchild
	else if(e>T->data)
	InsertBST(T->rchild,e);//go to rchild 
}

void CreateBST(BSTree &T)//����
{
	T=nullptr;
	int e;//����
	cout<<"��������ؼ�������\n"; 
	while(cin>>e)//������������ֹͣ
	{
		if(e==-1)
		break;
		InsertBST(T,e);
	} 
} 
BSTree SearchBST(BSTree T,ElemType key)//�ڶ����������еĲ���
{//�Ӹ�ָ��T��ָ������������ �ݹ� �Ĳ���ĳ�ؼ���=key������Ԫ��
//����ҵ��ˣ�����ָ�������Ԫ�ؽ���ָ�룬���򷵻ؿ�ָ�� 
	if((!T)||key==T->data) return T;
	else if(key<T->data) return SearchBST(T->lchild,key);// ���������в��� 
	else return SearchBST(T->rchild,key);//���������в��� 
}
void DeleteBST(BSTree &T,ElemType key)//�ҵ����ڵĹؼ��ֽ��Ǹ����ɾ��
{
	BSTNode *p=T,*father=nullptr,*Inorder_grandpa=nullptr,*Inorder_father=nullptr;//����ָ��ʹ�ɾ����˫�׽��
	/*-----------------�����whileѭ���Ӹ���ʼ���ҹؼ���=key�Ľ��*----------------*/
	while(p)
	{
		if(p->data==key) break;//�ҵ���
		father=p;
		if(p->data<key) p=p->rchild;
		else p=p->lchild; 
	}
	if(!p) return;//û���ҵ�
	
	/*------�����������ʵ��p��ָ�����ڲ��Ĵ���1.*p���Ҷ���Ϊ�գ�2.��������/��������3.ΪҶ�ӽ��-----*/ 
	 Inorder_grandpa=p;
	 if((p->lchild)&&(p->rchild))//������������Ϊ�յ������
	 {
	 	Inorder_father=p->lchild;//׼����ʼ�����������ǰ����㣬�����������ұ� 
	 	while(Inorder_father->rchild)
	 	{
		Inorder_grandpa=Inorder_father;
		Inorder_father=Inorder_father->rchild; 	//һ�������ұ��� 
		}
		
		p->data=Inorder_father->data;//��ʼ�滻
		//�ҵ���ǰ�����һ��û������������һ��һ������
		if(Inorder_grandpa!=p) Inorder_grandpa->rchild=Inorder_father->lchild; //�滻������ 
	    else Inorder_grandpa->lchild= Inorder_father->lchild;//�滻������ 
	   //ɾ��ǰ����㣬��Ϊ�Ѿ��滻�ɹ� 
	    delete Inorder_father;
	    Inorder_father=nullptr;
	    return; 
	 } //if
	 else if(!p->rchild)//�������� 
	 p=p->lchild;
	 else if(!p->lchild)//�������� 
	 p=p->rchild;
	 /*------��p��ָ�������ƴ�ӵ�˫�׽��*f����Ӧλ����ȥ----------*/
	//���� ������������ ��  Ҷ�ӽ������   һ����� 
	
	if(!father) T=p;//��ɾ���Ϊ���ڵ�
	//���ʱ���Inorder_grandpa=p; ����Ϊû�н����һ��if������ Inorder_grandpa=p��ȻΪ��ʼֵ 
	else if(Inorder_grandpa==father->lchild)
	father->lchild=p;//ƴ�ӵ�*f����������λ����ȥ 
	else 
	father->rchild=p;//ƴ�ӵ�*f����������λ����ȥ 

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
		 	cout<<"���ص�ָ��ָ���Ԫ���ǣ�"<<result->data<<'\n';
		 else
		 cout<<"û���ҵ���\n";
}

int main()
{
	BSTree T=nullptr,result=nullptr;
	
	CreateBST(T);
	ElemType key;
	cout<<"��������key: ";cin>>key;
	result=SearchBST(T,key);
	print(result);

	cout<<"��������Ҫɾ����key��";cin>>key;
	cout<<"��ɾ֮ǰ��";
	Inordering_Traverse(T); 
	 
	DeleteBST(T,key);
	result=SearchBST(T,key);
	cout<<"\n��ɾ֮��";
	Inordering_Traverse(T);
	print(result);
		
	return 0;
}
/*45 24 53 12 37 93 -1*/
