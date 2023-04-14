#include<iostream>

#define MAXSIZE 100//�궨���������Ϊ100 

using namespace std;

//˳���
typedef struct 
{
	int *elem;
	int length;	
}SqList;

void InitList(SqList &L)
{
	L.elem=new int[MAXSIZE];//�����ڴ�ռ�
	if(!L.elem)abort();
	L.length=0;//���ȳ�ʼ��Ϊ0 
}

//ȡֵ���� 
bool GetElem(SqList L,int i,int &e)//i���ĸ�λ����ȡֵ��e��ȡ����ֵ���� 
{
	if(i<1||i>L.length)return false;
	e=L.elem[i-1];//i�Ǵ�1��2��3��4....������0,1,2,3 
	return true;
}

//���Ҳ���
int LocateElem(SqList L,int e)//��˳����в���Ԫ��e�ҵ��򷵻����i+1
{
	for(int i=0;i<L.length;i++)
	if(L.elem[i]==e)return i+1;//i�Ǵ�1��2��3��4....������0,1,2,3 
	return 0;//û���ҵ�����0 
} 

//�������
bool ListInsert(SqList &L,int i,int e)//��iλ�ò���e
{
	//�ж�����������1:�����λ���Ƿ����2: ˳����Ƿ�����
	if(i<1||i>L.length+1){cout<<"�����λ�ò�����"<<endl;return false;}
	if(L.length==MAXSIZE){cout<<"˳����Ѿ�����"<<endl;return false;}
	
	for(int j=L.length-1;j>=i-1;j--)//i-1��Ϊ��i�Ǵ�1��ʼ 
	L.elem[j+1]=L.elem[j];//�ƶ�
	
	L.elem[i-1]=e;
	++L.length;//����++
	
	return true; 
}

//ɾ������ 
bool ListDelete(SqList &L,int i)
{
	if(i<1||i>L.length){cout<<"ɾ����λ�ò�����"<<endl;return false;}
	
	for(int j=i;j<=L.length-1;j++)
	L.elem[j-1]=L.elem[j];//�ƶ�
	
	--L.length;
	
	return true; 
}

void display(SqList L) 
{
	for(int i=0;i<=L.length-1;i++)
	cout<<L.elem[i]<<" ";
	cout<<endl;
}

int main()
{
	SqList L;
	
	InitList(L);
	for(int i=1;i<=99;i++)
		ListInsert(L,i,i);//�ڵ�i��λ���ϲ���i 
	
	display(L);
	
	int e=0;
	if(!GetElem(L,99,e)){cout<<"ȡֵʧ��\n";}
		cout<<"99��λ��ȡֵΪ��"<<e<<endl;
	
	if(!ListDelete(L,99)){cout<<"ɾ��ʧ��\n";}
		display(L);
	
	return 0;
}
