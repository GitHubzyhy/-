#include<stdio.h>
#include<malloc.h>

typedef struct Lnode
{
	int a;
	struct Lnode *next;//后继 
	struct Lnode *prior;//前驱 
}DuLNode,*DuLinkList;

DuLNode* create(DuLinkList L,int n)
{
	DuLNode* next=NULL,*r=NULL;//双向链表设置了尾指针 
	int i;
	
	L=(DuLinkList)malloc(sizeof(DuLNode));//创建头节点 
	L->next=L->prior=NULL;
	r=L;//尾指针初始化 
	
	for(i=1;i<=n;i++)
	{
		next=(DuLNode *)malloc(sizeof(DuLNode));
		next->next=NULL;
		next->a=i;//给数据域赋值 
		r->next=next;
		next->prior=r;
		r=next;
		if(i==n)//创建循环链
		{r->next=L;L->prior=r; }	
	}
	
	return L;
}

void display(DuLinkList L)
{
	DuLNode *p=L->next;//指向其首元节点 
	while(1)
	{
		printf("a:%d  ",p->a);
		if(p->next!=L)
		p=p->next;
		else break;
	}
	putchar('\n');
}

DuLNode* merge(DuLinkList L1,DuLinkList L2)//合并 
{
	DuLNode *r1=L1->prior,*r2=L2->prior,*p=NULL;//设置两个双向循环链表的尾指针
	
	p=r2->next->next;//指向的前驱
	free(r2->next);//删除头节点
	
	r2->next=r1->next;//B连接A；
	r1->next=p;//A连接B *
	
	return L1;
}

DuLNode* GetElem(DuLinkList L,int i)//取值操作
{
	DuLNode *p=L->next;//指向的首元节点
	int j=1;
	
	while((p!=L)&&(j<i))
	{p=p->next;++j;}
	
	if((p==L)||(j>i)){printf("i值不合法\n");return NULL;}
	
	return p;//返回地址 
} 

DuLNode * ListInsert(DuLinkList L,int i,int e)//双向循环链表的插入
{
	DuLNode *p,*s=NULL;
	if(!(p=GetElem(L,i))){printf("没有找到\n");return NULL;}//找的是后继 
	
	s=(DuLinkList)malloc(sizeof(DuLNode));	
	s->a=e;
	
	//修改前面的 
	s->prior=p->prior;
	p->prior->next=s;
	
	//修改后面的 
	s->next=p;
	p->prior=s;
	
	return L;
} 

DuLNode * ListDelete(DuLinkList &L,int i)
{
	DuLNode *p=NULL;
	if(!(p=GetElem(L,i))){printf("没有找到\n");return NULL;}//找到已经要删除的节点了 

	p->prior->next=p->next;//改变的是前驱的指针域 
	p->next->prior=p->prior;//改变的是后继指针的prior域	
	
	free(p);
	
	return L;
}

int main()
{
	DuLNode *L1=NULL,*L2=NULL; 
	
	L1=create(L1,5);
	L2=create(L2,5);
	
	//合并过后 
    L1=merge(L1,L2);
    printf("合并过后的：\n");
	display(L1);
	
	//插入删除的调试步骤 
	L1=ListInsert(L1,2,0);
	printf("插入之后 \n");
	display(L1);
	
	L1=ListDelete(L1,2); 
	printf("删除之后\n");
	display(L1);
	
	return 0;
}
