#include<iostream>

using namespace std;

void BInsertSort(int *arr,int n)
{
	int low,high,mid;//�±귶Χ 
	for(int i=2;i<=n;++i)
	{
		arr[0]=arr[i];//��Ϊ�ݴ�Ԫ�أ�����Ϊ�ڱ� 
		low=1,high=i-1;//��ʱ 
		while(low<=high)
		{
			mid=(low+high)/2;//ȷ�Ϸ�Χ�����ӱ������ӱ� 
			if(arr[0]<arr[mid]) high=mid-1;
			else low=mid+1;
		} 
		
		//�Ż�������һ�� 
		for(int j=i-1;j>=high+1;--j)//���ƶ�Ԫ�� high+1���ǲ���λ�� 
		arr[j+1]=arr[j];
		
		//������ԭ����λ��ҲҪ������һ������ֱ�Ӳ�������Ĳ�ͬ 
		arr[high+1]=arr[0];//���뵽���ʵ�λ�� 
	}
	
	for(int i=1;i<=n;++i)
	cout<<arr[i]<<" "; 
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
	
	//��ʼ�۰��������
	BInsertSort(arr,n);
	
	return 0;
}
/*�������ݣ� 
5
5 4 1 3 2
�𰸣�
12345*/
