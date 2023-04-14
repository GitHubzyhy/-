#include<bits/stdc++.h>
/*1��ѡ����С������
  2��ɾ����С������
����n��Ҷ�ӽ��Ĺ�����������n+n-1=2n-1�����
                              �������->�µĽ��*/
using namespace std;

typedef char** HuffmanCode;
typedef struct
{
	char ch;//��������ַ��� 
	int weight;//Ȩֵ
	int parent,lchild,rchild;//����˫�ף����ӣ��Һ��ӵ��±� 
}HTNode,*HuffmanTree;

void CreateHuffmanTree(HuffmanTree &HT,int n)
{/*�����������HT �����0��λ�ò��ã���������Ĵ�СΪ2n
ǰ1~n��λ��ΪҶ�ӽ�㣬��n-1�����洢�����Ҷ�ӽ�� */
	void Select(HuffmanTree,int,int *,int *);
	
	if(n<=1)return;//��Ҷ�ӽ��=1��ʱ��ֱ���˳��˺��� 
	int m=n+n-1;//����һ����Ҫ��ô��Ŀռ�
	HT=new(nothrow) HTNode[m+1];//0��λ�ò���
	if(!HT){cerr<<"�����ڴ����\n";}
	
	//��ʼ�� 
	for(int i=1;i<=m;i++)
	HT[i].parent=HT[i].lchild=HT[i].rchild=0;
	cout<<"����������ַ���Ȩֵ �ÿո����\n";
	
	for(int i=1;i<=n;i++)
	cin>>HT[i].ch>>HT[i].weight;//����Ȩֵ
	
	/*���濪ʼ�����������*/
	for(int i=n+1;i<=m;i++)
	{//ͨ��n-1�ε�ѡ��ɾ�����ϲ��������������� 
		int s1,s2;//��ʾ����Ȩֵ��С��Ҷ�ӽ����HT�е���� 
		Select(HT,i-1,&s1,&s2);//i-1����һ����n��Ҷ�ӽ�㣬�ڶ�����n+1���������Ȩֵ��С�� 
	
		HT[s1].parent=HT[s2].parent=i;//�ø���Ϊi
		HT[i].lchild=s1,HT[i].rchild=s2;//s1��s2�ֱ���Ϊi�����Һ���
		HT[i].weight=HT[s1].weight+HT[s2].weight;//Ȩֵ�������Һ���Ȩֵ֮�� 
	} 

}
void Select(HuffmanTree HT,int n,int* s1,int* s2)//���s1��Ȩֵ��С�ı��s2��Ȩֵ�ڶ�С�ı�� 
{
	int min1=99999,min2=99999;
	*s1=*s2=0;
	for(int i=1;i<=n;i++)
	{
		if(HT[i].parent==0)//�ҵ���Ҷ�ӽ�� 
		{
			if(HT[i].weight<min1)
			{
				min2=min1;//ͨ�����������min2����min1���Ҷ���Ŀǰ ��С��
				*s2=*s1; //��ͬ�ĵ��� 
				min1=HT[i].weight;
				*s1=i;
			}
			else if(HT[i].weight<min2)
			{
				min2=HT[i].weight;
				*s2=i;
			}
			
		}
	}	
}

//��̬���������HC 0��λ�ò��ã�����HC�Ĵ�СΪn+1 
void CreateHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n)
{
/*start������¼������cd�д�ŵ�λ�ã���ʼ��ָ����󣬼����������λ��n-1 
 �������������Ǵ�Ҷ�ӽ����������ϻ��ݵ����ڵ㣬���Ե�һ���������
 cd[n-2]��*/	
	int start,c,f;//c:���ϻ��������������±꣬f���ڼ�¼i��˫�׽����±�
	HC=new(nothrow) char*[n+1];if(!HC){cerr<<"�����ڴ����\n";}
	char *cd=new(nothrow) char[n];//�ַ�����һ��С��n
	cd[n-1]='\0';//�ű�������� 
	
	for(int i=1;i<=n;i++)
	{
		start=n-1;//start��ʼ��ָ������������λ��,ÿһ��ѭ���������� 
		c=i,f=HT[i].parent;//fָ��˫�׽��
		while(f!=0) //��Ҷ�ӽ�㿪ʼ���ϻ��ݣ�ֵ�����ڵ�
		{
			--start;
			if(HT[f].lchild==c)cd[start]='0';//��0��1
			else  cd[start]='1';
			c=f;f=HT[f].parent;//�������ϻ��� 
		} 
		HC[i]=new(nothrow) char[n-start];//Ϊ�ַ��������ռ�0��λ�ò�ʹ�� 
		strcpy(HC[i],&cd[start]);//������ı��� ����ʱ�ռ临�Ƶ�HC�ĵ�ǰ���� 
	} 
	
	delete[] cd;
	cd=nullptr;
}

int main()
{	
	HuffmanTree HT;
	HuffmanCode HC;
	int n;cout<<"���������ж��ٸ�Ԫ��"<<endl;cin>>n;
	
	CreateHuffmanTree(HT,n);
	CreateHuffmanCode(HT,HC,n);	
	
	//HC��1��ʼ�洢��HC[i]��0��ʼ�洢���������� 
	for(int i=1;i<=n;i++)
	{
		cout<<HT[i].ch<<": ";
		for(int j=0;j<=int(strlen(HC[i]));j++)
		cout<<HC[i][j];
		cout.put('\n');
	}	
	
	return 0;
}
