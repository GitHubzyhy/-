#include<iostream>

using namespace std;

void InsertSort(int arr[],int n)//0��λ�ò��õ��ڱ� 
{
    int i,j;
    
	//��ʼֱ�Ӳ������� 
	for(i=2;i<=n;i++)
	{
		if(arr[i]<arr[i-1])//<��ʱ����Ҫ��r[i] ���������ӱ�
		{
			arr[0]=arr[i];//�ŵ���������
			for(j=i-1;arr[0]<arr[j];--j)//1...i-1   �����ڲ��� 
			{
				arr[j+1]=arr[j];//��¼�������
			} 
			arr[j+1]=arr[0];//�ҵ����ʵĲ���λ�� 
		}
	}
	
	//���
	for(i=1;i<=n;i++)
	cout<<arr[i]<<" "; 
}

int main()
{
	int *arr=nullptr,n;
	cout<<"�������������ж��ٸ�Ԫ��: ";cin>>n;
	arr=new(nothrow) int[n+1];//0��λ�ò��� 
	
	for(int i=1;i<=n;i++)
	cin>>arr[i]; 
	
	InsertSort(arr,n);
	return 0;
}
/*�������ݣ� 
5
5 4 1 3 2
�𰸣�
12345*/
