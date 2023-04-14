#include<stdio.h>
#include<malloc.h>//实现用顺序形式将两个线性表合并 

#define Maxsize 100

typedef struct 
{
	int *elem;
	int length;//记录顺序表的长度	
}Sqlist;

void InitList(Sqlist &L)
{
	L.elem=(int *)malloc(4*Maxsize);
	L.length=0;//顺序表的长度初始化为0 
}

int ListLength(Sqlist L)
{return L.length;}

bool GetElem(Sqlist L,int i,int &e)//取值操作
{
	if(i<1||i>L.length){printf("i超过了取值范围\n");return false;}
	e=L.elem[i-1];
	return true;
} 

int LocateElem(Sqlist L,int e)//定位元素的位置 
{
	int i;
	for(i=0;i<L.length;i++)
	if(L.elem[i]==e)//找到了要取的值
	return i+1;
	
	return 0;//否则返回0 
}

void ListInsert(Sqlist &L,int i,int e)
{
	if(i<1||(i>L.length+1)){printf("i的位置不合理\n");return ;}
	if(L.length==Maxsize){printf("顺序表已经满了\n");return ;}
	
	int j;
	for(j=L.length-1;j>=i-1;j--)
	L.elem[j+1]=L.elem[j];//全体向后移动
	
	L.elem[i-1]=e; 
	++L.length;//长度也要随之增加 
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
	
	for(int i=1;i<=n;i++)//把L2中每个元素拿出来到L1中比较 
	{
		GetElem(L2,i,e);//从L2中拿输出shuju 
		if(!LocateElem(L1,e))//判断e是否属于L1不属于则插入 
		ListInsert(L1,++m,e);//在最后插入 
	}
}

void MergeList_sq(Sqlist L1,Sqlist L2,Sqlist &L3)//有序表的合并 
{
	L3.length=L1.length+L2.length;
	L3.elem=( int*)malloc(sizeof(int)*L3.length);
	int *p3=L3.elem,*p2=L2.elem,*p1=L1.elem,*p1_last=L1.elem+L1.length-1,*p2_last=L2.elem+L2.length-1;
	
	while((p1<=p1_last)&&(p2<=p2_last))//其中有一个达到了末尾则跳出循环  [通过地址判断] 
	{
		if(*p1<=*p2) *p3++=*p1++;//值非递减
		else *p3++=*p2++; 
	}
	
	//将剩余表中的数据放在p3中去 
	while(p1<=p1_last) *p3++=*p1++;//p2已经到达了表尾
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
	
	MergeList(L1,L2);//合并入L1 
	display(L1);
	
	//清空操作 
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
