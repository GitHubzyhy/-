#include<iostream>

using namespace std;

void bubble_sort(int *arr,int n)
{
	int i,j;
	bool flag=1;//如果没有交换就结束循环
	for(i=1;i<=n-1&&flag;++i)
	{
		flag=0;//每次循环刷新 
		for(j=1;j<=n-i;++j)
		{
			flag=1;
			if(arr[j]>arr[j+1])//是逆序就交换 
			swap(arr[j],arr[j+1]);//进行交换 
		}
	} 
} 

int main()
{
	int *arr=nullptr,n;
	cout<<"请你输入数组有多少个元素: ";cin>>n;
	arr=new(nothrow) int[n+1];//0号位置不用 

	for(int i=1;i<=n;i++)
	cin>>arr[i]; 
	
	//开始冒泡排序 
	bubble_sort(arr,n); 
	for(int i=1;i<=n;i++)
	cout<<arr[i]<<" ";	
		
	return 0;
}

/*测试数据： 
5
5 4 1 3 2
答案：
12345*/
