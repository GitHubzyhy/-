#include<stdio.h>
#include<malloc.h>

typedef struct Lnode
{
	int a;//数据域 
	struct Lnode *next;//指针域 
}Lnode,*LinkList;//LinkList相当于Lnode* 

Lnode* create1(LinkList L,int n)//头插法 
{
	Lnode *next=NULL;
	
	L=(LinkList)malloc(sizeof(Lnode));
	L->next=NULL;//先建立一个带头节点的空链表
	
	int i;
	for(i=0;i<n;i++)//循环n次 
	{
		next=(Lnode *)malloc(sizeof(Lnode));
		if(!next){printf("分配内存错误！\n");exit(0);}
		
		printf("请你输入数据域的值\n");
		scanf("%d",&next->a);
		next->next=L->next;L->next=next;//类似于插入 (插入在头节点之后） 
	}
	
	return L; 
}

Lnode* create2(LinkList L,int n)//尾插入法 
{
	int i;
	Lnode *next=NULL,*current=NULL;
	
	L=(Lnode *)malloc(sizeof(Lnode));if(!L){printf("分配内存错误！\n");exit(0);}
	L->next=NULL;//先建立一个带头节点的空链表
	current=L;//尾指针指向头节点
	
	for(i=0;i<n;i++)
	{
		next=(LinkList)malloc(sizeof(Lnode));
		printf("请你输入数据域的值\n");
		scanf("%d",&next->a);
		
		next->next=NULL;
		current->next=next;//连接起来 
		current=next;//尾指针移动 
	}
	
	return L;
}

void display(LinkList L)
{
	Lnode *p=L->next;//指向的首元节点 
	while(p)//p不为空的条件下做循环 
	{
		printf("a的值:%d ",p->a);
		p=p->next;
	}
	putchar('\n');
}

//取值操作 
int GetElem(LinkList L,int i,int e)//从i的位置取值
{
	Lnode *p=L->next;//指向首元节点
	
	int j=1;
	while(p&&(j<i))//p不为空的条件且j<i的条件下做循环直到找到哪个节点 
	{p=p->next;	++j;} 
	
	if(!p||(j>i)){printf("i不合法\n");return false;}
	e=p->a;//已经找到了哪个节点直接赋值 
	
	return e;
} 

//按值查找 
Lnode* LocateElem(LinkList L,int e)//找到后返回的是地址
{
	Lnode *p=NULL;
	p=L->next;//指向首元节点
	
	while(p&&p->a!=e)
	p=p->next;
	
	return p;//成功返回地址，失败返回NULL 
} 
bool  insert(LinkList &L,int i,int e)//在i的位置插入e的值(找前驱) 
{
	Lnode *p=L;//指向头节点 
	int j=0;
	
	while(p&&(j<i-1))//找的是前驱
	{p=p->next;++j;}
	
	if(!p||j>i-1){printf("插入的位置不合理\n");return false;}
	Lnode *s=(Lnode *)malloc(sizeof(Lnode));
	if(!s){printf("内存分配失败！\n");exit(0);}
	
	s->a=e;
	s->next=p->next;
	p->next=s;
	
	return true;
}

bool Delete(LinkList &L,int i)//在第i个位置上删除
{
	int j=0;
	Lnode *p=L,*temp=NULL;
	
	while((p->next)&&(j<i-1))//也是找的前驱，但是前驱不能是最后一个
	{p=p->next;++j;}
	
	if(!(p->next)||(j>i-1)){printf("删除的位置不合理\n");return false;}
	
	temp=p->next;//temp指针保存着要删除指针的位置
	p->next=temp->next;//改变了指针域
	free(temp);
	temp=NULL;
	
	return true; 
} 

void clear(LinkList &L)
{
	Lnode *p=NULL,*q=NULL;
	p=L->next;
	
	while(p)
	{
		q=p->next;
		free(p);//q动p删保留头节点 
		p=q;
	}
} 

void destory(LinkList &L)//销毁操作
{
	Lnode *p=NULL;
	while(L)
	{
		p=L;
		L=L->next;
		 free(p);
	}
	L=NULL;
} 

int main()
{
	LinkList L=NULL,p=NULL;
	
	L=create1(L,4);
	display(L);
	printf("\n");
	clear(L);
	
	int e;
	L=create2(L,4);
	display(L);
	
	e=GetElem(L,1,e); 
	printf("查找第一个位置的值是：%d",e);
	
	p=LocateElem(L,1);
	if(!p){printf("查找失败！\n");}
	else printf("p->a:%d\n ",p->a);
	
	if(!insert(L,5,4)){printf("插入失败！\n");}
		display(L);
	
	if(!Delete(L,5)){printf("删除失败！\n");}
		display(L);
		destory(L);//用完销毁 
	
	return 0;
}
