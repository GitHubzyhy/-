#include<iostream>

using namespace std;

void bubble_sort(int *arr,int n)
{
	int i,j;
	bool flag=1;//���û�н����ͽ���ѭ��
	for(i=1;i<=n-1&&flag;++i)
	{
		flag=0;//ÿ��ѭ��ˢ�� 
		for(j=1;j<=n-i;++j)
		{
			flag=1;
			if(arr[j]>arr[j+1])//������ͽ��� 
			swap(arr[j],arr[j+1]);//���н��� 
		}
	} 
} 

int main()
{
	int *arr=nullptr,n;
	cout<<"�������������ж��ٸ�Ԫ��: ";cin>>n;
	arr=new(nothrow) int[n+1];//0��λ�ò��� 

	for(int i=1;i<=n;i++)
	cin>>arr[i]; 
	
	//��ʼð������ 
	bubble_sort(arr,n); 
	for(int i=1;i<=n;i++)
	cout<<arr[i]<<" ";	
		
	return 0;
}

/*�������ݣ� 
5
5 4 1 3 2
�𰸣�
12345*/
