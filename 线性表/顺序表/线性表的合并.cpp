#include<stdio.h>
#include<malloc.h>//ʵ����˳����ʽ���������Ա�ϲ� 

#define Maxsize 100

typedef struct 
{
	int *elem;
	int length;//��¼˳���ĳ���	
}Sqlist;

void InitList(Sqlist &L)
{
	L.elem=(int *)malloc(4*Maxsize);
	L.length=0;//˳���ĳ��ȳ�ʼ��Ϊ0 
}

int ListLength(Sqlist L)
{return L.length;}

bool GetElem(Sqlist L,int i,int &e)//ȡֵ����
{
	if(i<1||i>L.length){printf("i������ȡֵ��Χ\n");return false;}
	e=L.elem[i-1];
	return true;
} 

int LocateElem(Sqlist L,int e)//��λԪ�ص�λ�� 
{
	int i;
	for(i=0;i<L.length;i++)
	if(L.elem[i]==e)//�ҵ���Ҫȡ��ֵ
	return i+1;
	
	return 0;//���򷵻�0 
}

void ListInsert(Sqlist &L,int i,int e)
{
	if(i<1||(i>L.length+1)){printf("i��λ�ò�����\n");return ;}
	if(L.length==Maxsize){printf("˳����Ѿ�����\n");return ;}
	
	int j;
	for(j=L.length-1;j>=i-1;j--)
	L.elem[j+1]=L.elem[j];//ȫ������ƶ�
	
	L.elem[i-1]=e; 
	++L.length;//����ҲҪ��֮���� 
}

void display(Sqlist L) 
{
	int i;
	for(i=0;i<L.length;i++)
	printf("elem:%d ",L.elem[i]);
	putchar('\n');
}
void MergeList(Sqlist &L1,Sqlist &L2)
{
	int m=ListLength(L1),n=ListLength(L2);
	int e;
	
	for(int i=1;i<=n;i++)//��L2��ÿ��Ԫ���ó�����L1�бȽ� 
	{
		GetElem(L2,i,e);//��L2�������shuju 
		if(!LocateElem(L1,e))//�ж�e�Ƿ�����L1����������� 
		ListInsert(L1,++m,e);//�������� 
	}
}

void MergeList_sq(Sqlist L1,Sqlist L2,Sqlist &L3)//�����ĺϲ� 
{
	L3.length=L1.length+L2.length;
	L3.elem=( int*)malloc(sizeof(int)*L3.length);
	int *p3=L3.elem,*p2=L2.elem,*p1=L1.elem,*p1_last=L1.elem+L1.length-1,*p2_last=L2.elem+L2.length-1;
	
	while((p1<=p1_last)&&(p2<=p2_last))//������һ���ﵽ��ĩβ������ѭ��  [ͨ����ַ�ж�] 
	{
		if(*p1<=*p2) *p3++=*p1++;//ֵ�ǵݼ�
		else *p3++=*p2++; 
	}
	
	//��ʣ����е����ݷ���p3��ȥ 
	while(p1<=p1_last) *p3++=*p1++;//p2�Ѿ������˱�β
	while(p2<=p2_last) *p3++=*p2++;
	
}

void clearList(Sqlist &L1)
{
	L1.length=0;
}

void destory(Sqlist &L1)
{
	if(L1.elem)
	{free(L1.elem);L1.elem=nullptr;L1.length=0;}
}

int main()
{
	Sqlist L1,L2,L3; 
	InitList(L1);	InitList(L2);
	
	for(int i=1;i<=5;i++)
		ListInsert(L1,i,i);
	
	for(int i=1;i<=10;i++)
	ListInsert(L2,i,i);
	
	MergeList(L1,L2);//�ϲ���L1 
	display(L1);
	
	//��ղ��� 
	clearList(L1);
	clearList(L2);
	
	ListInsert(L1,1,3);
	ListInsert(L1,2,5);
	ListInsert(L1,3,8); 
	ListInsert(L1,4,11);
	
    ListInsert(L2,1,2);
	ListInsert(L2,2,6);
	ListInsert(L2,3,8);
	ListInsert(L2,4,9);
	ListInsert(L2,5,11);
	ListInsert(L2,6,15);
	
	MergeList_sq(L1,L2,L3);
	display(L3);
		
	return 0;
}
