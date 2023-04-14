#include<iostream>

using namespace std;

int Partition(int *arr,int low,int high)
{
	arr[0]=arr[low];//选择枢轴
	
	while(low<high)//没有=
	{// 后面空了搬前面，前面空了搬后面 
	while(low<high&&arr[high]>=arr[0]) --high;
	arr[low]=arr[high];//不满足条件逆序的时候交换
	
	while(low<high&&arr[low]<=arr[0]) ++low;
	arr[high]=arr[low];	
	}
	
	arr[low]=arr[0];//low和high现在指向同一个位置
	return low; 
}

void Qsort(int *arr,int low,int high)
{
	if(low<high)//长度大于1 
	{
		int pivotloc=Partition(arr,low,high);//将其一分为二 
		 Qsort(arr,low,pivotloc-1);//左子表
		 Qsort(arr,pivotloc+1,high);//右子表 
	}
	
} 

int main()
{
	int *arr=nullptr,n;
	cout<<"请你输入数组有多少个元素: ";cin>>n;
	
	arr=new(nothrow) int[n+1];//0号位置不用 
	for(int i=1;i<=n;i++)
	cin>>arr[i]; 
	
	//开始快速排序 
	Qsort(arr,1,n);
	for(int i=1;i<=n;++i)
	cout<<arr[i]<<" ";
	
	return 0; 
}
/*测试数据： 
5
5 4 1 3 2
答案：
12345*/
