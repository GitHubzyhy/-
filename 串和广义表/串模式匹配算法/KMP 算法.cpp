#include<stdio.h>
#include<malloc.h>
#include<string.h>

void Get_nextval(char * T,int *nextval)//获取nextval数组的值 
{
	/*
主串指针      i=0
            	a a a b
模式串指针 j=-1  	
	*/
	int i,j;
	i=1,j=-1,nextval[0]=-1;//给第一个赋值，让一号位与主串下一位比较 
	
	while(i<(int)strlen(T))//没有达到字符串末尾 
	{
	if(j==-1||T[i-1]==T[j])//匹配成功继续匹配 ,不减一数组会越界 
	{
		++j; 
		if(T[i]!=T[j])nextval[i]=j;//如果不同则=模式串位置 ,j以及+1，并且i在j+1的前面 
		else nextval[i]=nextval[j];//如果相同则拿下j的nextval值 例如aaaab的情况 
		++i;//指针移动 
	}	
	else j=nextval[j];//匹配失败！模式串指针回溯 【找门牌】 
	}
		
}

int Index_KMP(char *S,char *T,int pos)
{
	//利用模式串T的next函数求T在主串S中第pos个字符之后的位置
	int i=pos-1,j=0;
	int *nextval=(int *)malloc(sizeof(int)*(int)strlen(T));if(!nextval){printf("分配内存错误！\n");exit(0);}
	Get_nextval(T,nextval);//获取nextval的值 
	printf("模式串：");puts(T);
	//输出nextval数组 
	
	for(int i=0;i<(int)strlen(T);i++)
	printf("%d",nextval[i]);
	while(i<(int)strlen(S)&&j<(int)strlen(T)) //都没有达到串的末尾 
	{
		/*如果j==-1表示模式串第一个位置便于主串不相等，或者主串元素和模式串的元素相等
		指针分别向后移动*/
		if(j==-1||S[i]==T[j]){++i,++j;}
		else j=nextval[j];//否则模式串指针j回溯到next数组中的模式串位置 
	}  
	
	if(j>=(int)strlen(T)) return i-j+1;//最后输出结果是从1，2，3，4开始的 
	else return 0;//没有找到 
}

int main()
{
	char S[100]={0},T[100]={0};
	printf("请你输入主串\n");
	gets(S);
	
	printf("请你输入匹配的模式串\n");
	gets(T);
	
	int pos=Index_KMP(S,T,1);
	printf("从%d个位置与主串匹配\n",pos);

	return 0;
}
