#include<bits/stdc++.h>

#define MaxInt 32767//��ʾȨ�ļ���ֵ
#define MvNum 100//��󶥵���

using namespace std;

typedef char VertexType;
typedef int ArcType;
typedef struct//�������ṹ
{
	VertexType vexs[MvNum];//�����
	ArcType arcs[MvNum][MvNum];//�ڽӾ��� 
	int vexnum,arcnum;
}AMGraph; 

int LocateVex(AMGraph G,VertexType U)//�ڶ�����в���u�ڵ��±�
{
	
	for(int i=0;i<G.vexnum;i++){
		if(G.vexs[i]==U)
		return i;
	} 
	return -1;//û���ҵ� 
} 

void CreateUDN(AMGraph &G)
{
	int i,j;
	VertexType v1,v2;//���� 
	ArcType w;//Ȩֵ 
	
	cout<<"�����������������ж��ٸ����� �ͻ�\n";
	cin>>G.vexnum>>G.arcnum;
	
	cout<<"�������붥��\n";
	for(i=0;i<G.vexnum;i++)
	cin>>G.vexs[i];
	
	for(i=0;i<G.vexnum;i++)//���ڽӾ��󸳳�ֵ 
	for(j=0;j<G.vexnum;j++)
	G.arcs[i][j]=MaxInt;
	
	cout<<"�������� ���� ���� Ȩֵ\n";
	for(int k=0;k<G.arcnum;k++)
	{
		cin>>v1>>v2>>w;
		i=LocateVex(G,v1),j=LocateVex(G,v2);
		G.arcs[i][j]=w;
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
void Show_shortestPath(AMGraph G, int i,int j,int **Path,int k)//iΪ��ʼ��㣬jΪ�ն˽�� 
{
	if(k==-1)
	{cout<<"û�����·��,����������\n"<<endl;return;}
	
	if(k!=i)//�м���k!=��ʼ��i
	Show_shortestPath(G,i,j,Path,Path[i][k]);
			
	cout<<G.vexs[k]<<"-->";
}

void print(AMGraph G,int **Path,int **D)
{
	 cout.put('\n');
	 for(int k=0;k<G.vexnum;k++)//kΪ�м���
	 for(int i=0;i<G.vexnum;i++)//iΪ��ʼ��
	 for(int j=0;j<G.vexnum;j++)//jΪ�յ�
	 {
	 	if(D[i][k]+D[k][j]<D[i][j])//�ҵ�һ�����̵ĸ���
		 {
		 	D[i][j]=D[i][k]+D[k][j];
		 	Path[i][j]=Path[k][j];//����j��ǰ��Ϊk 
		 } 
	 } 
	 
	    cout<<"D:    �� ¼ �� ǰ �� �� vi �� vj �� �� �� · �� �� �� \nPath: �� ¼ ǰ �� �� · �� �� �� �� vj �� ǰ һ �� �� ��\n";
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
		
		cout<<"��������Ҫ��ѯ�����·��(���� ����)\n";
		VertexType v1,v2;
		cin>>v1>>v2;
		
		int i=LocateVex(G,v1),j=LocateVex(G,v2);//iΪ��ʼ�ڵ㣬jΪ�ն˽�� 
		int k=Path[i][j];//kΪ�м��� 
	    Show_shortestPath(G,i,j,Path,k);
	    cout<<v2<<": "<<D[i][j]<<'\n';
}

void ShortestPath_Floyd(AMGraph G)
{
	//��Floyd�㷨������ͼG�и��Զ���i��j֮������·��
	 //��ǰ���·��������vj��ǰһ����ţ���Dijkstra ��Դ��v0�̶������õ�һά���� 
	int **Path=new int*[G.vexnum];
	 //��¼��ǰ����vi��vj�����·������ 
	int **D=new int*[G.vexnum];
	for(int i=0;i<G.vexnum;i++)
	{
		Path[i]=new int;
		D[i]=new int;
	}		
	 
	 for(int i=0;i<G.vexnum;i++)//���Զ���֮���ʼ��֪·���Լ����� 
	 for(int j=0;j<G.vexnum;j++)
	 {
	 	if(i==j)//�Խ���Ϊ0������������ 
	 	D[i][j]=0;
	 	else
	 	D[i][j]=G.arcs[i][j];
	 	
	 	if(D[i][j]<MaxInt && (i!=j))//�Խ���Ϊ0����������	
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
