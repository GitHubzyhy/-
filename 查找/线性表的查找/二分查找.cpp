#include<bits/stdc++.h>

using namespace std;

typedef int ElemType;

typedef struct//顺序表的定义 
{
	ElemType *R;
	int length;
}SSTable;

int Search_Bin(SSTable ST,ElemType key)
{
	//在递增有序表 ST中用折半查找关键字=key的数据元素，找到则返回在表中的位置，否则为0
	int low=1,high=ST.length,mid;//0号位置不用
	while(low<=high)//=时候区间还有最后一个结点需要比较
	{
		mid=(low+high)/2;//找中间的位置
		if(key==ST.R[mid]) return mid;
		else if(key<ST.R[mid]) high=mid-1;
		else low=mid+1;
	} 
	return 0;//找到失败！ 
}

int Search_Bin_recursion(SSTable ST,ElemType key,int low,int high,int mid)
{
	if(low>high) return 0;//没有找到 
	else 
	{
		if(ST.R[mid]==key) return mid;//找到了 
		else if(ST.R[mid]<key) 
		{
			high=mid-1;
	    	return Search_Bin_recursion(ST,key,low,high,(low+high)/2); 	
		}
		else
		{
			low=mid+1;
			return Search_Bin_recursion(ST,key,low,high,(low+high)/2);
		}
	}
}

int main()
{
	SSTable ST;
	cout<<"请你输入数组的长度\n";
	cin>>ST.length;

	cout<<"请你输入数组的值\n";
	ST.R=new(nothrow) ElemType[ST.length+1];

	for(int i=1;i<=ST.length;i++)
	cin>>ST.R[i];

	sort(ST.R+1,ST.R+ST.length+1);// 1关键字有序排列和 2顺序存储结构
	int pos=Search_Bin(ST,3) ;
	for(int i=1;i<=ST.length;i++)
	cout<<ST.R[i]<<" "; 
	
	if(pos)
		cout<<"位置："<<pos<<'\n';
	else
	    cout<<"查找失败\n";
 /*-----------------------------------------------------------------------------------*/
	 pos=Search_Bin_recursion(ST,3,1,ST.length,(1+ST.length)/2);
 	 if(pos)
 		 cout<<"位置："<<pos<<'\n';
 	 else
 	     cout<<"查找失败\n";
 	     
 	return 0;	
}
