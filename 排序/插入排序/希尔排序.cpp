#include<iostream>

using namespace std;

void ShellInsert(int *arr,int n,int dk)
{//dkΪ���� 
	int i,j;
	for(i=dk+1;i<=n;++i)//ֱ�Ӳ�������ı���� 
	{
		if(arr[i]<arr[i-dk])
		{
			arr[0]=arr[i];// ��ʱ���Ԫ�أ������ڱ���Ϊ-dk����-1�п���-������ 
			for(j=i-dk;j>0&&arr[0]<arr[j];j=j-dk)
			arr[j+dk]=arr[j];
			arr[j+dk]=arr[0];	
		}
	}
}

void ShellSort(int *arr,int n)
{
	int dk=n;
	while(dk>1)//dk==1ѭ��Ҳ��Ҫ���� 
	{
		dk=dk/3+1;//Ϊ�������ж�������t��ϣ������
		ShellInsert(arr,n,dk);
	} 
} 

int main()
{
	int *arr=nullptr,n;
	cout<<"�������������ж��ٸ�Ԫ��: ";cin>>n;
	arr=new(nothrow) int[n+1];//0��λ�ò��� 
	
	for(int i=1;i<=n;i++)
	{
	cin>>arr[i]; 
	}
	
	//��ʼϣ������ 
	ShellSort(arr,n);
	for(int i=1;i<=n;++i)
	cout<<arr[i]<<" ";	
	
	return 0;
}
/*�������ݣ� 
5
5 4 1 3 2
�𰸣�
12345*/
