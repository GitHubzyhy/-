#include<iostream>

using namespace std;

int Partition(int *arr,int low,int high)
{
	arr[0]=arr[low];//ѡ������
	
	while(low<high)//û��=
	{// ������˰�ǰ�棬ǰ����˰���� 
	while(low<high&&arr[high]>=arr[0]) --high;
	arr[low]=arr[high];//���������������ʱ�򽻻�
	
	while(low<high&&arr[low]<=arr[0]) ++low;
	arr[high]=arr[low];	
	}
	
	arr[low]=arr[0];//low��high����ָ��ͬһ��λ��
	return low; 
}

void Qsort(int *arr,int low,int high)
{
	if(low<high)//���ȴ���1 
	{
		int pivotloc=Partition(arr,low,high);//����һ��Ϊ�� 
		 Qsort(arr,low,pivotloc-1);//���ӱ�
		 Qsort(arr,pivotloc+1,high);//���ӱ� 
	}
	
} 

int main()
{
	int *arr=nullptr,n;
	cout<<"�������������ж��ٸ�Ԫ��: ";cin>>n;
	
	arr=new(nothrow) int[n+1];//0��λ�ò��� 
	for(int i=1;i<=n;i++)
	cin>>arr[i]; 
	
	//��ʼ�������� 
	Qsort(arr,1,n);
	for(int i=1;i<=n;++i)
	cout<<arr[i]<<" ";
	
	return 0; 
}
/*�������ݣ� 
5
5 4 1 3 2
�𰸣�
12345*/
