#include <stdio.h>
#include <stdlib.h>
/*
文件名称：最短路径Floyd算法
时间;2015-1-29 22:14
说明：最短路径Floyd算法 
*/ 


#define OK (1)
#define ERROR (0)
#define TRUE (1)
#define FALSE (0)

#define MAXVEX (9)
#define INFINITY (655325)/*将无穷大定义为655325*/

typedef int Bool;
typedef char VertexType;/*定义顶点类型*/ 
typedef int EdgeType;/*定义边上权值类型类型*/

/*定义图结构*/
typedef struct
{
	VertexType vertexs[MAXVEX];/*顶点表*/
	EdgeType arc[MAXVEX][MAXVEX];/*领结矩阵*/ 
	int numVertexs;/*顶点数*/
	int numEdges;/*边数*/
}MGraph;

typedef int Patharc[MAXVEX][MAXVEX];/* 用于存储最短路径前驱的矩阵数组 ,，Patharc[V0][V]表示从指定结点vo到v的最短路径的前驱*/
typedef int ShortPathTable[MAXVEX][MAXVEX]; /* 用于存储到各点最短路径的权值和的矩阵 数组*/


/*创建一个图*/
void GreateMGraph(MGraph *G)
{
	int i=0,j=0;
	
	G->numVertexs=9;
	G->numEdges=16;
	
	/*初始化图的顶点表*/	
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
	
	/*初始化图的领接矩阵*/
	for(i=0;i<G->numVertexs;i++)
	{
		for(j=0;j<G->numVertexs;j++)
		{
			if(i==j)
				G->arc[i][j]=0;
			else
				{
					G->arc[i][j]=INFINITY;/*首先将领结矩阵中各边的权值设置为无穷大*/
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
函数名称：ShortestPath_Dijkstra(MGrapth G,int V0,Patharc *P,ShortPathTable *D)
函数参数：G-----------由领接矩阵创建的图
		  V0------ ---起点
		  P-----------指向二维整型数组的指针，最短路径前驱矩阵数组，用于表示VO到顶点V最短路径的前驱
		  D-----------指向二维整型数组的指针，最短路径矩阵数组，用于表示VO到顶点V最短路径
函数说明：求最短路径的 Dijkstra算法 
*/
void ShortestPath_Floyd(MGraph G,Patharc *P,ShortPathTable *D)
{
	int i=0,j=0,k=0;
 

 	int point;
 	
 	for(i=0;i<G.numVertexs;i++)
 	{
		for(j=0;j<G.numVertexs;++j)
		{
			(*D)[i][j]=G.arc[i][j];/*初始化最短路径矩阵数组*/
			(*P)[i][j]=j;/*初始化最短路径前驱数组*/
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


Bool visited[MAXVEX];/*访问标志组*/

/* 邻接矩阵的深度优先递归算法 */
void DFS(MGraph G,int i)
{
	int j=0;
	if(visited[i]!=TRUE)/*当顶点还未被访问过时开始访问该顶点*/
	{
		visited[i]=TRUE;/*将访问标志置为TRUE*/
		printf("%d ",G.vertexs[i]);/*进行访问操作*/
		
		for(j=0;j<G.numVertexs;j++)
		{   /*访问与该顶点领接的顶点*/
			if((G.arc[i][j]!=INFINITY)&&(visited[j]!=TRUE))
			{
				DFS(G,j);	
			}	
		}
			
	} 
}

/* 邻接矩阵的深度遍历操作 */
void DFSTraverse(MGraph G)
{
	int i=0;
	
	for(i=0;i<G.numVertexs;i++)/*初始化将访问标志组置为FALSE*/
		visited[i]=FALSE;
		
	for(i=0;i<G.numVertexs;i++)
		DFS(G,i);
}

int main(int argc, char *argv[]) 
{	
	int i,j,k;
	int V0;/*定义起点*/	
	Patharc P;
	ShortPathTable D;
	
	MGraph G;
	GreateMGraph(&G);
	printf("\n对图进行DFS深度优先遍历:\n");
	DFSTraverse(G);
	

	
	 
	V0=G.vertexs[0];
	
	ShortestPath_Floyd(G,&P,&D);
	printf("\n各个顶点之间的最短路径:\n"); 
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
	printf("\n最短路径前驱矩阵数组:\n");
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
