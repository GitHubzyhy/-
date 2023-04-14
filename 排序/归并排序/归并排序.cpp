#include<iostream>

using namespace std;

void merge(int *R,int *T,int low,int mid,int high)
{//����С�߷���T�� 
	int i=low,j=mid+1,k=low;//�����ӱ�ָ�룬��T������±�
	
	while(i<=mid&&j<=high)//һ������һ����Ϊ�ս���һ�ǿձ����µĲ���ֱ�Ӹ��Ƶ�T�� 
	{
		if(R[i]<=R[j]) T[k++]=R[i++];
		else T[k++]=R[j++]; 
	} 
	while(i<=mid) T[k++]=R[i++];//��ʣ�ಿ�ָ��Ƶ�T�� 
	while(j<=high) T[k++]=R[j++];
	//һ��Ҫ��ԭ����������£���Ϊ��ʱ�������T��������ģ�������ԭ������R��������� \
	����low=1 mid=1 high=2 \
	���ӱ��˳����ӱ��˳����ر���ѭ�� ��ʼ�ϲ� 54���45����������\
	��һ�� ʱ��low=1 mid=2 high=3\
	�������ӱ�(low=3 high=3) ���ӱ����ֱ�ӷ��ر��㣬��Ҫ���кϲ�����low=1 mid=2 high=3���������whileѭ�����Եó�ִֻ��һ��\
	 ֮ǰ54�Ѿ�����Ϊ45 ��������µĻ�������541�������������whileѭ��ִ��һ�ξ���154����145 
	for(i=low;i<=high;++i)
	{
		R[i]=T[i];
	}
          
} 

void MSort(int *R,int *T,int low,int high)
{//R�鲢�����ŵ�T����
	
	if(low<high)//�����г���һ��Ԫ��
	{
		int mid=(low+high)/2;//����ָ�� 
		MSort(R,T,low,mid);//���ӱ�
		MSort(R,T,mid+1,high);//���ӱ�
		merge(R,T,low,mid,high);//�ϲ�������� 
	} 
	
}
 
int main()
{
	int *arr=nullptr,n,*t=nullptr;
	cout<<"�������������ж��ٸ�Ԫ��: ";cin>>n;
	
	arr=new(nothrow) int[n+1];//0��λ�ò���
	t=new(nothrow) int[n+1]; 
	for(int i=1;i<=n;i++)
	cin>>arr[i]; 
	
	//��ʼ�鲢���� 
	MSort(arr,t,1,n);
	for(int i=1;i<=n;i++)
	cout<<t[i]<<" ";
	
	return 0;
}
/*�������ݣ� 
5
5 4 1 3 2
�𰸣�
12345*/
