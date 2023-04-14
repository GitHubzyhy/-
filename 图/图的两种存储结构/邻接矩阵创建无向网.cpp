#include<bits/stdc++.h>

#define MaxInt 32767//��ʾ����ֵ
#define MVNum 100//��󶥵���

using namespace std;

typedef char VerTexType;//���趥�����������Ϊ�ַ���
typedef int ArcType;//����ߵ�Ȩֵ����Ϊ����

typedef struct
{
	VerTexType vexs[MVNum];//�����
	ArcType arcs[MVNum][MVNum];//�ڽӾ���
	int vexnum,arcnum;//ͼ�ĵ�ǰ�����ͱ��� 
	
}AMGraph; 

int LocateVex(AMGraph G,VerTexType U)
{
	int i;
	for(i=0;i<G.vexnum;++i)//�ҵ���Ӧ�Ķ���
	if(U==G.vexs[i])//�ڶ������Ѱ�� 
	return i;
	return -1;//û���ҵ� 
}

void CreateUDN(AMGraph &G)
{
	VerTexType v1,v2;//�������Ķ��� 
	ArcType w;//Ȩֵ 
	
	cout<<"�������������ܶ��������ܱ���\n";
	//ʹ���ڽӾ����ʾ��������������G
	cin>>G.vexnum>>G.arcnum;//�����ܶ��������ܱ���
	
	cout<<"�������붥�����Ϣ \n";
	for(int i=0;i<G.vexnum;i++)
	cin>>G.vexs[i];//�������붥�����Ϣ 
	
	for(int i=0;i<G.vexnum;i++)
	for(int j=0;j<G.vexnum;j++)//G.vexnum X G.vexnum�ľ��� 
	G.arcs[i][j]=MaxInt;//ȫ����ʼ��Ϊ����ֵ
	
	for(int k=0;k<G.arcnum;k++)//����ͼ���ڽӾ����жԳ��� 
	{
		cout<<"\n����������(����  ����  Ȩֵ): ";
		cin>>v1>>v2>>w;
		int i=LocateVex(G,v1),j=LocateVex(G,v2);//ȷ��v1��v2�ڶ�����λ��
		
		if(i==-1||j==-1){cout<<"����λ��δ�ҵ�\n",--k;continue;}//û�ҵ�����ѭ������ 
		G.arcs[i][j]=w;//��<v1,v2>��Ȩֵ��Ϊw
		G.arcs[j][i]=G.arcs[i][j];// <v1,v2>�ĶԳƱ�<v2,v1>��ȨֵҲΪw 
	} 
} 

void ShowpGraph(AMGraph G)
{
	cout<<"�ڽӾ���Ϊ��\n   ";
	for(int i=0;i<G.vexnum;i++)//�������� 
	cout<<G.vexs[i]<<"     ";
	cout.put('\n');
	
	for(int i=0;i<G.vexnum;i++)
	{
		cout<<G.vexs[i]<<"  ";
		for(int j=0;j<G.vexnum;j++)//����ڽӾ��� 
		{
			if(G.arcs[i][j]==MaxInt)//Ϊ����ֵ��ʱ������Ǹ����� 
			cout<<"��  ";
			else
			cout<<G.arcs[i][j]<<"   ";
		}
		cout<<"\n\n";
	}//for
}

bool visited[MVNum];//���ʶ�̬���飬���ʼֵΪfalse
void DFS(AMGraph G,int v)//Dept First Search 
{
	cout<<G.vexs[v]<<" ";//�������Ϊv�Ķ���
	visited[v]=true;// ���÷��ʱ�־������Ӧ����ֵΪtrue
	for(int w=0;w<G.vexnum;w++)//���μ���ڽӾ������ڵ��� 
	if(G.arcs[v][w]!=MaxInt&&visited[w]==false)//�ҵ�һ���ڽӵ㲢��δ�����ʣ���
		DFS(G,w);//����ݹ� 	
}

bool visited_bfs[MVNum];
void BFS(AMGraph G,int v)//Breadth First Search
{
    queue<int> q;
	cout<<G.vexs[v]<<" ";
	visited_bfs[v]=true;
	q.push(v);
	
	while(!q.empty())//���в���Ϊ��
	{
		int u=q.front();q.pop();
		for(int w=0;w<G.vexnum;w++)//���μ���ڽӾ������ڵ���
		{
			if(G.arcs[u][w]!=MaxInt&&visited[w]==false)//�ҵ�һ���ڽӵ㲢��δ�����ʣ���
			{
					cout<<G.vexs[w]<<" ";
					visited_bfs[w]=1;//��־����ı�
					q.push(w);
					 
			}//if	
		}//for 
 	}//while 
}
//-----------------------------------------------------------------------------------------------------
void DFS_Traverse(AMGraph G)//������ȱ��� 
{
	
	for(int i=0;i<G.vexnum;i++)//��ֹ����ͨ��ͼ����Ҫ��һ��δ�����ʵĶ�����Ϊ��ʼ�� 
		if(!visited[i])//û����һ�ξ��м�����ͨ���� 
		DFS(G,i);
}

void BFS_Traverse(AMGraph G)//������ȱ��� 
{
	for(int i=0;i<G.vexnum;i++)//��ֹ����ͨ��ͼ 
		if(!visited_bfs[i])//�����ж���δ���������ͼ������ѡһ����Ϊ��ʼ�� 
		BFS(G,i);
	cout.put('\n');
}

int main()
{
	memset(visited_bfs,0,sizeof(bool));
	memset(visited,0,sizeof(bool));//��ʼ����
	AMGraph G;
	
	CreateUDN(G);//���� �ڽӾ��� 
	ShowpGraph(G);//��� �ڽӾ��� 
    DFS_Traverse(G);//������ȱ��� 
    cout<<"\n������ȱ���\n";
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

�����1 2 4 8 5 3 6 7
      1 2 3 4 5 6 7 8*/
