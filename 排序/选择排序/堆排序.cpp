#include<iostream>

using namespace std;

void HeapAdjust(int *arr,int pos,int n)//筛选 
{
	int rc=arr[pos];//暂时存放
	for(int i=2*pos;i<=n;i*=2)//沿key较大孩子向下筛选
	{
		if(i<n&&arr[i]<arr[i+1]) ++i;//找到最大孩子
		if(rc>=arr[i]) break;//满足大顶堆的要求
		arr[pos]=arr[i];pos=i;//不满足情况下 进行筛选 
	} 
	arr[pos]=rc;//插入 
} 

void CreateHeap(int *arr,int n)
{//数组0号位置不用 
	for(int i=n/2;i>=1;--i)//非终端结点都要调整为堆
	HeapAdjust(arr,i,n); 
}

void HeapSort(int *arr,int n)
{
	CreateHeap(arr,n);//建立初堆
	
	for(int i=n;i>1;--i)//为根节点的时候不用交换，也没人 跟他交换 
	{
	cout<<arr[1]<<" ";//输出堆顶元素
	swap(arr[1],arr[i]);//根与最后一个结点交换
	HeapAdjust(arr,1,i-1);//重新调整为大根堆	
	} 
	
	cout<<arr[1]<<" ";//输出堆顶元素
}

int main()
{
	int *arr=nullptr,n;
	cout<<"请你输入数组有多少个元素: ";cin>>n;
	arr=new(nothrow) int[n+1];//0号位置不用 
	
	for(int i=1;i<=n;i++)
	cin>>arr[i]; 
	
	//开始堆排序
	HeapSort(arr,n);
	return 0;
}

/*测试数据： 
5
1 4 2 5 3
答案：
5 4 3 2 1*/
