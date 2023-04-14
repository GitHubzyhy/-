#include<iostream>
#include<stack>
#include<direct.h>

#define MvNum 100//最大顶点数

using namespace std;

typedef char VerTexType;//顶点的数据类型
typedef struct ArcNode//边结点
{
	int adjvex;
	struct ArcNode *nextarc;
	int info;
}ArcNode;

typedef struct Vnode//顶点信息
{
	VerTexType data;
	ArcNode *firstarc;//指向第一条依附该结点的边结点指针 
}Vnode,AdjList[MvNum];

typedef struct//边结点 
{
	AdjList vertices;//Vnode结点构成的数组 
	int vexnum,arcnum;
}ALGraph;

int LocateVex(ALGraph G,VerTexType v)//查找结点在顶点表的位置 
{
	for(int i=0;i<G.vexnum;i++)
	{
	 	if(G.vertices[i].data==v)
	 	return i;
	}
	 return -1;//没有找到 
}

void CreateAov(ALGraph &G)//是一个有向图 
{
	VerTexType v1,v2;
	ArcNode *p1;
	
	cout<<"输入总顶点数，总边数: ";
	cin>>G.vexnum>>G.arcnum; 
	
	cout<<"输入顶点的值\n";
	for(int i=0;i<G.vexnum;i++)
	{
		cin>>G.vertices[i].data;//输入顶点值
		G.vertices[i].firstarc=nullptr; 
	}
	
	for(int k=0;k<G.arcnum;k++)
	{
		cout<<"\n请你上输入(顶点  顶点 ): ";
		cin>>v1>>v2;
		int i=LocateVex(G,v1),j=LocateVex(G,v2);//返回在顶点表中的坐标
		
		p1=new(nothrow) ArcNode;if(!p1){cerr<<"分配内存失败！\n";abort();}
		p1->adjvex=j;
		p1->nextarc=G.vertices[i].firstarc;G.vertices[i].firstarc=p1;
	}
}

void ShowGraph(ALGraph G)
{
	int i,j;
	ArcNode *p;//边结点指针
	
	for(i=0;i<G.vexnum;i++)
	{
		cout<<i<<" ["<<G.vertices[i].data<<"|--]-> ";//输出顶点信息
		for(p=G.vertices[i].firstarc;p;p=p->nextarc)//依次输出边的信息
		cout<<"["<<p->adjvex<<"|--]-> ";
		cout.put('\n'); 
	} 
} 
void FindInDegree(ALGraph G,int indegree[])
{//初始化数组，数组默认为0
	memset(indegree,0,G.vexnum*sizeof(int));
//遍历邻接表，根据各个链表中的结点的数据域存储的各顶点位置下标，在indegree数组相应位置+1
	for(int i=0;i<G.vexnum;i++)
	for(ArcNode *p=G.vertices[i].firstarc;p;p=p->nextarc)
	indegree[p->adjvex]++;//入度++ 
}

bool TopologicalSort(ALGraph G,int *topo)	//topo:记录top序列的顶点序号
{
	//存放各项顶底的入度
	int *indegree=new(nothrow) int[G.vexnum];if(!indegree){cerr<<"分配内存失败！\n";abort();}
	//暂存放所有入度为0的顶点,可以避免重复扫描数组indegree检测入度为0的顶点，提高算法的效率 
	stack<int> S; 
 
	FindInDegree(G,indegree);
	
	for(int i=0;i<G.vexnum;i++)
	if(!indegree[i])//入度为0，进栈
	S.push(i);
	
	int m=0;//对输出顶点计数
	while(!S.empty()) 
	{
		int i=S.top();S.pop();//度为0的结点都在栈里面 
		
		topo[m++]=i;//存入拓扑序列，存入的是顶点下标 
		for(ArcNode  *p=G.vertices[i].firstarc;p;p=p->nextarc)//遍历整个邻接表 
		{
			int k=p->adjvex;//vk为vi的邻接点
			--indegree[k];// 删除所有以它为尾的弧
			if(!indegree[k])//入读为0 入栈 
			S.push(k);
		}	
	}
	
	void Show_topo(int *);
	
	if(m<G.vexnum) {cout<<"该 有 向 图 有 回 路，因 为 有 结 点 找 不 到 前 驱 所 以 度 不 为  0，入 不 了 栈 !\n"; return 0;}
	else { cout<<"该 有 向 图 无 回 路！ \n";return 1;}
}
void Show_topo(ALGraph G,int *topo)//拓扑序列存入的是下标 
{
	cout<<"拓扑序列: ";
	for(int i=0;i<G.vexnum;i++)
	cout<<G.vertices[topo[i]].data<<" ";
	cout.put('\n');
}

int main()
{
	ALGraph G;
	CreateAov(G);
	ShowGraph(G);
	
	//存储的结点编号 
	int *topo=new(nothrow) int[G.vexnum];if(!topo){cerr<<"分配内存失败！\n";abort();}
	TopologicalSort(G,topo);
	Show_topo(G,topo);
	
	return 0;
}
/*
6 8
123456
1 2
1 3
1 4
4 5
6 4
6 5
3 5
3 2
*/
