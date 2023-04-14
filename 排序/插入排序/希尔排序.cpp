#include<iostream>

using namespace std;

void ShellInsert(int *arr,int n,int dk)
{//dk为增量 
	int i,j;
	for(i=dk+1;i<=n;++i)//直接插入排序改编而来 
	{
		if(arr[i]<arr[i-dk])
		{
			arr[0]=arr[i];// 暂时存放元素，不做哨兵因为-dk不是-1有可能-到负数 
			for(j=i-dk;j>0&&arr[0]<arr[j];j=j-dk)
			arr[j+dk]=arr[j];
			arr[j+dk]=arr[0];	
		}
	}
}

void ShellSort(int *arr,int n)
{
	int dk=n;
	while(dk>1)//dk==1循环也是要做的 
	{
		dk=dk/3+1;//为增量序列对数组做t趟希尔排序
		ShellInsert(arr,n,dk);
	} 
} 

int main()
{
	int *arr=nullptr,n;
	cout<<"请你输入数组有多少个元素: ";cin>>n;
	arr=new(nothrow) int[n+1];//0号位置不用 
	
	for(int i=1;i<=n;i++)
	{
	cin>>arr[i]; 
	}
	
	//开始希尔排序 
	ShellSort(arr,n);
	for(int i=1;i<=n;++i)
	cout<<arr[i]<<" ";	
	
	return 0;
}
/*测试数据： 
5
5 4 1 3 2
答案：
12345*/
