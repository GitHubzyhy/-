#include<iostream>
#include<stack>
#include<direct.h>

#define MvNum 100//��󶥵���

using namespace std;

typedef char VerTexType;//�������������
typedef struct ArcNode//�߽��
{
	int adjvex;
	struct ArcNode *nextarc;
	int info;
}ArcNode;

typedef struct Vnode//������Ϣ
{
	VerTexType data;
	ArcNode *firstarc;//ָ���һ�������ý��ı߽��ָ�� 
}Vnode,AdjList[MvNum];

typedef struct//�߽�� 
{
	AdjList vertices;//Vnode��㹹�ɵ����� 
	int vexnum,arcnum;
}ALGraph;

int LocateVex(ALGraph G,VerTexType v)//���ҽ���ڶ�����λ�� 
{
	for(int i=0;i<G.vexnum;i++)
	{
	 	if(G.vertices[i].data==v)
	 	return i;
	}
	 return -1;//û���ҵ� 
}

void CreateAov(ALGraph &G)//��һ������ͼ 
{
	VerTexType v1,v2;
	ArcNode *p1;
	
	cout<<"�����ܶ��������ܱ���: ";
	cin>>G.vexnum>>G.arcnum; 
	
	cout<<"���붥���ֵ\n";
	for(int i=0;i<G.vexnum;i++)
	{
		cin>>G.vertices[i].data;//���붥��ֵ
		G.vertices[i].firstarc=nullptr; 
	}
	
	for(int k=0;k<G.arcnum;k++)
	{
		cout<<"\n����������(����  ���� ): ";
		cin>>v1>>v2;
		int i=LocateVex(G,v1),j=LocateVex(G,v2);//�����ڶ�����е�����
		
		p1=new(nothrow) ArcNode;if(!p1){cerr<<"�����ڴ�ʧ�ܣ�\n";abort();}
		p1->adjvex=j;
		p1->nextarc=G.vertices[i].firstarc;G.vertices[i].firstarc=p1;
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
void FindInDegree(ALGraph G,int indegree[])
{//��ʼ�����飬����Ĭ��Ϊ0
	memset(indegree,0,G.vexnum*sizeof(int));
//�����ڽӱ����ݸ��������еĽ���������洢�ĸ�����λ���±꣬��indegree������Ӧλ��+1
	for(int i=0;i<G.vexnum;i++)
	for(ArcNode *p=G.vertices[i].firstarc;p;p=p->nextarc)
	indegree[p->adjvex]++;//���++ 
}

bool TopologicalSort(ALGraph G,int *topo)	//topo:��¼top���еĶ������
{
	//��Ÿ���׵����
	int *indegree=new(nothrow) int[G.vexnum];if(!indegree){cerr<<"�����ڴ�ʧ�ܣ�\n";abort();}
	//�ݴ���������Ϊ0�Ķ���,���Ա����ظ�ɨ������indegree������Ϊ0�Ķ��㣬����㷨��Ч�� 
	stack<int> S; 
 
	FindInDegree(G,indegree);
	
	for(int i=0;i<G.vexnum;i++)
	if(!indegree[i])//���Ϊ0����ջ
	S.push(i);
	
	int m=0;//������������
	while(!S.empty()) 
	{
		int i=S.top();S.pop();//��Ϊ0�Ľ�㶼��ջ���� 
		
		topo[m++]=i;//�����������У�������Ƕ����±� 
		for(ArcNode  *p=G.vertices[i].firstarc;p;p=p->nextarc)//���������ڽӱ� 
		{
			int k=p->adjvex;//vkΪvi���ڽӵ�
			--indegree[k];// ɾ����������Ϊβ�Ļ�
			if(!indegree[k])//���Ϊ0 ��ջ 
			S.push(k);
		}	
	}
	
	void Show_topo(int *);
	
	if(m<G.vexnum) {cout<<"�� �� �� ͼ �� �� ·���� Ϊ �� �� �� �� �� �� ǰ �� �� �� �� �� Ϊ  0���� �� �� ջ !\n"; return 0;}
	else { cout<<"�� �� �� ͼ �� �� ·�� \n";return 1;}
}
void Show_topo(ALGraph G,int *topo)//�������д�������±� 
{
	cout<<"��������: ";
	for(int i=0;i<G.vexnum;i++)
	cout<<G.vertices[topo[i]].data<<" ";
	cout.put('\n');
}

int main()
{
	ALGraph G;
	CreateAov(G);
	ShowGraph(G);
	
	//�洢�Ľ���� 
	int *topo=new(nothrow) int[G.vexnum];if(!topo){cerr<<"�����ڴ�ʧ�ܣ�\n";abort();}
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
