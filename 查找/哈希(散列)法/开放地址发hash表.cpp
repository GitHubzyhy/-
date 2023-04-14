#include<iostream>
#include<cmath>
#define m 16//��Ϊ20 

using namespace std;
/*------���ŵ�ַ���Ĵ洢��ʾ--------*/

typedef struct
{
	int key;//Ψһ���ظ� 
	int data;//������ 
}HashTable[m];

int Find_primenumber()//�ҵ� 
{
	int i,j; 
	bool flag;
	
	for(i=m;i>=2;--i)
	{
		flag=1;	
		for(j=2;j<=sqrt(i);++j)
		{
			if(i%j==0)//һ����������
			 {
			 	flag=0;
			 	break;
			 }
		}
		
		if(flag)//2~sqrt(i)��û��������֤��������������� 
		break;
	}
	return i;
}

int H(int key)//ɢ�к��� 
{
	int p=Find_primenumber();//p<=m
	if(p==1) p=m;//û���ҵ���������� 
	return abs(key)%p;
}

void insert(HashTable &HT,int key)
{
	int H0=H(key);//ͨ��ɢ�к������ɢ�е�ַ
	
	if(HT[H0].key==0) HT[H0].key=key;//����ԪΪ����ŵ��˵�Ԫ��
	else if(HT[H0].key==key)return;//���ܷ��ظ��� 
	else
	{
		for(int di=1;di<m;di++)//����̽�ⷨ 
		{
			int Hi=abs(H0+di)%m;
			if(HT[Hi].key==0){ HT[Hi].key=key;break;}//�������һ����̽���ҵ���λ�� 
			else if(HT[Hi].key==key)return;
		}
	}
}

//�����ϣ�� 
void CreateHashTable(HashTable &HT)
{
	int key,i=0;
	while(i<12&&cin>>key)//�ؼ��ֵĳ���Ϊ12 
	{
		insert(HT,key);
		++i;
	}	
	
}

//�������1.����λ��Ϊ����Ԫ�أ�û�ҵ���2.�ҵ��ˣ�3.����û�ҵ� 
int  SearchHash(HashTable HT,int key)
{
	int H0=H(key);//����ɢ�е�ַ
	if(HT[H0].key==0) return  -1;//���ҵ�Ԫ�ز�����
	else if(HT[H0].key==key) return H0;//�ҵ��ˣ��� 
	else
	{
		for(int di=1;di<m;di++)
		{
			int Hi=abs(H0+di)%m;//����̽�ⷨ
			if(HT[Hi].key==0) return -1;//����ʧ��
			else if(HT[Hi].key==key) return Hi;//�ҵ��ˣ� 
		}
		return -1;//�����û���ҵ� 
	} //else
}

void print(HashTable HT)
{
	cout.put('\n');
	for(int i=0;i<m;i++)
	{
		cout.width(3); 
		cout<<i<<" ";
	}
	
	cout.put('\n');
	
	for(int i=0;i<m;i++)
	{
		cout.width(3); 
		cout<<HT[i].key<<" ";
	}
	
	cout.put('\n');
} 

int main()
{
	HashTable HT;
	
	for(int i=0;i<m;i++)
	HT[i].key=0;
	
	CreateHashTable(HT);
	print(HT);
	
	int key;
	cout<<"��������Ҫ���ҵĹؼ���key: ";cin>>key;
	key=SearchHash(HT,key);
	
	switch (key) 
	{
		case -1:
			cout<<"û�ҵ�\n";
			break;
		default:
			cout<<"�ؼ��ֵ�λ���ڹ�ϣ��ģ�"<<key<<'\n';
			break;
	} 
	
	return 0;
}

/*�������ݣ�19 14 23 1 68 20 84 27 55 11 10 79

�����0  14   1  68  27  55  19  20  84  79  23  11  10   0   0   0*/
