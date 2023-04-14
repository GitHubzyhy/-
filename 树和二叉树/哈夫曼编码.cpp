#include<bits/stdc++.h>
/*1：选用两小造新树
  2：删除两小添新人
包含n个叶子结点的哈夫曼树共有n+n-1=2n-1个结点
                              两两组合->新的结点*/
using namespace std;

typedef char** HuffmanCode;
typedef struct
{
	char ch;//结点代表的字符集 
	int weight;//权值
	int parent,lchild,rchild;//结点的双亲，左孩子，右孩子的下标 
}HTNode,*HuffmanTree;

void CreateHuffmanTree(HuffmanTree &HT,int n)
{/*构造哈夫曼树HT 数组的0号位置不用，所以数组的大小为2n
前1~n个位置为叶子结点，后n-1个结点存储其余非叶子结点 */
	void Select(HuffmanTree,int,int *,int *);
	
	if(n<=1)return;//当叶子结点=1的时候直接退出此函数 
	int m=n+n-1;//数组一共需要这么多的空间
	HT=new(nothrow) HTNode[m+1];//0号位置不用
	if(!HT){cerr<<"分配内存错误！\n";}
	
	//初始化 
	for(int i=1;i<=m;i++)
	HT[i].parent=HT[i].lchild=HT[i].rchild=0;
	cout<<"请输入结点的字符和权值 用空格隔开\n";
	
	for(int i=1;i<=n;i++)
	cin>>HT[i].ch>>HT[i].weight;//输入权值
	
	/*下面开始构造哈夫曼树*/
	for(int i=n+1;i<=m;i++)
	{//通过n-1次的选择，删除，合并来创建哈夫曼树 
		int s1,s2;//表示两个权值最小的叶子结点在HT中的序号 
		Select(HT,i-1,&s1,&s2);//i-1：第一次有n个叶子结点，第二次有n+1个结点中找权值最小的 
	
		HT[s1].parent=HT[s2].parent=i;//让父亲为i
		HT[i].lchild=s1,HT[i].rchild=s2;//s1和s2分别作为i的左右孩子
		HT[i].weight=HT[s1].weight+HT[s2].weight;//权值等于左右孩子权值之和 
	} 

}
void Select(HuffmanTree HT,int n,int* s1,int* s2)//最后s1是权值最小的编号s2是权值第二小的编号 
{
	int min1=99999,min2=99999;
	*s1=*s2=0;
	for(int i=1;i<=n;i++)
	{
		if(HT[i].parent==0)//找的是叶子结点 
		{
			if(HT[i].weight<min1)
			{
				min2=min1;//通过这个步骤让min2大于min1并且都是目前 最小的
				*s2=*s1; //相同的道理 
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

//动态分配的数组HC 0号位置不用，所以HC的大小为n+1 
void CreateHuffmanCode(HuffmanTree HT,HuffmanCode &HC,int n)
{
/*start用来记录编码在cd中存放的位置，初始化指向最后，即编码结束的位置n-1 
 求解哈夫曼编码是从叶子结点出发，向上回溯到根节点，所以第一个编码放在
 cd[n-2]中*/	
	int start,c,f;//c:向上回溯所经历结点的下标，f用于记录i的双亲结点的下标
	HC=new(nothrow) char*[n+1];if(!HC){cerr<<"分配内存错误！\n";}
	char *cd=new(nothrow) char[n];//字符编码一定小于n
	cd[n-1]='\0';//放编码结束符 
	
	for(int i=1;i<=n;i++)
	{
		start=n-1;//start初始化指向编码结束符的位置,每一次循环都是这样 
		c=i,f=HT[i].parent;//f指向双亲结点
		while(f!=0) //从叶子结点开始向上回溯，值到根节点
		{
			--start;
			if(HT[f].lchild==c)cd[start]='0';//左0右1
			else  cd[start]='1';
			c=f;f=HT[f].parent;//继续向上回溯 
		} 
		HC[i]=new(nothrow) char[n-start];//为字符编码分配空间0号位置不使用 
		strcpy(HC[i],&cd[start]);//将所求的编码 从临时空间复制到HC的当前行中 
	} 
	
	delete[] cd;
	cd=nullptr;
}

int main()
{	
	HuffmanTree HT;
	HuffmanCode HC;
	int n;cout<<"请您输入有多少个元素"<<endl;cin>>n;
	
	CreateHuffmanTree(HT,n);
	CreateHuffmanCode(HT,HC,n);	
	
	//HC从1开始存储，HC[i]从0开始存储哈夫曼编码 
	for(int i=1;i<=n;i++)
	{
		cout<<HT[i].ch<<": ";
		for(int j=0;j<=int(strlen(HC[i]));j++)
		cout<<HC[i][j];
		cout.put('\n');
	}	
	
	return 0;
}
