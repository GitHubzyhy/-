#include<iostream>

using namespace std;

void SelectSort(int *arr,int n)
{
	int i,j,k;
	for(i=1;i<n;++i)//ͨ��n-1�αȽϣ���n����¼��ѡ���ؼ�����С�ļ�¼
	{
		k=i;
		for(j=i+1;j<=n;++j)//Ҫ������i+1��ʼ����������ѡ����i+1��ҪС��ֵ 
		{
			if(arr[k]>arr[j])
			k=j;//�ҵ���Сֵ���±� 
		}
		if(k!=i)
		swap(arr[k],arr[i]);//���� 
	}
	
}

int main()
{
	int *arr=nullptr,n;
	cout<<"�������������ж��ٸ�Ԫ��: ";cin>>n;
	
	arr=new(nothrow) int[n+1];//0��λ�ò��� 
	for(int i=1;i<=n;i++)
	cin>>arr[i]; 
	
	//��ʼѡ������
	SelectSort(arr,n); 
	for(int i=1;i<=n;++i)
	cout<<arr[i]<<" "; 
	
	return 0;
}

/*�������ݣ� 
5
5 4 1 3 2
�𰸣�
12345*/
