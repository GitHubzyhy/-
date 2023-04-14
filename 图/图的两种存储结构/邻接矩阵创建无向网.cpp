#include<bits/stdc++.h>

#define MaxInt 32767//表示极大值
#define MVNum 100//最大顶点数

using namespace std;

typedef char VerTexType;//假设顶点的数据类型为字符型
typedef int ArcType;//假设边的权值类型为整型

typedef struct
{
	VerTexType vexs[MVNum];//顶点表
	ArcType arcs[MVNum][MVNum];//邻接矩阵
	int vexnum,arcnum;//图的当前点数和边数 
	
}AMGraph; 

int LocateVex(AMGraph G,VerTexType U)
{
	int i;
	for(i=0;i<G.vexnum;++i)//找到对应的顶点
	if(U==G.vexs[i])//在顶点表中寻找 
	return i;
	return -1;//没有找到 
}

void CreateUDN(AMGraph &G)
{
	VerTexType v1,v2;//边依附的顶点 
	ArcType w;//权值 
	
	cout<<"请你输入输入总顶点数，总边数\n";
	//使用邻接矩阵表示法，创建无向网G
	cin>>G.vexnum>>G.arcnum;//输入总顶点数，总边数
	
	cout<<"依次输入顶点的信息 \n";
	for(int i=0;i<G.vexnum;i++)
	cin>>G.vexs[i];//依次输入顶点的信息 
	
	for(int i=0;i<G.vexnum;i++)
	for(int j=0;j<G.vexnum;j++)//G.vexnum X G.vexnum的矩阵 
	G.arcs[i][j]=MaxInt;//全部初始化为极大值
	
	for(int k=0;k<G.arcnum;k++)//无向图的邻接矩阵有对称性 
	{
		cout<<"\n请你上输入(顶点  顶点  权值): ";
		cin>>v1>>v2>>w;
		int i=LocateVex(G,v1),j=LocateVex(G,v2);//确定v1和v2在顶点表的位置
		
		if(i==-1||j==-1){cout<<"顶点位置未找到\n",--k;continue;}//没找到本次循环作废 
		G.arcs[i][j]=w;//边<v1,v2>的权值置为w
		G.arcs[j][i]=G.arcs[i][j];// <v1,v2>的对称边<v2,v1>的权值也为w 
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

bool visited[MVNum];//访问动态数组，其初始值为false
void DFS(AMGraph G,int v)//Dept First Search 
{
	cout<<G.vexs[v]<<" ";//访问序号为v的顶点
	visited[v]=true;// 并置访问标志数组相应分量值为true
	for(int w=0;w<G.vexnum;w++)//依次检查邻接矩阵所在的行 
	if(G.arcs[v][w]!=MaxInt&&visited[w]==false)//找到一个邻接点并且未被访问！！
		DFS(G,w);//进入递归 	
}

bool visited_bfs[MVNum];
void BFS(AMGraph G,int v)//Breadth First Search
{
    queue<int> q;
	cout<<G.vexs[v]<<" ";
	visited_bfs[v]=true;
	q.push(v);
	
	while(!q.empty())//队列不能为空
	{
		int u=q.front();q.pop();
		for(int w=0;w<G.vexnum;w++)//依次检查邻接矩阵所在的行
		{
			if(G.arcs[u][w]!=MaxInt&&visited[w]==false)//找到一个邻接点并且未被访问！！
			{
					cout<<G.vexs[w]<<" ";
					visited_bfs[w]=1;//标志数组改变
					q.push(w);
					 
			}//if	
		}//for 
 	}//while 
}
//-----------------------------------------------------------------------------------------------------
void DFS_Traverse(AMGraph G)//深度优先遍历 
{
	
	for(int i=0;i<G.vexnum;i++)//防止非联通子图，需要从一个未被访问的顶点作为起始点 
		if(!visited[i])//没调用一次就有几个联通分量 
		DFS(G,i);
}

void BFS_Traverse(AMGraph G)//广度优先遍历 
{
	for(int i=0;i<G.vexnum;i++)//防止非联通子图 
		if(!visited_bfs[i])//若还有顶点未被访问则从图中另外选一个作为起始点 
		BFS(G,i);
	cout.put('\n');
}

int main()
{
	memset(visited_bfs,0,sizeof(bool));
	memset(visited,0,sizeof(bool));//初始化！
	AMGraph G;
	
	CreateUDN(G);//创建 邻接矩阵 
	ShowpGraph(G);//输出 邻接矩阵 
    DFS_Traverse(G);//深度优先遍历 
    cout<<"\n广度优先遍历\n";
    BFS_Traverse(G);
	return 0;
}/*
8 9
12345678
1 2 11

1 3 11

2 4 11

2 5 11

4 8 11

5 8 11

3 6 11

3 7 11

6 7 11

结果：1 2 4 8 5 3 6 7
      1 2 3 4 5 6 7 8*/
