#include<stdio.h>
#include<malloc.h>
#include<string.h>

void Get_nextval(char * T,int *nextval)//��ȡnextval�����ֵ 
{
	/*
����ָ��      i=0
            	a a a b
ģʽ��ָ�� j=-1  	
	*/
	int i,j;
	i=1,j=-1,nextval[0]=-1;//����һ����ֵ����һ��λ��������һλ�Ƚ� 
	
	while(i<(int)strlen(T))//û�дﵽ�ַ���ĩβ 
	{
	if(j==-1||T[i-1]==T[j])//ƥ��ɹ�����ƥ�� ,����һ�����Խ�� 
	{
		++j; 
		if(T[i]!=T[j])nextval[i]=j;//�����ͬ��=ģʽ��λ�� ,j�Լ�+1������i��j+1��ǰ�� 
		else nextval[i]=nextval[j];//�����ͬ������j��nextvalֵ ����aaaab����� 
		++i;//ָ���ƶ� 
	}	
	else j=nextval[j];//ƥ��ʧ�ܣ�ģʽ��ָ����� �������ơ� 
	}
		
}

int Index_KMP(char *S,char *T,int pos)
{
	//����ģʽ��T��next������T������S�е�pos���ַ�֮���λ��
	int i=pos-1,j=0;
	int *nextval=(int *)malloc(sizeof(int)*(int)strlen(T));if(!nextval){printf("�����ڴ����\n");exit(0);}
	Get_nextval(T,nextval);//��ȡnextval��ֵ 
	printf("ģʽ����");puts(T);
	//���nextval���� 
	
	for(int i=0;i<(int)strlen(T);i++)
	printf("%d",nextval[i]);
	while(i<(int)strlen(S)&&j<(int)strlen(T)) //��û�дﵽ����ĩβ 
	{
		/*���j==-1��ʾģʽ����һ��λ�ñ�����������ȣ���������Ԫ�غ�ģʽ����Ԫ�����
		ָ��ֱ�����ƶ�*/
		if(j==-1||S[i]==T[j]){++i,++j;}
		else j=nextval[j];//����ģʽ��ָ��j���ݵ�next�����е�ģʽ��λ�� 
	}  
	
	if(j>=(int)strlen(T)) return i-j+1;//����������Ǵ�1��2��3��4��ʼ�� 
	else return 0;//û���ҵ� 
}

int main()
{
	char S[100]={0},T[100]={0};
	printf("������������\n");
	gets(S);
	
	printf("��������ƥ���ģʽ��\n");
	gets(T);
	
	int pos=Index_KMP(S,T,1);
	printf("��%d��λ��������ƥ��\n",pos);

	return 0;
}
