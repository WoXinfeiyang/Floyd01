#include <stdio.h>
#include <stdlib.h>
/*
�ļ����ƣ����·��Floyd�㷨
ʱ��;2015-1-29 22:14
˵�������·��Floyd�㷨 
*/ 


#define OK (1)
#define ERROR (0)
#define TRUE (1)
#define FALSE (0)

#define MAXVEX (9)
#define INFINITY (655325)/*���������Ϊ655325*/

typedef int Bool;
typedef char VertexType;/*���嶥������*/ 
typedef int EdgeType;/*�������Ȩֵ��������*/

/*����ͼ�ṹ*/
typedef struct
{
	VertexType vertexs[MAXVEX];/*�����*/
	EdgeType arc[MAXVEX][MAXVEX];/*������*/ 
	int numVertexs;/*������*/
	int numEdges;/*����*/
}MGraph;

typedef int Patharc[MAXVEX][MAXVEX];/* ���ڴ洢���·��ǰ���ľ������� ,��Patharc[V0][V]��ʾ��ָ�����vo��v�����·����ǰ��*/
typedef int ShortPathTable[MAXVEX][MAXVEX]; /* ���ڴ洢���������·����Ȩֵ�͵ľ��� ����*/


/*����һ��ͼ*/
void GreateMGraph(MGraph *G)
{
	int i=0,j=0;
	
	G->numVertexs=9;
	G->numEdges=16;
	
	/*��ʼ��ͼ�Ķ����*/	
	/*
	G->vertexs[0]='A';
	G->vertexs[1]='B';
	G->vertexs[2]='C';
	G->vertexs[3]='D';
	G->vertexs[4]='E';
	G->vertexs[5]='F';
	G->vertexs[6]='G';
	G->vertexs[7]='H';
	G->vertexs[8]='I';
	*/
	for(i=0;i<G->numVertexs;i++)
	{
		G->vertexs[i]=i;	
	} 
	
	/*��ʼ��ͼ����Ӿ���*/
	for(i=0;i<G->numVertexs;i++)
	{
		for(j=0;j<G->numVertexs;j++)
		{
			if(i==j)
				G->arc[i][j]=0;
			else
				{
					G->arc[i][j]=INFINITY;/*���Ƚ��������и��ߵ�Ȩֵ����Ϊ�����*/
				}	
		}	
	}
	
	G->arc[0][1]=1;
	G->arc[0][2]=5; 
	G->arc[1][2]=3; 
	G->arc[1][3]=7; 
	G->arc[1][4]=5; 

	G->arc[2][4]=1; 
	G->arc[2][5]=7; 
	G->arc[3][4]=2; 
	G->arc[3][6]=3; 
	G->arc[4][5]=3;

	G->arc[4][6]=6;
	G->arc[4][7]=9; 
	G->arc[5][7]=5; 
	G->arc[6][7]=2; 
	G->arc[6][8]=7;

	G->arc[7][8]=4;
	
	
	for(i=0;i<G->numVertexs;i++)
	{
		for(j=i;j<G->numVertexs;j++)
		{
			G->arc[j][i]=G->arc[i][j];	
		}	
	}
}


/*
�������ƣ�ShortestPath_Dijkstra(MGrapth G,int V0,Patharc *P,ShortPathTable *D)
����������G-----------����Ӿ��󴴽���ͼ
		  V0------ ---���
		  P-----------ָ���ά���������ָ�룬���·��ǰ���������飬���ڱ�ʾVO������V���·����ǰ��
		  D-----------ָ���ά���������ָ�룬���·���������飬���ڱ�ʾVO������V���·��
����˵���������·���� Dijkstra�㷨 
*/
void ShortestPath_Floyd(MGraph G,Patharc *P,ShortPathTable *D)
{
	int i=0,j=0,k=0;
 

 	int point;
 	
 	for(i=0;i<G.numVertexs;i++)
 	{
		for(j=0;j<G.numVertexs;++j)
		{
			(*D)[i][j]=G.arc[i][j];/*��ʼ�����·����������*/
			(*P)[i][j]=j;/*��ʼ�����·��ǰ������*/
		}
	}

	
 	for(k=0;k<G.numVertexs;k++)
 	{
		for(i=0;i<G.numVertexs;i++)
		{
			for(j=0;j<G.numVertexs;j++)
			{
				if((*D)[i][j]>((*D)[i][k]+(*D)[k][j]))
				{
					(*D)[i][j]=((*D)[i][k]+(*D)[k][j]);
					(*P)[i][j]=(*P)[i][k];
				}	
			}
		}	
	}
}


Bool visited[MAXVEX];/*���ʱ�־��*/

/* �ڽӾ����������ȵݹ��㷨 */
void DFS(MGraph G,int i)
{
	int j=0;
	if(visited[i]!=TRUE)/*�����㻹δ�����ʹ�ʱ��ʼ���ʸö���*/
	{
		visited[i]=TRUE;/*�����ʱ�־��ΪTRUE*/
		printf("%d ",G.vertexs[i]);/*���з��ʲ���*/
		
		for(j=0;j<G.numVertexs;j++)
		{   /*������ö�����ӵĶ���*/
			if((G.arc[i][j]!=INFINITY)&&(visited[j]!=TRUE))
			{
				DFS(G,j);	
			}	
		}
			
	} 
}

/* �ڽӾ������ȱ������� */
void DFSTraverse(MGraph G)
{
	int i=0;
	
	for(i=0;i<G.numVertexs;i++)/*��ʼ�������ʱ�־����ΪFALSE*/
		visited[i]=FALSE;
		
	for(i=0;i<G.numVertexs;i++)
		DFS(G,i);
}

int main(int argc, char *argv[]) 
{	
	int i,j,k;
	int V0;/*�������*/	
	Patharc P;
	ShortPathTable D;
	
	MGraph G;
	GreateMGraph(&G);
	printf("\n��ͼ����DFS������ȱ���:\n");
	DFSTraverse(G);
	

	
	 
	V0=G.vertexs[0];
	
	ShortestPath_Floyd(G,&P,&D);
	printf("\n��������֮������·��:\n"); 
	for(i=0;i<G.numVertexs;i++)
	{
		for(j=i+1;j<G.numVertexs;j++)
		{
			printf("\nV%d--V%d weight:%2d, path: ",i,j,D[i][j]);
			k=P[i][j];
			printf("%2d ",i);
			while(k!=j)
			{
				printf("->%2d ",k);
				k=P[k][j];
			}
			printf("->%2d ",j);	
		}
		printf("\n");
	}
	printf("\n���·��ǰ����������:\n");
	for(i=0;i<G.numVertexs;i++)
	{
		for(j=0;j<G.numVertexs;j++)
		{
			printf("%2d ",P[i][j]);	
		}
		printf("\n");	
	}
	
	return 0;
}
