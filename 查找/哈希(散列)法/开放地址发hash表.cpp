#include<iostream>
#include<cmath>
#define m 16//表长为20 

using namespace std;
/*------开放地址法的存储表示--------*/

typedef struct
{
	int key;//唯一不重复 
	int data;//数据域 
}HashTable[m];

int Find_primenumber()//找到 
{
	int i,j; 
	bool flag;
	
	for(i=m;i>=2;--i)
	{
		flag=1;	
		for(j=2;j<=sqrt(i);++j)
		{
			if(i%j==0)//一旦可以整除
			 {
			 	flag=0;
			 	break;
			 }
		}
		
		if(flag)//2~sqrt(i)都没有整除的证明这个数字是质数 
		break;
	}
	return i;
}

int H(int key)//散列函数 
{
	int p=Find_primenumber();//p<=m
	if(p==1) p=m;//没有找到质数的情况 
	return abs(key)%p;
}

void insert(HashTable &HT,int key)
{
	int H0=H(key);//通过散列函数求出散列地址
	
	if(HT[H0].key==0) HT[H0].key=key;//若单元为空则放到此单元内
	else if(HT[H0].key==key)return;//不能放重复的 
	else
	{
		for(int di=1;di<m;di++)//线性探测法 
		{
			int Hi=abs(H0+di)%m;
			if(HT[Hi].key==0){ HT[Hi].key=key;break;}//否则继续一个个探测找到空位置 
			else if(HT[Hi].key==key)return;
		}
	}
}

//构造哈希表 
void CreateHashTable(HashTable &HT)
{
	int key,i=0;
	while(i<12&&cin>>key)//关键字的长度为12 
	{
		insert(HT,key);
		++i;
	}	
	
}

//三种情况1.查找位置为空无元素，没找到，2.找到了！3.纯粹没找到 
int  SearchHash(HashTable HT,int key)
{
	int H0=H(key);//计算散列地址
	if(HT[H0].key==0) return  -1;//查找的元素不存在
	else if(HT[H0].key==key) return H0;//找到了！！ 
	else
	{
		for(int di=1;di<m;di++)
		{
			int Hi=abs(H0+di)%m;//线性探测法
			if(HT[Hi].key==0) return -1;//查找失败
			else if(HT[Hi].key==key) return Hi;//找到了！ 
		}
		return -1;//最后还是没有找到 
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
	cout<<"请你输入要查找的关键字key: ";cin>>key;
	key=SearchHash(HT,key);
	
	switch (key) 
	{
		case -1:
			cout<<"没找到\n";
			break;
		default:
			cout<<"关键字的位置在哈希表的："<<key<<'\n';
			break;
	} 
	
	return 0;
}

/*测试数据：19 14 23 1 68 20 84 27 55 11 10 79

结果：0  14   1  68  27  55  19  20  84  79  23  11  10   0   0   0*/
