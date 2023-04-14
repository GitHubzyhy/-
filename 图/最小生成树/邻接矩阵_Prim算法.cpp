#include<bits/stdc++.h>

#define MaxInt 32767//表示权的极大值
#define MvNum 100///最大顶点数

using namespace std;

typedef char VerTexType;
typedef int ArcType; 
typedef struct//无向网的结构 
{
	VerTexType vexs[MvNum];//顶点表
	ArcType arcs[MvNum][MvNum];//邻接矩阵
	int vexnum,arcnum;//图的顶点和弧的数量 
}AMGraph;

int LocateVex(AMGraph G,VerTexType U)//在顶点表中查找U的在顶点表中的下标序号
{
	for(int i=0;i<G.vexnum;i++)
	{
		if(G.vexs[i]==U)
		return i;
	}
	
	return -1;//没有找到！ 
} 

void CreateUDN(AMGraph &G)
{
	int i,j;//为后面查找方便 
	VerTexType v1,v2;//顶点
	ArcType w;//权值 
	cout<<"请你输入无向网中有多少个顶点 和弧\n";
	
	cin>>G.vexnum>>G.arcnum;
	cout<<"请你输入顶点\n";
	for(i=0;i<G.vexnum;i++)
	cin>>G.vexs[i];
	
	for(i=0;i<G.vexnum;i++)//给邻接矩阵赋初值 
	for(j=0;j<G.vexnum;j++)
	G.arcs[i][j]=MaxInt;
	
	cout<<"请你输入 顶点 顶点 权值\n";
	for(int k=0;k<G.arcnum;k++)
	{
		cin>>v1>>v2>>w;
		i=LocateVex(G,v1),j=LocateVex(G,v2);	if(i==-1||j==-1){std::cout<<"顶点位置未找到\n",--k;continue;}//没找到本次循环作废 
		G.arcs[i][j]=w;
		G.arcs[j][i]=w;//无向网边是对称的 
	}
}

void ShowpGraph(AMGraph G)
{
	cout<<"邻接矩阵为：\n   ";
	for(int i=0;i<G.vexnum;i++)//输出顶点表 
	cout<<G.vexs[i]<<"    ";
	cout.put('\n');
	for(int i=0;i<G.vexnum;i++)
	{
		cout<<G.vexs[i]<<"  ";
		for(int j=0;j<G.vexnum;j++)//输出邻接矩阵 
		{
			if(G.arcs[i][j]==MaxInt)//为极大值的时候输出那个符号 
			cout<<"∞  ";
			else
			cout<<G.arcs[i][j]<<"   ";
		}
		cout<<"\n\n";
	}//for
}

struct lowcost_Vode//用于记录U到V-U具有最小权值的边 结点 
{
	VerTexType adjvex;// 最小边在U的那个顶点，父结点 
	ArcType lowcost;//最小边的权值 
};

int mins=MaxInt;//最小权值 初始化让mins最大 
int MIN(AMGraph G,struct lowcost_Vode * closedge)//选择权值最小
{
	int index=0;
	
	for(int i=0;i<G.vexnum;i++)
	if(closedge[i].lowcost!=0&&closedge[i].lowcost<mins)//lowcost为0表示当前顶点放入到了U,边也放到TE 
	{
	mins=closedge[i].lowcost;
	index=i;	
	}
	return index;
} 

void print(AMGraph G,struct lowcost_Vode *closedge)//输出辅助数组里面的最小权值 
{
	 cout<<"辅助数组：";
	 for(int j=0;j<G.vexnum;j++)
	  	cout<<	closedge[j].lowcost<<" ";
		cout<<'\n';
}

void MiniSpanTree_Prim(AMGraph G,VerTexType u)
{
	//无向网G以邻接矩阵存储，从顶底u出发构造G的最小生成树T，输出T的各条边
	 int k=LocateVex(G,u);
	 VerTexType u0,v0;//边的两个顶点 
	
	 //记录U到顶点表的V-U的权值 
	 struct lowcost_Vode *closedge=new(nothrow) lowcost_Vode[G.vexnum];
	 
	 for(int j=0;j<G.vexnum;j++)//初始化closedge数组为u邻接的边的权值 
	 if(j!=k)//自身没有边 
	 {
	 	closedge[j]={u,G.arcs[k][j]};//重要！！！！！！！
	 	cout<<	closedge[j].lowcost<<" ";
	 }
	  	
	 closedge[k].lowcost=0;//初始化，U={u}
	 cout<<"\n从起点开始的最小生成树\n\n";
	 for(int i=1;i<G.vexnum;i++)//选择其余n-1个顶点,生成n-1条边，u0已经在U集合中 
	 {
	 	print(G,closedge);
	 	mins=MaxInt;//因为mins是全局变量
		  
	 	k=MIN(G,closedge);//找到最小权值边的顶点坐标  
	 	u0=closedge[k].adjvex;//u0为最小边的一个顶点，u0属于U 
	 	v0=G.vexs[k];//v0为最小边的另外一个顶点，v0属于V-U 邻接矩阵方式想象 
	 	cout<<"("<<u0<<"-->"<<v0<<")mins: "<<mins<<"\n\n";//输出当前最小边(u0,v0)
		closedge[k].lowcost=0;//第k个顶点并入U集，边也并入了TE 
		for(int j=0;j<G.vexnum;j++)
		{
			if(G.arcs[k][j]<closedge[j].lowcost)//新顶点并入U后重新选择最小边，替换1: 原来无法到达的极大值 和2: 比原来小的边 
			closedge[j]={G.vexs[k],G.arcs[k][j]};//替换掉边权值大的 
		} 
	 } 
	 	print(G,closedge);
	/*找边的时候，是找已经并入最小生成树的所有点相关的边怕[权最小] 不是找刚入的点*/
}

int main()
{	
	AMGraph G;
	CreateUDN(G);
	ShowpGraph(G);//输出邻接矩阵	
	MiniSpanTree_Prim(G,'1'); //输出最小生成树 
	
	return 0;
}
/*测试数据直接cv到运行框框  
6 10
123456
1 2 6
1 4 5
1 3 1
2 3 5
3 4 5
3 5 6
3 6 4
2 5 3
5 6 6
6 4 2
答案：
辅助数组：0 6 1 5 32767 32767
(1-->3)mins: 1

辅助数组：0 5 0 5 6 4
(3-->6)mins: 4

辅助数组：0 5 0 2 6 0
(6-->4)mins: 2

辅助数组：0 5 0 0 6 0
(3-->2)mins: 5

辅助数组：0 0 0 0 3 0
(2-->5)mins: 3

辅助数组：0 0 0 0 0 0*/
