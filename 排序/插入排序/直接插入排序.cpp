#include<iostream>

using namespace std;

void InsertSort(int arr[],int n)//0号位置不用当哨兵 
{
    int i,j;
    
	//开始直接插入排序 
	for(i=2;i<=n;i++)
	{
		if(arr[i]<arr[i-1])//<的时候，需要将r[i] 插入有序子表
		{
			arr[0]=arr[i];//放到监视哨中
			for(j=i-1;arr[0]<arr[j];--j)//1...i-1   监视哨查找 
			{
				arr[j+1]=arr[j];//记录逐个后移
			} 
			arr[j+1]=arr[0];//找到合适的插入位置 
		}
	}
	
	//输出
	for(i=1;i<=n;i++)
	cout<<arr[i]<<" "; 
}

int main()
{
	int *arr=nullptr,n;
	cout<<"请你输入数组有多少个元素: ";cin>>n;
	arr=new(nothrow) int[n+1];//0号位置不用 
	
	for(int i=1;i<=n;i++)
	cin>>arr[i]; 
	
	InsertSort(arr,n);
	return 0;
}
/*测试数据： 
5
5 4 1 3 2
答案：
12345*/
