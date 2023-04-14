#include<iostream>
#include<cstring>

using namespace std;

int Index_Bf(char *S,char *T,int pos)
{
	int S_Length=strlen(S),T_Length=strlen(T),i,j;//i主串指针，j模式串指针 
	i=pos-1;//从0开始
	j=0;
		/*
		一旦发生不匹配模式串指针回溯到0，
		主串指针回溯到i-（j-1）=走的路程+1(主串指针下一个位置进行重新匹配) 
		又因为数组是从0开始存储所以还要-1   总：i=j-(j-1)+1-1 
		0123
		#### 当第0个位置发生不匹配 0-(0-1)->路程+1=2{理想位置是1出现错误！！} 
		##	 如果是从1开始标标记，1-(1-1)->路程+1=2{这里的理想位置正确！！成功！j=0;} 
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
	 return i-T_Length+1;//返回的时候加一因为显示的时候不是从0开始的 
	 else
	 return 0;
}

int main()
{
	char s[20],t[20];//主串和模式串
	cout<<"请你输入主串的值"<<endl;
	cin>>s;
	
	cout<<"请你输入模式串的值"<<endl;
	cin>>t;
	
	cout<<"请你输入要进行匹配的位置"<<endl;
	int pos=0;
	cin>>pos;
	pos=Index_Bf(s,t,pos);
	
	if(pos)
	cout<<"模式串从"<<pos<<"位置匹配成功"<<endl;
	else
	cout<<"没有找到"<<endl;
	
	return 0;
}
