#include<iostream>

using namespace std;

void HeapAdjust(int *arr,int pos,int n)//ɸѡ 
{
	int rc=arr[pos];//��ʱ���
	for(int i=2*pos;i<=n;i*=2)//��key�ϴ�������ɸѡ
	{
		if(i<n&&arr[i]<arr[i+1]) ++i;//�ҵ������
		if(rc>=arr[i]) break;//����󶥶ѵ�Ҫ��
		arr[pos]=arr[i];pos=i;//����������� ����ɸѡ 
	} 
	arr[pos]=rc;//���� 
} 

void CreateHeap(int *arr,int n)
{//����0��λ�ò��� 
	for(int i=n/2;i>=1;--i)//���ն˽�㶼Ҫ����Ϊ��
	HeapAdjust(arr,i,n); 
}

void HeapSort(int *arr,int n)
{
	CreateHeap(arr,n);//��������
	
	for(int i=n;i>1;--i)//Ϊ���ڵ��ʱ���ý�����Ҳû�� �������� 
	{
	cout<<arr[1]<<" ";//����Ѷ�Ԫ��
	swap(arr[1],arr[i]);//�������һ����㽻��
	HeapAdjust(arr,1,i-1);//���µ���Ϊ�����	
	} 
	
	cout<<arr[1]<<" ";//����Ѷ�Ԫ��
}

int main()
{
	int *arr=nullptr,n;
	cout<<"�������������ж��ٸ�Ԫ��: ";cin>>n;
	arr=new(nothrow) int[n+1];//0��λ�ò��� 
	
	for(int i=1;i<=n;i++)
	cin>>arr[i]; 
	
	//��ʼ������
	HeapSort(arr,n);
	return 0;
}

/*�������ݣ� 
5
1 4 2 5 3
�𰸣�
5 4 3 2 1*/
