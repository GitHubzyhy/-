#include<iostream>
#include<fstream>
#include<cstring>
#include<time.h>
#include<malloc.h>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

int Index_Bf(std::string S,std::string T,int pos)//BF算法 
{
	int i,j;//i主串指针，j模式串指针 
	i=pos-1;//从0开始
	j=0;
	
	while(i<(int)S.length()&&j<(int)T.length())
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
	
	 if(j>=(int)T.length())
	 return i-T.length()+1;//返回的时候加一因为显示的时候不是从0开始的 
	 else
	 return 0;
	 
}

void Get_Nextval(std::string T,int *nextval)
{
	int i,j;
	i=1,j=-1,nextval[0]=-1;
	
	while(i<(int)T.length())
	{
		if(j==-1||T[i-1]==T[j])
		{
			j++;//继续匹配
			if(T[i]!=T[j])nextval[i]=j ;
			else nextval[i]=nextval[j];
			i++;  
		}
		else
		j=nextval[j];
	}
	
}

int Index_KMP(std::string S,std::string T,int pos)
{
	int i=pos-1,j=0;
	int *nextval=(int *)malloc(sizeof(int)*T.length());if(!nextval){std::cerr<<"分配内存失败！"<<std::endl;abort();}
	Get_Nextval(T,nextval);
	
	while(i<(int)S.length()&&j<(int)T.length())
	{
		if(j==-1||S[i]==T[j])
		{
			i++,j++;
		} 
		else
		j=nextval[j];
	}
	
	delete[] nextval;
	nextval=nullptr; 
	
	if(j>=(int)T.length())
	return i-j+1;
	else
	return 0;
}
int Get_time()
{
	time_t timep;
	time(&timep);
	struct tm *p;
	p=gmtime(&timep);
	return p->tm_sec;
}

int main()
{
	int fist_time=clock(),last_time;
	/*因为病毒DNA是螺旋的，为了线性取到每个可行的长度为m的模式串，将病毒DNA扩大为2m
	然后循环m次，依次取得每个长度为m的环状字符串*/
	
	std::ifstream inFile("病毒感染检测输入数据.txt");if(!inFile){cerr<<"文件打开失败！！"<<endl;abort();}
	std::ofstream outFile("病毒感染检测输出结果.txt",std::ios::out);
	
	int num;//获取有多少组数据，文件第一行就是
	inFile>>num;
	
	std::string Virus_DNA,Person_DNA,start_Virus_DNA,temp;
	bool flag=0;
	while(num--)
	{
		inFile>>Virus_DNA>>Person_DNA;//依次读取病毒的DNA和人的DNA 
		start_Virus_DNA=Virus_DNA;//保存给最后备用 
		
		//cout<<Virus_DNA<<"\t"<<Person_DNA<<endl;//最原始的数据 
		int m=Virus_DNA.length();//病毒DNA的长度 
		Virus_DNA+=Virus_DNA;///连续存储两次
		cout<<Virus_DNA<<"\t"<<Person_DNA<<endl;//扩大存储后的 
		
		for(int i=0;i<m;i++)//依次取得每个长度为m的病毒DNA环状字符串temp 
		{
			temp=std::string();//让temp重新初始化 
			for(int j=1;j<=m;j++)
			{
				//	cout<<*(Virus_DNA.begin()+(i+j))<<"|";
					temp.push_back(*(Virus_DNA.begin()+(i+j)));
			}
			cout<<temp<<"\t"<<Person_DNA<<endl;
		
	 			//	 flag=Index_Bf(Person_DNA,temp,1);   
			flag=Index_KMP(Person_DNA,temp,1);
			if(flag)break;//匹配成功就退出循环 
			cout<<endl;
				
		}
			if(flag) outFile<<	start_Virus_DNA<<"\t"<<Person_DNA<<" "<<"YES"<<endl;
			else	 outFile<<	start_Virus_DNA<<"\t"<<Person_DNA<<" "<<"NO"<<endl;
				cout<<endl;
	}
	
	inFile.close(),outFile.close();
	
	last_time=clock();
	cout<<"一共花费了"<<(double)(last_time-fist_time)/CLOCKS_PER_SEC<<"毫秒"<<std::endl;
	
	return 0;
}
