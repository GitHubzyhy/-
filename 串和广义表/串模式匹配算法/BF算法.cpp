#include<iostream>
#include<cstring>

using namespace std;

int Index_Bf(char *S,char *T,int pos)
{
	int S_Length=strlen(S),T_Length=strlen(T),i,j;//i����ָ�룬jģʽ��ָ�� 
	i=pos-1;//��0��ʼ
	j=0;
		/*
		һ��������ƥ��ģʽ��ָ����ݵ�0��
		����ָ����ݵ�i-��j-1��=�ߵ�·��+1(����ָ����һ��λ�ý�������ƥ��) 
		����Ϊ�����Ǵ�0��ʼ�洢���Ի�Ҫ-1   �ܣ�i=j-(j-1)+1-1 
		0123
		#### ����0��λ�÷�����ƥ�� 0-(0-1)->·��+1=2{����λ����1���ִ��󣡣�} 
		##	 ����Ǵ�1��ʼ���ǣ�1-(1-1)->·��+1=2{���������λ����ȷ�����ɹ���j=0;} 
		01 
		*/
	while(i<S_Length&&j<T_Length)
	{
		if(S[i]==T[j])
		{
			i++;j++;
		}
		else 
		{
			i=i-j+2-1;
			j=0;
		}
	}
	
	 if(j>=T_Length)
	 return i-T_Length+1;//���ص�ʱ���һ��Ϊ��ʾ��ʱ���Ǵ�0��ʼ�� 
	 else
	 return 0;
}

int main()
{
	char s[20],t[20];//������ģʽ��
	cout<<"��������������ֵ"<<endl;
	cin>>s;
	
	cout<<"��������ģʽ����ֵ"<<endl;
	cin>>t;
	
	cout<<"��������Ҫ����ƥ���λ��"<<endl;
	int pos=0;
	cin>>pos;
	pos=Index_Bf(s,t,pos);
	
	if(pos)
	cout<<"ģʽ����"<<pos<<"λ��ƥ��ɹ�"<<endl;
	else
	cout<<"û���ҵ�"<<endl;
	
	return 0;
}
