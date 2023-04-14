#include<iostream>
#include<stack>
#include<direct.h>

#define MvNum 100//最大顶点数

using namespace std;

typedef char VerTexType;
typedef int ArcType;//权值的数据类型 
typedef struct ArcNode//边结点 
{
	int adjvex;
	struct ArcNode *nextarc;//下一条边
	ArcType info;//权值 
}ArcNode;

typedef struct Vnode//顶点信息
{
	VerTexType data;//存储结点数据域
	ArcNode *firstarc; //指向第一条依附该结点的边结点指针
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

void CreateAoe(ALGraph &G)//是一个有向图 
{
	VerTexType v1,v2;//结点 
	ArcType w;//权值 
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
		cout<<"\n请你上输入(顶点  顶点 权值 ): ";
		cin>>v1>>v2>>w;
		int i=LocateVex(G,v1),j=LocateVex(G,v2);//返回在顶点表中的坐标
		
		p1=new(nothrow) ArcNode;if(!p1){cerr<<"分配内存失败！\n";abort();}
		p1->adjvex=j;
		p1->info=w;
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
{	//存放各项顶底的入度
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
		
		for(ArcNode *p=G.vertices[i].firstarc;p;p=p->nextarc)//遍历整个邻接表 
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

void CriticalPath(ALGraph G,int *topo)
{//G为邻接表存储的有向图吗，输出G的各项关键活动：l(i)=e(i)
	if(!TopologicalSort(G,topo)) return;//存在有向环
	int k,j,e,l;
	
	//事件vi的最早发生时间 
	int *ve=new(nothrow) int[G.vexnum];if(!ve){cerr<<"分配内存失败！\n";abort();}
	
	//事件vi的最晚发生时间
	int *vl=new(nothrow) int[G.vexnum];if(!vl) {cerr<<"分配内存失败！\n";abort();}
	
	memset(ve,0,G.vexnum*sizeof(int));//初始化全部为0[int类型只能初始化为-1或者0] 
	/*-----------------------------按照拓扑次序求得每个事件的最早发生时间--------------------------------*/
	for(int i=0;i<G.vexnum;i++)
	{
		k=topo[i];//获得拓扑序列中的顶点序号k
		for(ArcNode *p=G.vertices[k].firstarc;p;p=p->nextarc)//遍历邻接的边
		{
			j=p->adjvex;//j为邻接顶点的序号 
			if(ve[j]<ve[k]+p->info)//找max k->j
			ve[j]=ve[k]+p->info;
		}  
	} 
	
	for(int i=0;i<G.vexnum;i++)//给每一个事件的最晚发生时间赋初值 
	vl[i]=ve[G.vexnum-1];//ve[n-1]=vl[n-1] 


/*-------------------------------按照逆拓扑次序求每个事件的最迟发生时间--------------------------------*/
	for(int i=G.vexnum-2;i>=0;i--)//直接从拓扑记录倒数第二个进行 
	{
		k=topo[i];
		for(ArcNode *p=G.vertices[k].firstarc;p;p=p->nextarc)
		{
			j=p->adjvex;//j为邻接顶点的序号 
			if(vl[k]>vl[j]-p->info)//找min k->j
			vl[k]=vl[j]-p->info;
		}
	}
/*-------------------------------判断每一活动是否为关键路径--------------------------------------------*/
	for(int i=0;i<G.vexnum;i++)
	{
		for(ArcNode *p=G.vertices[i].firstarc;p;p=p->nextarc)
		{
			j=p->adjvex;
			e=ve[i];// //计算活动<vi,vj>的最早开始时间 
			l=vl[j]-p->info;//计算活动<vi,vj>的最迟开始时间 
			
			if(e==l)//为关键活动
			cout<<"<"<<G.vertices[i].data<<","<<G.vertices[j].data<<">,";
		}
	}

}

int main()
{
	ALGraph G;
	CreateAoe(G);
	ShowGraph(G);
	
	//存储的结点编号 
	int *topo=new(nothrow) int[G.vexnum];if(!topo){cerr<<"分配内存失败！\n";abort();}
	TopologicalSort(G,topo);
	Show_topo(G,topo);
	CriticalPath(G,topo);
}
/*测试数据
9 11
012345678
0 1 6
0 2 4
0 3 5
1 4 1
2 4 1
3 5 2
4 6 9
4 7 7
5 7 4
6 8 2
7 8 4
 

*/
