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
void Show_shortestPath(AMGraph G,int i,int k,int *Path)//利用递归输出路径 
{
	if(k==-1)
	{cout<<"没有最短路径,不考虑自身\n"<<endl;return;}
	if(k!=i)//前驱不能等于起点结点 
		Show_shortestPath(G,i,Path[k],Path);

	cout<<G.vexs[k]<<"-->";
		
}
void print(AMGraph G,bool S[],int Path[],int D[])//最短路径输出 
{
	for(int i=0;i<G.vexnum;i++)
	cout<<'\t'<<"v="<<i<<" ";
	cout<<"\nS"<<"       ";
	
	for(int i=0;i<G.vexnum;i++)//S数组输出 
	{
	cout<<S[i]<<"\t";
	}
	cout.put('\n');
	
	cout<<'D'<<"       ";
	for(int i=0;i<G.vexnum;i++)//D数组输出
	{
			if(D[i]==MaxInt)//为极大值的时候输出那个符号 
			cout<<"∞"<<'\t';
			else
			cout<<D[i]<<'\t';
	} 
	cout.put('\n');
	
	cout<<"Path"<<"   ";
	for(int i=0;i<G.vexnum;i++)//Path数组输出
	{
		cout<<Path[i]<<'\t';
	}		
	cout.put('\n');cout.put('\n');
	
} 

void ShortestPath_DIJ(AMGraph G,int v0)//求最短路径
{//用Dijkstra算法在有向网Gv0顶点到其余顶点的最短路径 

	//记录从源点到终点vi是否已被确定最短路径长度
	bool *S=new bool[G.vexnum];
	//记录从源点v0到终点vi的当前最短路径vi的直接前驱序号 无弧就为-1 
	int *Path=new int[G.vexnum];
	//记录 从源点v0到终点vi的当前最短路径长度 无弧就为极大值 
	int *D=new int[G.vexnum];
	
	for(int v=0;v<G.vexnum;v++)//n个顶点依次初始化 
	{
		S[v]=false;//S初始化为空集
		D[v]=G.arcs[v0][v];//初始化为v0的各条邻接的边的权值
		
		if(D[v]<MaxInt)//不是极大值
		Path[v]=v0;//记录前驱顶点的序号 
		else Path[v]=-1; 
	}
	
	S[v0]=true;//已经确认最短路径长度
	D[v0]=0;//v0到v0的距离为0
	cout<<"S:    从 源 点 v0 到 终 点 vi 是 否 已 经 确 认 最 短 路 径 长 度\nD:    记 录 从 源 点 到 终 点 当 前 最 短 路 径 长 度 \nPath: 记 录 从 源 点 v0 到 终 点 vi 当 前 最 短 路 径 上 vi 的 直 接 前 驱 顶 点 序 号\n";
	print(G,S,Path,D);//输出 

/*-----初始化结束，开始主循环，每一次求的v0到某个顶点v的最短路径，将v加入到S集合-----------*/
	for(int i=1;i<G.vexnum;i++)//对其余n-1个顶点，依次进行计算 
	{
	int min=MaxInt,v;//初始值为极大值
		
		for(int w=0;w<G.vexnum;w++)
		{
			if(!S[w]&&D[w]<min)
			{v=w,min=D[w];}//选择一条当前最短路径，终点是v 
		}
		
	S[v]=true;//找到了最短路径，将v加入S 
	for(int w=0;w<G.vexnum;w++)
	{
		//没有确认最短路径，新加入的结点作为中间结点总路径小于原来的路径就更新 
		if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
		{//更新 
			D[w]=D[v]+G.arcs[v][w];
			Path[w]=v;
		}
	}
	
	print(G,S,Path,D);//输出 	
	} //for
	
    cout<<"请你输入要查询的最短路径 终点顶点 \n";
	VertexType vj;
	cin>>vj;
	
	int i=LocateVex(G,vj);//i为起始节点
	int k=Path[i];	//为前驱结点 
	Show_shortestPath(G,i,k,Path); 
	cout<<G.vexs[i]<<": "<<D[i]<<'\n';
}

int main()
{
	AMGraph G;
	
	CreateUDN(G);
	ShowpGraph(G);
	
	ShortestPath_DIJ(G,0);
	return 0;
}
/*测试数据 
6 8
012345
0 2 10
0 4 30
0 5 100
1 2 5
2 3 50
3 5 10
4 3 20
4 5 60*/
