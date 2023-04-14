#include<iostream>

using namespace std;

void SelectSort(int *arr,int n)
{
	int i,j,k;
	for(i=1;i<n;++i)//通过n-1次比较，从n个记录中选出关键字最小的记录
	{
		k=i;
		for(j=i+1;j<=n;++j)//要遍历从i+1开始的整个数组选出比i+1还要小的值 
		{
			if(arr[k]>arr[j])
			k=j;//找到最小值的下标 
		}
		if(k!=i)
		swap(arr[k],arr[i]);//交换 
	}
	
}

int main()
{
	int *arr=nullptr,n;
	cout<<"请你输入数组有多少个元素: ";cin>>n;
	
	arr=new(nothrow) int[n+1];//0号位置不用 
	for(int i=1;i<=n;i++)
	cin>>arr[i]; 
	
	//开始选择排序
	SelectSort(arr,n); 
	for(int i=1;i<=n;++i)
	cout<<arr[i]<<" "; 
	
	return 0;
}

/*测试数据： 
5
5 4 1 3 2
答案：
12345*/
