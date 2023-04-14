#include<iostream>
using namespace std;

typedef struct Pnode//��������ʽ[�����]��� 
{
	float coef;//ϵ��	
	int expn;//ָ��
	struct Pnode *next;	
}Pnode,*Polynomial;

void create(Polynomial &L,int n)
{
	Pnode *s=nullptr,*pre=nullptr,*q=nullptr;//preָ���һ������������ָ���Ľ���ǰ�� 
	L=new(nothrow) Pnode;
	L->next=nullptr;//������ͷ�ڵ�ĵ�����
    
	for(int i=1;i<=n;i++)
	 {
		s=new(nothrow) Pnode;
		
		cout<<"����ϵ����ָ��:";
		cin>>s->coef>>s->expn;
		
		pre=L;//���ڱ���q��ǰ����ֵΪͷ�ڵ�
		q=L->next;//q�ĳ�ֵΪ��Ԫ�ڵ�[ÿһ��ѭ����������]
		
		while(q&&q->expn<s->expn)//һ�����Ƚ��ҵ���һ������������ָ������(ֵ�ǵݼ�)
		{pre=q; q=q->next;}//ѭ��������ʱ��pre�Ǳȵ�һ�����ǰ���ڵ㣬q���ǵ�һ�����ڵĽڵ� 
		
		s->next =q;
		pre->next= s;//��������s���뵽q��ǰ��pre֮�� 
	 }
}

void display(Polynomial L)
{
	Pnode *p=L->next;//ָ����Ԫ�ڵ�
	while(1)
	{
		cout<<"p->coef:"<<p->coef<<" p->expn:"<<p->expn<<" ";
		if(p->next)
		p=p->next;
		else break;
	} 
	cout.put('\n');
}

void clear(Polynomial &L)//��ղ��� 
{
	Pnode *p=L->next,*q=nullptr;
	while(p)
	{
		q=p->next;
		delete p;
		p=q;
	}
}

void destory(Polynomial &L)//���ٲ���
{
	Pnode *p=nullptr;
	while(L)
	{
		p=L;
		L=L->next; 
		delete p;
	}
	L=nullptr;
}
 
void merge(Polynomial &L1,Polynomial &L2)//����ʽ����������������ĺϲ�
{
	Pnode *p1=L1->next,*p2=L2->next,*p3=L1,*temp=nullptr;//p1,p2ָ����Ԫ�ڵ�p3��L1��ͷ�ڵ���Ϊ��ʼ 
	double sum=0;
	
	while(p1&&p2)//p1��p2�ǿ�
	{
		if(p1->expn==p2->expn)//��һ�����(ָ����ͬ�����)
		{
		sum=p1->coef+p2->coef;//ϵ����� 
		
			if(sum)//�Ͳ���0 
			{
				p1->coef=sum;//��ֵ 
				p3->next=p1;//p1���ӵ�p3{��p1��ͷ�ڵ���Ϊ��ʼ}��ȥ 
				p3=p1;//p3�ƶ� 
				p1=p1->next;
				temp=p2; p2=p2->next; delete temp;//ɾ��p2��ǰ�ڵ� 
			}
			else//һ��ϵ�����Ϊ0 
			{
				temp=p1;p1=p1->next;delete temp;//p1�ڵ�ɾ�����ƶ� 
				temp=p2;p2=p2->next;delete temp;//p2�ڵ�ɾ�����ƶ� 
			}
			
		} 
		else if(p1->expn<p2->expn)//p1��ָ��С��p2��ָ�� 
		{
			p3->next=p1;//ָ��С������ 
			p3=p1;p1=p1->next;
		}
		else//p1��ָ������p2��ָ�� 
		{
			p3->next=p2;//ָ��С������ 
			p3=p2;p2=p2->next;
		}
	} 
	
	p3->next=p1?p1:p2;//�жϻ����ĸ������Ƿǿ�״̬ȫ����������{�������������} 
	delete L2;//ɾ��L2��ͷ�ڵ�(�����Ѿ������ӻ��߱�ɾ��) 
} 

int main()
{
	Polynomial L1=nullptr,L2=nullptr;
	
	cout<<"p1�Ĵ���\n"; 
	create(L1,2);
	cout<<"p2�Ĵ���\n"; 
	create(L2,5);
	
	merge(L1,L2);
	display(L1);
	destory(L1);
	return 0;
}
