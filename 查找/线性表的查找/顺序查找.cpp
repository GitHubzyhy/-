#include<iostream>

using namespace std;

typedef int ElemType;

typedef struct
{
	ElemType *R;
	int length;
}SSTable;

int Search_Seq1(SSTable ST,ElemType key)//˳����� 
{//�ҵ��򷵻�Ԫ���ڱ��е�λ�ã�����Ϊ0 
	for(int i=ST.length;i>1;--i)//0��λ�ò��� 
	if(ST.R[i]==key) return i;
	
	return 0;
}//�Ƚ������Σ��Ƿ��ҵ����Ƿ�Խ�� 

int Search_Seq2(SSTable ST,ElemType key)//���ü����ڵ�˳�����
{
	int i;
	ST.R[0]=key;//������
	for(i=ST.length;ST.R[i]!=key;--i);//�ֺ�
	return i; 
}
 
int main()
{
	SSTable ST;
	cout<<"������������ĳ���length\n";
	cin>>ST.length;
	ST.R=new(nothrow) ElemType[ST.length+1];//0��λ�ò��� 
	
	cout<<"�������������ڵ�Ԫ��\n";
	for(int i=1;i<=ST.length;i++)
	cin>>ST.R[i];
	
	int pos=Search_Seq1(ST,5);
	if(pos)
	cout<<"λ���ڣ�"<<pos;
	else
	cout<<"û�ҵ�";
	
	pos=Search_Seq2(ST,5);
	if(pos)
	cout<<"\nλ���ڣ�"<<pos;
	else
	cout<<"\nû�ҵ�";
	
	return 0;
}
