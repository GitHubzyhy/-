#include<bits/stdc++.h>

#define MaxInt 32767//��ʾȨ�ļ���ֵ
#define MvNum 100///��󶥵���

using namespace std;

typedef char VerTexType;
typedef int ArcType; 
typedef struct//�������Ľṹ 
{
	VerTexType vexs[MvNum];//�����
	ArcType arcs[MvNum][MvNum];//�ڽӾ���
	int vexnum,arcnum;//ͼ�Ķ���ͻ������� 
}AMGraph;

int LocateVex(AMGraph G,VerTexType U)//�ڶ�����в���U���ڶ�����е��±����
{
	for(int i=0;i<G.vexnum;i++)
	{
		if(G.vexs[i]==U)
		return i;
	}
	
	return -1;//û���ҵ��� 
} 

void CreateUDN(AMGraph &G)
{
	int i,j;//Ϊ������ҷ��� 
	VerTexType v1,v2;//����
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
		i=LocateVex(G,v1),j=LocateVex(G,v2);	if(i==-1||j==-1){std::cout<<"����λ��δ�ҵ�\n",--k;continue;}//û�ҵ�����ѭ������ 
		G.arcs[i][j]=w;
		G.arcs[j][i]=w;//���������ǶԳƵ� 
	}
}

void ShowpGraph(AMGraph G)
{
	cout<<"�ڽӾ���Ϊ��\n   ";
	for(int i=0;i<G.vexnum;i++)//�������� 
	cout<<G.vexs[i]<<"    ";
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

struct lowcost_Vode//���ڼ�¼U��V-U������СȨֵ�ı� ��� 
{
	VerTexType adjvex;// ��С����U���Ǹ����㣬����� 
	ArcType lowcost;//��С�ߵ�Ȩֵ 
};

int mins=MaxInt;//��СȨֵ ��ʼ����mins��� 
int MIN(AMGraph G,struct lowcost_Vode * closedge)//ѡ��Ȩֵ��С
{
	int index=0;
	
	for(int i=0;i<G.vexnum;i++)
	if(closedge[i].lowcost!=0&&closedge[i].lowcost<mins)//lowcostΪ0��ʾ��ǰ������뵽��U,��Ҳ�ŵ�TE 
	{
	mins=closedge[i].lowcost;
	index=i;	
	}
	return index;
} 

void print(AMGraph G,struct lowcost_Vode *closedge)//������������������СȨֵ 
{
	 cout<<"�������飺";
	 for(int j=0;j<G.vexnum;j++)
	  	cout<<	closedge[j].lowcost<<" ";
		cout<<'\n';
}

void MiniSpanTree_Prim(AMGraph G,VerTexType u)
{
	//������G���ڽӾ���洢���Ӷ���u��������G����С������T�����T�ĸ�����
	 int k=LocateVex(G,u);
	 VerTexType u0,v0;//�ߵ��������� 
	
	 //��¼U��������V-U��Ȩֵ 
	 struct lowcost_Vode *closedge=new(nothrow) lowcost_Vode[G.vexnum];
	 
	 for(int j=0;j<G.vexnum;j++)//��ʼ��closedge����Ϊu�ڽӵıߵ�Ȩֵ 
	 if(j!=k)//����û�б� 
	 {
	 	closedge[j]={u,G.arcs[k][j]};//��Ҫ��������������
	 	cout<<	closedge[j].lowcost<<" ";
	 }
	  	
	 closedge[k].lowcost=0;//��ʼ����U={u}
	 cout<<"\n����㿪ʼ����С������\n\n";
	 for(int i=1;i<G.vexnum;i++)//ѡ������n-1������,����n-1���ߣ�u0�Ѿ���U������ 
	 {
	 	print(G,closedge);
	 	mins=MaxInt;//��Ϊmins��ȫ�ֱ���
		  
	 	k=MIN(G,closedge);//�ҵ���СȨֵ�ߵĶ�������  
	 	u0=closedge[k].adjvex;//u0Ϊ��С�ߵ�һ�����㣬u0����U 
	 	v0=G.vexs[k];//v0Ϊ��С�ߵ�����һ�����㣬v0����V-U �ڽӾ���ʽ���� 
	 	cout<<"("<<u0<<"-->"<<v0<<")mins: "<<mins<<"\n\n";//�����ǰ��С��(u0,v0)
		closedge[k].lowcost=0;//��k�����㲢��U������Ҳ������TE 
		for(int j=0;j<G.vexnum;j++)
		{
			if(G.arcs[k][j]<closedge[j].lowcost)//�¶��㲢��U������ѡ����С�ߣ��滻1: ԭ���޷�����ļ���ֵ ��2: ��ԭ��С�ı� 
			closedge[j]={G.vexs[k],G.arcs[k][j]};//�滻����Ȩֵ��� 
		} 
	 } 
	 	print(G,closedge);
	/*�ұߵ�ʱ�������Ѿ�������С�����������е���صı���[Ȩ��С] �����Ҹ���ĵ�*/
}

int main()
{	
	AMGraph G;
	CreateUDN(G);
	ShowpGraph(G);//����ڽӾ���	
	MiniSpanTree_Prim(G,'1'); //�����С������ 
	
	return 0;
}
/*��������ֱ��cv�����п��  
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
�𰸣�
�������飺0 6 1 5 32767 32767
(1-->3)mins: 1

�������飺0 5 0 5 6 4
(3-->6)mins: 4

�������飺0 5 0 2 6 0
(6-->4)mins: 2

�������飺0 5 0 0 6 0
(3-->2)mins: 5

�������飺0 0 0 0 3 0
(2-->5)mins: 3

�������飺0 0 0 0 0 0*/
