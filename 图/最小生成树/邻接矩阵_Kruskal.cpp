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
	for(int i=0;i<G.vexnum;i++){
		if(G.vexs[i]==U)
		return i;
	}
	return -1;//û���ҵ��� 
} 

class Edges//�洢�ߵ���Ϣ 
{
public:
	VerTexType Head;//�ߵ���ʼ��
	VerTexType Tail;//�ߵ��յ�
	ArcType lowcost;//���ϵ�Ȩֵ 
};

void CreateUDN(AMGraph &G,Edges *&Edge)
{
	int i,j;//Ϊ������ҷ��� 
	VerTexType v1,v2;//����
	ArcType w;//Ȩֵ 
	cout<<"�����������������ж��ٸ����� �ͻ�\n";
	
	cin>>G.vexnum>>G.arcnum;
	Edge=new(std::nothrow) Edges[G.arcnum];
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
		Edge[k].Head=v1,Edge[k].Tail=v2,Edge[k].lowcost=w;//�洢�ߵ���Ϣ 
		i=LocateVex(G,v1),j=LocateVex(G,v2);	if(i==-1||j==-1){std::cout<<"����λ��δ�ҵ�\n",--k;continue;}//û�ҵ�����ѭ������ 
		G.arcs[i][j]=w;
		G.arcs[j][i]=w;//���������ǶԳƵ� 
	}
}


void MiniSpanTree_Kruskal(AMGraph &G)
{//������G���ڽӾ�����ʽ�洢������G����С������T�����T�ĸ�����
	Edges *Edge=nullptr;//Edge��洢�ߵ���Ϣ 
	CreateUDN(G,Edge);
	
	//������Edge�е�Ԫ�ذ���Ȩֵ��С�������� 
	sort(Edge,Edge+G.arcnum,[](Edges a,Edges b){return a.lowcost<b.lowcost;});
	
	//���������ʶ����������������ͨ������Ϊ���治���γɻ��������� 
	ArcType *Vexset=new(nothrow) ArcType[G.vexnum],vs1,vs2;
	for(int i=0;i<G.vexnum;i++)
	Vexset[i]=i;//��ʼ�����������Գ�һ����ͨ����
	
	for(int i=0;i<G.arcnum;i++)//���β鿴����Edge�еı� 
	{
		int v1,v2; 
		v1=LocateVex(G,Edge[i].Head);//v1Ϊ�ߵ�ʼ��head���±�
		v2=LocateVex(G,Edge[i].Tail);//v2Ϊ���յ�Tail���±�
		vs1=Vexset[v1],vs2=Vexset[v2];
		
		if(vs1!=vs2)//��ʼ�㲻�����յ�˵�������ڻ� 
		{
			cout<<Edge[i].Head<<"-->"<<Edge[i].Tail<<": "<<Edge[i].lowcost<<'\n';//����α�
			
			for(int j=0;j<G.vexnum;j++)//�ϲ���������������������ͳһ���
			{
				if(Vexset[j]==vs2) 
				Vexset[j]=vs1;
			}
			
		} //if
	}//for 
}

int main()
{
	AMGraph G;
	MiniSpanTree_Kruskal(G);
	
	return 0;
}
/*
�������ݣ� 
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
1-->3: 1
6-->4: 2
2-->5: 3
3-->6: 4
2-->3: 5
*/
