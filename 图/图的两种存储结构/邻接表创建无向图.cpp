#include<bits/stdc++.h>

#define MVNum 100//��󶥵���

using namespace std;

typedef  char VerTexType;//������������� 
typedef struct ArcNode//�߽�� 
{
	//adjacent���ڵ� vertex���� 
	int adjvex;//�ñ���ָ��Ķ���λ��[�±�]
	struct ArcNode *nextarc ;//ָ����һ���ߵ�ָ��
	int info;//Ȩֵ 
}ArcNode;

typedef struct VNode//������Ϣ 
{
	VerTexType data;
	ArcNode *firstarc;//ָ���һ�������ý��ı߽��ָ�� 
}Vnode,AdjList[MVNum];

typedef struct
{
	AdjList vertices;//Vnode��㹹�ɵ����� 
	int vexnum,arcnum;//ͼ�ĵ�ǰ�������ͱ��� 
}ALGraph;

int LocateVex(ALGraph G,VerTexType v)//���ҽ���ڶ�����λ�� 
{
	for(int i=0;i<G.vexnum;i++)
	if(G.vertices[i].data==v)
	return i;
	return -1;//û���ҵ� 
}

void CreateUDG(ALGraph &G)//Unconditional Dependency Graph����������ͼ 
{
	VerTexType v1,v2;//���� 
	ArcNode *p1,*p2;// �߽��ָ�� ����������ͼ����Ҫ�������� 
	
	//�����ڽӱ��ʾ��,��������ͼG
	cout<<"�����ܶ��������ܱ���: ";
	cin>>G.vexnum>>G.arcnum; 
	
	cout<<"���붥���ֵ\n";
	for(int i=0;i<G.vexnum;i++)
	{
		cin>>G.vertices[i].data;//���붥��ֵ
		G.vertices[i].firstarc=nullptr; 
	}
	
	for(int k=0;k<G.arcnum;k++)//������߹����ڽӱ�
	{
		cout<<"\n����������(����  ���� ): ";
		cin>>v1>>v2;
		int i=LocateVex(G,v1),j=LocateVex(G,v2);//�����ڶ�����е�����
		
		p1=new(nothrow) ArcNode;if(!p1){cerr<<"�����ڴ����"<<endl;abort();}
		p1->adjvex=j;
		
		//�ڶ���vi��λ����ͷ�巨�����뵽����vi�ı߱�ͷ�� 
		p1->nextarc=G.vertices[i].firstarc; G.vertices[i].firstarc=p1; 
		
		p2=new(nothrow) ArcNode;if(!p2){cerr<<"�����ڴ����"<<endl;abort();}
		p2->adjvex=i;//�ڽӵ� ���Ϊi
	
		//�ڶ���vj��λ����ͷ�巨�����뵽����vj�ı߱�ͷ�� 
		p2->nextarc=G.vertices[j].firstarc;G.vertices[j].firstarc=p2; 
	} 
} 

void ShowGraph(ALGraph G)
{
	int i,j;
	ArcNode *p;//�߽��ָ��
	for(i=0;i<G.vexnum;i++)
	{
		cout<<i<<" ["<<G.vertices[i].data<<"|--]-> ";//���������Ϣ
		for(p=G.vertices[i].firstarc;p;p=p->nextarc)//��������ߵ���Ϣ
		cout<<"["<<p->adjvex<<"|--]-> ";
		cout.put('\n'); 
	} 
} 

void CreateUDG_pushback(ALGraph &G)//��������ͼ β�巨 [�˽�]
{
	ArcNode *p1=nullptr,*r1=nullptr,*r2=nullptr;//r1��r2��ʾβָ�� 
	int i,j;
	VerTexType v1,v2;
	
	cout<<"��������ͼ�� ���ٸ�����ͱ�\n";
	cin>>G.vexnum>>G.arcnum;
	
	cout<<"�������붥�������\n";
	for(int k=0;k<G.vexnum;k++)
	{
		cin>>G.vertices[k].data;
		G.vertices[k].firstarc=nullptr;
	}	
	
	cout<<"�������루���㣬���㣩\n";
	for(int k=0;k<G.arcnum;k++)
	{
		cin>>v1>>v2;
		i=LocateVex(G,v1),j=LocateVex(G,v2);//�ҵ���������� 
		
		p1=new(nothrow) ArcNode;
		p1->adjvex=j;p1->nextarc=nullptr;
	    r1= G.vertices[i].firstarc;
		if(r1==nullptr)
		 G.vertices[i].firstarc=p1;	//ʵ������������ִֻ��һ�� 
		else
		{
			for(;r1->nextarc;r1=r1->nextarc);//һ��Ҫ�зֺ� 
			r1->nextarc=p1;
			
		}
		
		//�ڶ������ָ��������ƣ�˼��һ��һ�� 
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

//-�������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������� 
bool visited[MVNum];//��־����
void DFS(ALGraph &G,int v)//������ȱ����ڽӱ�
{
	ArcNode *p=nullptr;//����ָ�� 
	int w=0;//��ȡ������±� 
	cout<<G.vertices[v].data<<" ";
	
	visited[v]=true;
	p=G.vertices[v].firstarc;//ָ��v�ĵ�һ���߽��
	
	while(p!=nullptr)
	{
	 	w=p->adjvex;
	 	if(visited[w]==false)//���wδ��������ݹ����DFS 
	 	DFS(G,w);
	 	p=p->nextarc;//pָ����һ���߽��
	}
} 

void DFS_Traverse(ALGraph G)
{
	
	for(int i=0;i<G.vexnum;i++)//��ֹ����ͨ��ͼ����Ҫ��һ��δ�����ʵĶ�����Ϊ��ʼ�� 
	{
		if(!visited[i])
		DFS(G,i);
	}
}

//------------------------------------------------------------------------------------------------------------------------------------------------------- 
bool visited_bfs[MVNum];
void BFS(ALGraph G,int v)//Breadth First Search
{
    queue<int> q;//�洢�Ѿ������ʵĽ�� 
	cout<<G.vertices[v].data<<" ";
	visited_bfs[v]=true;
	q.push(v);
	
	while(!q.empty())//���в���Ϊ��
	{
		int u=q.front();q.pop();//���������������ڽӵ� 
		for(auto p=G.vertices[u].firstarc;p;p=p->nextarc)//�����ڽӵı߽�� 
		{
			if(!visited_bfs[p->adjvex])//�ñ���ָ��Ķ���[�±�]û�б����� 
			{
				cout<<G.vertices[p->adjvex].data<<" ";
				visited_bfs[p->adjvex]=1;//��־����ı�
				q.push(p->adjvex); 
			}//if	
    	}//for 
	}//while 
}

void BFS_Traverse(ALGraph G)
{
	for(int i=0;i<G.vexnum;i++)//��ֹ����ͨ��ͼ 
	if(!visited_bfs[i])//�����ж���δ���������ͼ������ѡһ����Ϊ��ʼ�� 
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
	/*��������
	�����ܶ��������ܱ���: 4 3
    ���붥���ֵ A B C D
	����������(����  ���� ):A B
	                        A C
							B D
	�����A->2->1
	      B->3->0
		  C->0
		  D->1*/
    cout<<"�������������\n";
	DFS_Traverse(G);
	cout<<"\n�������������\n";
    BFS_Traverse(G);
	/*�����Ĳ������� 
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
  ������������������
		1 3 7 6 2 5 8 4
		�������������
		1 3 2 7 6 5 4 8 */
	return 0;
}
