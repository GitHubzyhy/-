#include<iostream>

using namespace std;

void BInsertSort(int *arr,int n)
{
	int low,high,mid;//下标范围 
	for(int i=2;i<=n;++i)
	{
		arr[0]=arr[i];//作为暂存元素，不作为哨兵 
		low=1,high=i-1;//此时 
		while(low<=high)
		{
			mid=(low+high)/2;//确认范围在左子表还是右子表 
			if(arr[0]<arr[mid]) high=mid-1;
			else low=mid+1;
		} 
		
		//优化的是这一步 
		for(int j=i-1;j>=high+1;--j)//后移动元素 high+1就是插入位置 
		arr[j+1]=arr[j];
		
		//就算在原本的位置也要进行这一步，跟直接插入排序的不同 
		arr[high+1]=arr[0];//插入到合适的位置 
	}
	
	for(int i=1;i<=n;++i)
	cout<<arr[i]<<" "; 
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
	
	//开始折半插入排序
	BInsertSort(arr,n);
	
	return 0;
}
/*测试数据： 
5
5 4 1 3 2
答案：
12345*/
