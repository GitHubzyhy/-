#include<bits/stdc++.h>

#define MVNum 100//最大顶点数

using namespace std;

typedef  char VerTexType;//顶点的数据类型 
typedef struct ArcNode//边结点 
{
	//adjacent相邻的 vertex顶点 
	int adjvex;//该边所指向的顶点位置[下标]
	struct ArcNode *nextarc ;//指向下一条边的指针
	int info;//权值 
}ArcNode;

typedef struct VNode//顶点信息 
{
	VerTexType data;
	ArcNode *firstarc;//指向第一条依附该结点的边结点指针 
}Vnode,AdjList[MVNum];

typedef struct
{
	AdjList vertices;//Vnode结点构成的数组 
	int vexnum,arcnum;//图的当前顶点数和边数 
}ALGraph;

int LocateVex(ALGraph G,VerTexType v)//查找结点在顶点表的位置 
{
	for(int i=0;i<G.vexnum;i++)
	if(G.vertices[i].data==v)
	return i;
	return -1;//没有找到 
}

void CreateUDG(ALGraph &G)//Unconditional Dependency Graph无条件依赖图 
{
	VerTexType v1,v2;//顶点 
	ArcNode *p1,*p2;// 边结点指针 这里是无向图所以要插入两次 
	
	//采用邻接表表示法,创建无向图G
	cout<<"输入总顶点数，总边数: ";
	cin>>G.vexnum>>G.arcnum; 
	
	cout<<"输入顶点的值\n";
	for(int i=0;i<G.vexnum;i++)
	{
		cin>>G.vertices[i].data;//输入顶点值
		G.vertices[i].firstarc=nullptr; 
	}
	
	for(int k=0;k<G.arcnum;k++)//输入各边构造邻接表
	{
		cout<<"\n请你上输入(顶点  顶点 ): ";
		cin>>v1>>v2;
		int i=LocateVex(G,v1),j=LocateVex(G,v2);//返回在顶点表中的坐标
		
		p1=new(nothrow) ArcNode;if(!p1){cerr<<"分配内存错误！"<<endl;abort();}
		p1->adjvex=j;
		
		//在顶点vi的位置用头插法，插入到顶点vi的边表头部 
		p1->nextarc=G.vertices[i].firstarc; G.vertices[i].firstarc=p1; 
		
		p2=new(nothrow) ArcNode;if(!p2){cerr<<"分配内存错误！"<<endl;abort();}
		p2->adjvex=i;//邻接点 序号为i
	
		//在顶点vj的位置用头插法，插入到顶点vj的边表头部 
		p2->nextarc=G.vertices[j].firstarc;G.vertices[j].firstarc=p2; 
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

void CreateUDG_pushback(ALGraph &G)//创建无向图 尾插法 [了解]
{
	ArcNode *p1=nullptr,*r1=nullptr,*r2=nullptr;//r1和r2表示尾指针 
	int i,j;
	VerTexType v1,v2;
	
	cout<<"请你输入图有 多少个顶点和边\n";
	cin>>G.vexnum>>G.arcnum;
	
	cout<<"请你输入顶点的数据\n";
	for(int k=0;k<G.vexnum;k++)
	{
		cin>>G.vertices[k].data;
		G.vertices[k].firstarc=nullptr;
	}	
	
	cout<<"请你输入（顶点，顶点）\n";
	for(int k=0;k<G.arcnum;k++)
	{
		cin>>v1>>v2;
		i=LocateVex(G,v1),j=LocateVex(G,v2);//找到顶点的坐标 
		
		p1=new(nothrow) ArcNode;
		p1->adjvex=j;p1->nextarc=nullptr;
	    r1= G.vertices[i].firstarc;
		if(r1==nullptr)
		 G.vertices[i].firstarc=p1;	//实现两点相连，只执行一次 
		else
		{
			for(;r1->nextarc;r1=r1->nextarc);//一定要有分号 
			r1->nextarc=p1;
			
		}
		
		//第二个部分跟上面类似，思想一摸一样 
		p1=new(nothrow) ArcNode;
		p1->adjvex=i;p1->nextarc=nullptr;
		r2= G.vertices[j].firstarc;
		if(r2==nullptr)
		 G.vertices[j].firstarc=p1;
		else
		{
			for(;r2->nextarc;r2=r2->nextarc);
			r2->nextarc=p1;			
		}
		
	}//for
}

//-—————————————————————————————————————————————————————————————————————————————————————————————————————————— 
bool visited[MVNum];//标志数组
void DFS(ALGraph &G,int v)//深度优先遍历邻接表
{
	ArcNode *p=nullptr;//工作指针 
	int w=0;//获取顶点的下标 
	cout<<G.vertices[v].data<<" ";
	
	visited[v]=true;
	p=G.vertices[v].firstarc;//指向v的第一个边结点
	
	while(p!=nullptr)
	{
	 	w=p->adjvex;
	 	if(visited[w]==false)//如果w未被访问则递归调用DFS 
	 	DFS(G,w);
	 	p=p->nextarc;//p指向下一个边结点
	}
} 

void DFS_Traverse(ALGraph G)
{
	
	for(int i=0;i<G.vexnum;i++)//防止非联通子图，需要从一个未被访问的顶点作为起始点 
	{
		if(!visited[i])
		DFS(G,i);
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------- 
bool visited_bfs[MVNum];
void BFS(ALGraph G,int v)//Breadth First Search
{
    queue<int> q;//存储已经被访问的结点 
	cout<<G.vertices[v].data<<" ";
	visited_bfs[v]=true;
	q.push(v);
	
	while(!q.empty())//队列不能为空
	{
		int u=q.front();q.pop();//弹出来访问它的邻接点 
		for(auto p=G.vertices[u].firstarc;p;p=p->nextarc)//查找邻接的边结点 
		{
			if(!visited_bfs[p->adjvex])//该边所指向的顶点[下标]没有被访问 
			{
				cout<<G.vertices[p->adjvex].data<<" ";
				visited_bfs[p->adjvex]=1;//标志数组改变
				q.push(p->adjvex); 
			}//if	
    	}//for 
	}//while 
}

void BFS_Traverse(ALGraph G)
{
	for(int i=0;i<G.vexnum;i++)//防止非联通子图 
	if(!visited_bfs[i])//若还有顶点未被访问则从图中另外选一个作为起始点 
	BFS(G,i);
	cout.put('\n');
}

int main()
{
	memset(visited,0,sizeof(bool)); 
	memset(visited_bfs,0,sizeof(bool)); 
	ALGraph G;
	CreateUDG(G);
//	CreateUDG_pushback(G);
	ShowGraph(G);
	/*测试数据
	输入总顶点数，总边数: 4 3
    输入顶点的值 A B C D
	请你上输入(顶点  顶点 ):A B
	                        A C
							B D
	结果：A->2->1
	      B->3->0
		  C->0
		  D->1*/
    cout<<"深度优先搜索！\n";
	DFS_Traverse(G);
	cout<<"\n广度优先搜索！\n";
    BFS_Traverse(G);
	/*遍历的测试数据 
	8 9
	12345678
	1 2 
	
	1 3 
	
	2 4 
	
	2 5 

	4 8 
	
	5 8 
	
	3 6 
	
	3 7 
	
	6 7 
  结果：深度优先搜索！
		1 3 7 6 2 5 8 4
		广度优先搜索！
		1 3 2 7 6 5 4 8 */
	return 0;
}
