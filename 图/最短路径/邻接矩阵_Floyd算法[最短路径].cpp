#include<bits/stdc++.h>

#define MaxInt 32767//表示权的极大值
#define MvNum 100//最大顶点数

using namespace std;

typedef char VertexType;
typedef int ArcType;
typedef struct//有向网结构
{
	VertexType vexs[MvNum];//顶点表
	ArcType arcs[MvNum][MvNum];//邻接矩阵 
	int vexnum,arcnum;
}AMGraph; 

int LocateVex(AMGraph G,VertexType U)//在顶点表中查找u在的下标
{
	
	for(int i=0;i<G.vexnum;i++){
		if(G.vexs[i]==U)
		return i;
	} 
	return -1;//没有找到 
} 

void CreateUDN(AMGraph &G)
{
	int i,j;
	VertexType v1,v2;//顶点 
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
		i=LocateVex(G,v1),j=LocateVex(G,v2);
		G.arcs[i][j]=w;
	}
	
}

void ShowpGraph(AMGraph G)
{
	
	cout<<"邻接矩阵为：\n   ";
	for(int i=0;i<G.vexnum;i++)//输出顶点表 
	cout<<G.vexs[i]<<"     ";
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
void Show_shortestPath(AMGraph G, int i,int j,int **Path,int k)//i为起始结点，j为终端结点 
{
	if(k==-1)
	{cout<<"没有最短路径,不考虑自身\n"<<endl;return;}
	
	if(k!=i)//中间结点k!=起始点i
	Show_shortestPath(G,i,j,Path,Path[i][k]);
			
	cout<<G.vexs[k]<<"-->";
}

void print(AMGraph G,int **Path,int **D)
{
	 cout.put('\n');
	 for(int k=0;k<G.vexnum;k++)//k为中间结点
	 for(int i=0;i<G.vexnum;i++)//i为起始点
	 for(int j=0;j<G.vexnum;j++)//j为终点
	 {
	 	if(D[i][k]+D[k][j]<D[i][j])//找到一条更短的更新
		 {
		 	D[i][j]=D[i][k]+D[k][j];
		 	Path[i][j]=Path[k][j];//更改j的前驱为k 
		 } 
	 } 
	 
	    cout<<"D:    记 录 当 前 顶 点 vi 和 vj 的 最 短 路 径 长 度 \nPath: 记 录 前 最 短 路 径 顶 点 上 vj 的 前 一 项 序 号\n";
		cout<<"\t\tD"<<'\n';
		for(int i=0;i<G.vexnum;i++)
		{
		for(int j=0;j<G.vexnum;j++)
		{
			cout<<D[i][j]<<" ";
		}
		cout.put('\n');
		}	
		cout.put('\n');
			
		cout<<"\t\tPath"<<'\n';
		for(int i=0;i<G.vexnum;i++)
		{
		for(int j=0;j<G.vexnum;j++)
		cout<<Path[i][j]<<" ";
		cout.put('\n');
		}	
		
		cout<<"请你输入要查询的最短路径(顶点 顶点)\n";
		VertexType v1,v2;
		cin>>v1>>v2;
		
		int i=LocateVex(G,v1),j=LocateVex(G,v2);//i为起始节点，j为终端结点 
		int k=Path[i][j];//k为中间结点 
	    Show_shortestPath(G,i,j,Path,k);
	    cout<<v2<<": "<<D[i][j]<<'\n';
}

void ShortestPath_Floyd(AMGraph G)
{
	//用Floyd算法求有向图G中各对顶点i和j之间的最短路径
	 //当前最短路径顶点上vj的前一项序号，和Dijkstra 是源点v0固定所以用的一维数组 
	int **Path=new int*[G.vexnum];
	 //记录当前顶点vi和vj的最短路径长度 
	int **D=new int*[G.vexnum];
	for(int i=0;i<G.vexnum;i++)
	{
		Path[i]=new int;
		D[i]=new int;
	}		
	 
	 for(int i=0;i<G.vexnum;i++)//各对顶点之间初始已知路径以及距离 
	 for(int j=0;j<G.vexnum;j++)
	 {
	 	if(i==j)//对角线为0，不考虑自身 
	 	D[i][j]=0;
	 	else
	 	D[i][j]=G.arcs[i][j];
	 	
	 	if(D[i][j]<MaxInt && (i!=j))//对角线为0不考虑自身	
			 	Path[i][j]=i;
		else
		Path[i][j]=-1;
	 }
	
	print(G,Path,D);

}

int main()
{
	AMGraph G;

	CreateUDN(G);
	ShowpGraph(G);
	ShortestPath_Floyd(G);
	 
	return 0;
} 
/*
4 8
0123
0 1 1
0 3 4
1 2 9
1 3 2
2 0 3
2 1 5
2 3 8
3 2 6*/
