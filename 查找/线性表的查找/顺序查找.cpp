#include<iostream>

using namespace std;

typedef int ElemType;

typedef struct
{
	ElemType *R;
	int length;
}SSTable;

int Search_Seq1(SSTable ST,ElemType key)//顺序查找 
{//找到则返回元素在表中的位置，否则为0 
	for(int i=ST.length;i>1;--i)//0号位置不用 
	if(ST.R[i]==key) return i;
	
	return 0;
}//比较了两次，是否找到和是否越界 

int Search_Seq2(SSTable ST,ElemType key)//设置监视哨的顺序查找
{
	int i;
	ST.R[0]=key;//监视哨
	for(i=ST.length;ST.R[i]!=key;--i);//分号
	return i; 
}
 
int main()
{
	SSTable ST;
	cout<<"请你输入数组的长度length\n";
	cin>>ST.length;
	ST.R=new(nothrow) ElemType[ST.length+1];//0号位置不用 
	
	cout<<"请你输入数组内的元素\n";
	for(int i=1;i<=ST.length;i++)
	cin>>ST.R[i];
	
	int pos=Search_Seq1(ST,5);
	if(pos)
	cout<<"位置在："<<pos;
	else
	cout<<"没找到";
	
	pos=Search_Seq2(ST,5);
	if(pos)
	cout<<"\n位置在："<<pos;
	else
	cout<<"\n没找到";
	
	return 0;
}
