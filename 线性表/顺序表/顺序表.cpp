#include<iostream>

#define MAXSIZE 100//宏定义最大容量为100 

using namespace std;

//顺序表
typedef struct 
{
	int *elem;
	int length;	
}SqList;

void InitList(SqList &L)
{
	L.elem=new int[MAXSIZE];//分配内存空间
	if(!L.elem)abort();
	L.length=0;//长度初始化为0 
}

//取值操作 
bool GetElem(SqList L,int i,int &e)//i在哪个位置上取值，e把取到的值带回 
{
	if(i<1||i>L.length)return false;
	e=L.elem[i-1];//i是从1，2，3，4....数组是0,1,2,3 
	return true;
}

//查找操作
int LocateElem(SqList L,int e)//在顺序表中查找元素e找到则返回序号i+1
{
	for(int i=0;i<L.length;i++)
	if(L.elem[i]==e)return i+1;//i是从1，2，3，4....数组是0,1,2,3 
	return 0;//没有找到返回0 
} 

//插入操作
bool ListInsert(SqList &L,int i,int e)//在i位置插入e
{
	//判断条件有两个1:插入的位置是否合理2: 顺序表是否满了
	if(i<1||i>L.length+1){cout<<"插入的位置不合理"<<endl;return false;}
	if(L.length==MAXSIZE){cout<<"顺序表已经满了"<<endl;return false;}
	
	for(int j=L.length-1;j>=i-1;j--)//i-1因为是i是从1开始 
	L.elem[j+1]=L.elem[j];//移动
	
	L.elem[i-1]=e;
	++L.length;//长度++
	
	return true; 
}

//删除操作 
bool ListDelete(SqList &L,int i)
{
	if(i<1||i>L.length){cout<<"删除的位置不合理"<<endl;return false;}
	
	for(int j=i;j<=L.length-1;j++)
	L.elem[j-1]=L.elem[j];//移动
	
	--L.length;
	
	return true; 
}

void display(SqList L) 
{
	for(int i=0;i<=L.length-1;i++)
	cout<<L.elem[i]<<" ";
	cout<<endl;
}

int main()
{
	SqList L;
	
	InitList(L);
	for(int i=1;i<=99;i++)
		ListInsert(L,i,i);//在第i个位置上插入i 
	
	display(L);
	
	int e=0;
	if(!GetElem(L,99,e)){cout<<"取值失败\n";}
		cout<<"99号位置取值为："<<e<<endl;
	
	if(!ListDelete(L,99)){cout<<"删除失败\n";}
		display(L);
	
	return 0;
}
