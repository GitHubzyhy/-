#include<iostream>

using namespace std;

void merge(int *R,int *T,int low,int mid,int high)
{//将较小者放入T中 
	int i=low,j=mid+1,k=low;//左右子表指针，和T数组的下标
	
	while(i<=mid&&j<=high)//一旦其中一个表为空将另一非空表余下的部分直接复制到T中 
	{
		if(R[i]<=R[j]) T[k++]=R[i++];
		else T[k++]=R[j++]; 
	} 
	while(i<=mid) T[k++]=R[i++];//将剩余部分复制到T中 
	while(j<=high) T[k++]=R[j++];
	//一定要将原来的数组更新，因为此时排序后在T中是有序的，但是在原来数组R还是无序的 \
	例子low=1 mid=1 high=2 \
	左子表退出右子表退出返回本层循环 开始合并 54变成45接下来返回\
	上一层 时候low=1 mid=2 high=3\
	进入右子表(low=3 high=3) 右子表进入直接返回本层，就要进行合并处理low=1 mid=2 high=3带入上面的while循环可以得出只执行一次\
	 之前54已经排序为45 如果不更新的话，就是541进行排序，上面的while循环执行一次就是154不是145 
	for(i=low;i<=high;++i)
	{
		R[i]=T[i];
	}
          
} 

void MSort(int *R,int *T,int low,int high)
{//R归并排序后放到T里面
	
	if(low<high)//序列中超过一个元素
	{
		int mid=(low+high)/2;//求出分割点 
		MSort(R,T,low,mid);//左子表
		MSort(R,T,mid+1,high);//右子表
		merge(R,T,low,mid,high);//合并成有序表 
	} 
	
}
 
int main()
{
	int *arr=nullptr,n,*t=nullptr;
	cout<<"请你输入数组有多少个元素: ";cin>>n;
	
	arr=new(nothrow) int[n+1];//0号位置不用
	t=new(nothrow) int[n+1]; 
	for(int i=1;i<=n;i++)
	cin>>arr[i]; 
	
	//开始归并排序 
	MSort(arr,t,1,n);
	for(int i=1;i<=n;i++)
	cout<<t[i]<<" ";
	
	return 0;
}
/*测试数据： 
5
5 4 1 3 2
答案：
12345*/
