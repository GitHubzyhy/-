#include<bits/stdc++.h>

using namespace std;

typedef int ElemType;

typedef struct//˳���Ķ��� 
{
	ElemType *R;
	int length;
}SSTable;

int Search_Bin(SSTable ST,ElemType key)
{
	//�ڵ�������� ST�����۰���ҹؼ���=key������Ԫ�أ��ҵ��򷵻��ڱ��е�λ�ã�����Ϊ0
	int low=1,high=ST.length,mid;//0��λ�ò���
	while(low<=high)//=ʱ�����仹�����һ�������Ҫ�Ƚ�
	{
		mid=(low+high)/2;//���м��λ��
		if(key==ST.R[mid]) return mid;
		else if(key<ST.R[mid]) high=mid-1;
		else low=mid+1;
	} 
	return 0;//�ҵ�ʧ�ܣ� 
}

int Search_Bin_recursion(SSTable ST,ElemType key,int low,int high,int mid)
{
	if(low>high) return 0;//û���ҵ� 
	else 
	{
		if(ST.R[mid]==key) return mid;//�ҵ��� 
		else if(ST.R[mid]<key) 
		{
			high=mid-1;
	    	return Search_Bin_recursion(ST,key,low,high,(low+high)/2); 	
		}
		else
		{
			low=mid+1;
			return Search_Bin_recursion(ST,key,low,high,(low+high)/2);
		}
	}
}

int main()
{
	SSTable ST;
	cout<<"������������ĳ���\n";
	cin>>ST.length;

	cout<<"�������������ֵ\n";
	ST.R=new(nothrow) ElemType[ST.length+1];

	for(int i=1;i<=ST.length;i++)
	cin>>ST.R[i];

	sort(ST.R+1,ST.R+ST.length+1);// 1�ؼ����������к� 2˳��洢�ṹ
	int pos=Search_Bin(ST,3) ;
	for(int i=1;i<=ST.length;i++)
	cout<<ST.R[i]<<" "; 
	
	if(pos)
		cout<<"λ�ã�"<<pos<<'\n';
	else
	    cout<<"����ʧ��\n";
 /*-----------------------------------------------------------------------------------*/
	 pos=Search_Bin_recursion(ST,3,1,ST.length,(1+ST.length)/2);
 	 if(pos)
 		 cout<<"λ�ã�"<<pos<<'\n';
 	 else
 	     cout<<"����ʧ��\n";
 	     
 	return 0;	
}
