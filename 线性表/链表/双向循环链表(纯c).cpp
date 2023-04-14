#include<stdio.h>
#include<malloc.h>

typedef struct Lnode
{
	int a;
	struct Lnode *next;//��� 
	struct Lnode *prior;//ǰ�� 
}DuLNode,*DuLinkList;

DuLNode* create(DuLinkList L,int n)
{
	DuLNode* next=NULL,*r=NULL;//˫������������βָ�� 
	int i;
	
	L=(DuLinkList)malloc(sizeof(DuLNode));//����ͷ�ڵ� 
	L->next=L->prior=NULL;
	r=L;//βָ���ʼ�� 
	
	for(i=1;i<=n;i++)
	{
		next=(DuLNode *)malloc(sizeof(DuLNode));
		next->next=NULL;
		next->a=i;//��������ֵ 
		r->next=next;
		next->prior=r;
		r=next;
		if(i==n)//����ѭ����
		{r->next=L;L->prior=r; }	
	}
	
	return L;
}

void display(DuLinkList L)
{
	DuLNode *p=L->next;//ָ������Ԫ�ڵ� 
	while(1)
	{
		printf("a:%d  ",p->a);
		if(p->next!=L)
		p=p->next;
		else break;
	}
	putchar('\n');
}

DuLNode* merge(DuLinkList L1,DuLinkList L2)//�ϲ� 
{
	DuLNode *r1=L1->prior,*r2=L2->prior,*p=NULL;//��������˫��ѭ�������βָ��
	
	p=r2->next->next;//ָ���ǰ��
	free(r2->next);//ɾ��ͷ�ڵ�
	
	r2->next=r1->next;//B����A��
	r1->next=p;//A����B *
	
	return L1;
}

DuLNode* GetElem(DuLinkList L,int i)//ȡֵ����
{
	DuLNode *p=L->next;//ָ�����Ԫ�ڵ�
	int j=1;
	
	while((p!=L)&&(j<i))
	{p=p->next;++j;}
	
	if((p==L)||(j>i)){printf("iֵ���Ϸ�\n");return NULL;}
	
	return p;//���ص�ַ 
} 

DuLNode * ListInsert(DuLinkList L,int i,int e)//˫��ѭ������Ĳ���
{
	DuLNode *p,*s=NULL;
	if(!(p=GetElem(L,i))){printf("û���ҵ�\n");return NULL;}//�ҵ��Ǻ�� 
	
	s=(DuLinkList)malloc(sizeof(DuLNode));	
	s->a=e;
	
	//�޸�ǰ��� 
	s->prior=p->prior;
	p->prior->next=s;
	
	//�޸ĺ���� 
	s->next=p;
	p->prior=s;
	
	return L;
} 

DuLNode * ListDelete(DuLinkList &L,int i)
{
	DuLNode *p=NULL;
	if(!(p=GetElem(L,i))){printf("û���ҵ�\n");return NULL;}//�ҵ��Ѿ�Ҫɾ���Ľڵ��� 

	p->prior->next=p->next;//�ı����ǰ����ָ���� 
	p->next->prior=p->prior;//�ı���Ǻ��ָ���prior��	
	
	free(p);
	
	return L;
}

int main()
{
	DuLNode *L1=NULL,*L2=NULL; 
	
	L1=create(L1,5);
	L2=create(L2,5);
	
	//�ϲ����� 
    L1=merge(L1,L2);
    printf("�ϲ�����ģ�\n");
	display(L1);
	
	//����ɾ���ĵ��Բ��� 
	L1=ListInsert(L1,2,0);
	printf("����֮�� \n");
	display(L1);
	
	L1=ListDelete(L1,2); 
	printf("ɾ��֮��\n");
	display(L1);
	
	return 0;
}
