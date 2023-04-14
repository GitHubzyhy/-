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
void Show_shortestPath(AMGraph G,int i,int k,int *Path)//���õݹ����·�� 
{
	if(k==-1)
	{cout<<"û�����·��,����������\n"<<endl;return;}
	if(k!=i)//ǰ�����ܵ�������� 
		Show_shortestPath(G,i,Path[k],Path);

	cout<<G.vexs[k]<<"-->";
		
}
void print(AMGraph G,bool S[],int Path[],int D[])//���·����� 
{
	for(int i=0;i<G.vexnum;i++)
	cout<<'\t'<<"v="<<i<<" ";
	cout<<"\nS"<<"       ";
	
	for(int i=0;i<G.vexnum;i++)//S������� 
	{
	cout<<S[i]<<"\t";
	}
	cout.put('\n');
	
	cout<<'D'<<"       ";
	for(int i=0;i<G.vexnum;i++)//D�������
	{
			if(D[i]==MaxInt)//Ϊ����ֵ��ʱ������Ǹ����� 
			cout<<"��"<<'\t';
			else
			cout<<D[i]<<'\t';
	} 
	cout.put('\n');
	
	cout<<"Path"<<"   ";
	for(int i=0;i<G.vexnum;i++)//Path�������
	{
		cout<<Path[i]<<'\t';
	}		
	cout.put('\n');cout.put('\n');
	
} 

void ShortestPath_DIJ(AMGraph G,int v0)//�����·��
{//��Dijkstra�㷨��������Gv0���㵽���ඥ������·�� 

	//��¼��Դ�㵽�յ�vi�Ƿ��ѱ�ȷ�����·������
	bool *S=new bool[G.vexnum];
	//��¼��Դ��v0���յ�vi�ĵ�ǰ���·��vi��ֱ��ǰ����� �޻���Ϊ-1 
	int *Path=new int[G.vexnum];
	//��¼ ��Դ��v0���յ�vi�ĵ�ǰ���·������ �޻���Ϊ����ֵ 
	int *D=new int[G.vexnum];
	
	for(int v=0;v<G.vexnum;v++)//n���������γ�ʼ�� 
	{
		S[v]=false;//S��ʼ��Ϊ�ռ�
		D[v]=G.arcs[v0][v];//��ʼ��Ϊv0�ĸ����ڽӵıߵ�Ȩֵ
		
		if(D[v]<MaxInt)//���Ǽ���ֵ
		Path[v]=v0;//��¼ǰ���������� 
		else Path[v]=-1; 
	}
	
	S[v0]=true;//�Ѿ�ȷ�����·������
	D[v0]=0;//v0��v0�ľ���Ϊ0
	cout<<"S:    �� Դ �� v0 �� �� �� vi �� �� �� �� ȷ �� �� �� · �� �� ��\nD:    �� ¼ �� Դ �� �� �� �� �� ǰ �� �� · �� �� �� \nPath: �� ¼ �� Դ �� v0 �� �� �� vi �� ǰ �� �� · �� �� vi �� ֱ �� ǰ �� �� �� �� ��\n";
	print(G,S,Path,D);//��� 

/*-----��ʼ����������ʼ��ѭ����ÿһ�����v0��ĳ������v�����·������v���뵽S����-----------*/
	for(int i=1;i<G.vexnum;i++)//������n-1�����㣬���ν��м��� 
	{
	int min=MaxInt,v;//��ʼֵΪ����ֵ
		
		for(int w=0;w<G.vexnum;w++)
		{
			if(!S[w]&&D[w]<min)
			{v=w,min=D[w];}//ѡ��һ����ǰ���·�����յ���v 
		}
		
	S[v]=true;//�ҵ������·������v����S 
	for(int w=0;w<G.vexnum;w++)
	{
		//û��ȷ�����·�����¼���Ľ����Ϊ�м�����·��С��ԭ����·���͸��� 
		if(!S[w]&&(D[v]+G.arcs[v][w]<D[w]))
		{//���� 
			D[w]=D[v]+G.arcs[v][w];
			Path[w]=v;
		}
	}
	
	print(G,S,Path,D);//��� 	
	} //for
	
    cout<<"��������Ҫ��ѯ�����·�� �յ㶥�� \n";
	VertexType vj;
	cin>>vj;
	
	int i=LocateVex(G,vj);//iΪ��ʼ�ڵ�
	int k=Path[i];	//Ϊǰ����� 
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
/*�������� 
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
