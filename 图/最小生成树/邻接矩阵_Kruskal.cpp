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
	for(int i=0;i<G.vexnum;i++){
		if(G.vexs[i]==U)
		return i;
	}
	return -1;//没有找到！ 
} 

class Edges//存储边的信息 
{
public:
	VerTexType Head;//边的起始点
	VerTexType Tail;//边的终点
	ArcType lowcost;//边上的权值 
};

void CreateUDN(AMGraph &G,Edges *&Edge)
{
	int i,j;//为后面查找方便 
	VerTexType v1,v2;//顶点
	ArcType w;//权值 
	cout<<"请你输入无向网中有多少个顶点 和弧\n";
	
	cin>>G.vexnum>>G.arcnum;
	Edge=new(std::nothrow) Edges[G.arcnum];
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
		Edge[k].Head=v1,Edge[k].Tail=v2,Edge[k].lowcost=w;//存储边的信息 
		i=LocateVex(G,v1),j=LocateVex(G,v2);	if(i==-1||j==-1){std::cout<<"顶点位置未找到\n",--k;continue;}//没找到本次循环作废 
		G.arcs[i][j]=w;
		G.arcs[j][i]=w;//无向网边是对称的 
	}
}


void MiniSpanTree_Kruskal(AMGraph &G)
{//无向网G以邻接矩阵形式存储，构造G的最小生成树T，输出T的各条边
	Edges *Edge=nullptr;//Edge类存储边的信息 
	CreateUDN(G,Edge);
	
	//将数组Edge中的元素按照权值从小到大排序 
	sort(Edge,Edge+G.arcnum,[](Edges a,Edges b){return a.lowcost<b.lowcost;});
	
	//辅助数组标识各个顶点所属的联通分量，为后面不能形成环构成条件 
	ArcType *Vexset=new(nothrow) ArcType[G.vexnum],vs1,vs2;
	for(int i=0;i<G.vexnum;i++)
	Vexset[i]=i;//初始化各个顶点自成一个联通分量
	
	for(int i=0;i<G.arcnum;i++)//依次查看数组Edge中的边 
	{
		int v1,v2; 
		v1=LocateVex(G,Edge[i].Head);//v1为边的始点head的下标
		v2=LocateVex(G,Edge[i].Tail);//v2为边终点Tail的下标
		vs1=Vexset[v1],vs2=Vexset[v2];
		
		if(vs1!=vs2)//起始点不等于终点说明不存在环 
		{
			cout<<Edge[i].Head<<"-->"<<Edge[i].Tail<<": "<<Edge[i].lowcost<<'\n';//输出次边
			
			for(int j=0;j<G.vexnum;j++)//合并两个分量，即两个集合统一编号
			{
				if(Vexset[j]==vs2) 
				Vexset[j]=vs1;
			}
			
		} //if
	}//for 
}

int main()
{
	AMGraph G;
	MiniSpanTree_Kruskal(G);
	
	return 0;
}
/*
测试数据： 
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
1-->3: 1
6-->4: 2
2-->5: 3
3-->6: 4
2-->3: 5
*/
