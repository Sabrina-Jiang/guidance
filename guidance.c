#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
// #include <windows.h>  /* 调用system函数的头文件 */
#define Max 20000
#define TRUE 1
#define FALSE 0

typedef struct ArcCell{
 int adj;  /*相邻接的景点之间的路程 adj为权值*/ 
}ArcCell;   /* 定义 边 的类型 邻接矩阵 */

typedef struct VertexType{
 int number;  /* 景点编号 */
 char sight[100];  /* 景点名称 */
 char description[1000]; /* 景点简述 */
 char elaborate[1000]; /*景点详述*/
}VertexType;   /* 定义 顶点 的类型 */

typedef struct{
 VertexType vex[20]; /* 图中的顶点,即为景点 */
 ArcCell arcs[20][20]; /* 图中的边,即为景点间的距离 */
 int vexnum,arcnum; /* 顶点数,边数 */
}MGraph;   /* 定义 图 的类型 */

MGraph G;   /* 把图定义为全局变量 */
char nameofschool[100];
int NUM=9;
int P[20][20];  /*P[v][w] w是从v0到v的最短路径上的顶点  */
int p[20];/*全局数组,用来存放路径上的各顶点*/
int visited[20];/*全局数组,用来记录各顶点被访问的情况*/
int a=0;/*全局变量,用来记录每对顶点之间的所有路径的条数*/
long int D[20];  /* 辅助变量存储最短路径长度 */
void CreateUDN(int v,int a); /* 造图函数 */
void narrate();   /*说明函数,输出菜单*/
void ShortestPath(int num); /*最短路径函数*/
void output(int sight1,int sight2); /*输出函数*/
char Menu();   /* 主菜单 */
void search();   /* 查询景点信息 */
char SearchMenu();  /* 查询子菜单 */
void Searchpath1(MGraph g);/*查询两个景点间的所有路径*/
void disppath(MGraph g,int i,int j);
void path(MGraph g,int i,int j,int k);/*确定路径上第k+1个顶点的序号*/
int Addnewsight(int n); /*添加新的景点和路径*/
int Deletesight(int n); /*删除景点和路径*/
void Changesight(); /*修改景点和路径*/
char Changemenu();  /*修改路径或顶点的选择菜单*/
char Sightmenu();  /*选择需该景点的菜单*/
void NewCreateUDN(); /*创建新的导游图*/

void main() /* 主函数 */
{ 
 int v0,v1;
 char ck;
 system("color f2");
 CreateUDN(NUM,11);
 do
 {  
  ck=Menu();
  switch(ck)
  {
  case '1':
   search();
   break;
  case '2':
   system("clear");  /*清屏函数*/
   narrate();
   printf("\n\n\t\t\t请选择起点景点(0～%d):",NUM-1);
   scanf("%d",&v0);
   printf("\t\t\t请选择终点景点(0～%d):",NUM-1);
   scanf("%d",&v1);
   ShortestPath(v0);  /* 计算两个景点之间的最短路径 */
   output(v0,v1);     /* 输出结果 */
   printf("\n\n\t\t\t\t请按任意键继续...\n");
   getchar();
   getchar();
   break;
  case '3':
   system("clear");
   narrate();
   Searchpath1(G);
   printf("\n\n\t\t\t\t请按任意键继续...\n");
   getchar();
   getchar();
   break;
  case'4':
	  system("clear");
	  narrate();
	  NUM=Addnewsight(NUM);
	  system("clear");
	  narrate();
	  break;
  case'5':
	  NUM=Deletesight(NUM);
	  break;
  case'6':
	  Changesight();
	  break;
  case'7':
      NewCreateUDN();
	  break;
  };
 }while(ck!='e'); 
}

char Menu()  /* 主菜单 */
{
 char c;
 int flag;
 do{
  flag=1;
 system("clear");
  narrate();
  printf("\n\t\t\t┏━━━━━━━━━━━━━━━┑\n");
  printf("\t\t\t┃                              ┃\n");
  printf("\t\t\t┃      1、查询景点信息         ┃\n");
  printf("\t\t\t┃      2、查询两景点间最短路径 ┃\n");
  printf("\t\t\t┃      3、查询两景点间所有路线 ┃\n");
  printf("\t\t\t┃      4、添加新的景点和路径   ┃\n");
  printf("\t\t\t┃      5、删除已有景点和路径   ┃\n");
  printf("\t\t\t┃      6、修改已有景点和路径   ┃\n");
  printf("\t\t\t┃      7、创建新的校园导游图   ┃\n");
  printf("\t\t\t┃      e、退出                 ┃\n");
  printf("\t\t\t┃                              ┃\n");
  printf("\t\t\t┗━━━━━━━━━━━━━━━┛\n");
  printf("\t\t\t\t请输入您的选择:");
  scanf("%c",&c);
  if(c=='1'||c=='2'||c=='3'||c=='4'||c=='5'||c=='6'||c=='7'||c=='e')
   flag=0;
 }while(flag);
 return c;
}

char SearchMenu()  /* 查询子菜单 */
{
 char c;
 int flag;
 do{
  flag=1;
  system("clear");
  narrate();
  printf("\n\t\t\t┏━━━━━━━━━━━━━━━┑\n");
  printf("\t\t\t┃                              ┃\n");
  printf("\t\t\t┃      1、按照景点编号查询     ┃\n");
  printf("\t\t\t┃      2、按照景点名称查询     ┃\n");
  printf("\t\t\t┃      e、返回                 ┃\n");
  printf("\t\t\t┃                              ┃\n");
  printf("\t\t\t┗━━━━━━━━━━━━━━━┛\n");
  printf("\t\t\t\t请输入您的选择:");
  scanf("%c",&c);
  if(c=='1'||c=='2'||c=='e')
   flag=0;
 }while(flag);
 return c;
}

void search()  /* 查询景点信息 */
{
 int num;
 int i;
 char c;
 char name[20]; 
 do
 {
  system("clear");
  c=SearchMenu();
  switch (c)
  {
  case '1':  
   system("clear");
 narrate();
   printf("\n\n\t\t请输入您要查找的景点编号:");
   scanf("%d",&num);
   for(i=0;i<NUM;i++)
   {
    if(num==G.vex[i].number)
    {
     printf("\n\n\t\t\t您要查找景点信息如下:");
     printf("\n\n\t%-25s\n\n",G.vex[i].elaborate); /*-表示左对齐 25表示所占字符宽度*/
     printf("\n\t\t\t按任意键返回...");
     getchar();
     getchar();
     break;
    }
   }
   if(i==NUM)
   {
    printf("\n\n\t\t\t没有找到！");
    printf("\n\n\t\t\t按任意键返回...");
    getchar();
    getchar();
   }
   break;
  case '2':
   system("clear");
   narrate();
   printf("\n\n\t\t请输入您要查找的景点名称:");
   scanf("%s",name);
   for(i=0;i<NUM;i++)
   {
    if(!strcmp(name,G.vex[i].sight))
    {
     printf("\n\n\t\t\t您要查找景点信息如下:");
     printf("\n\n\t%-25s\n\n",G.vex[i].elaborate);  /*-表示左对齐 25表示所占字符宽度*/
     printf("\n\t\t\t按任意键返回...");
     getchar();
     getchar();
     break;
    }
   }
   if(i==NUM)
   {
    printf("\n\n\t\t\t没有找到！");
    printf("\n\n\t\t\t按任意键返回...");
    getchar();
    getchar();
   }
   break;
  }
 }while(c!='e');
}

void CreateUDN(int v,int a) /* 造图函数 */
{ 
 int i,j;/* 邻接矩阵的行数,列数*/
 strcpy(nameofschool,"天津师范大学");
 G.vexnum=v;  /* 初始化结构中的景点数和边数 */
 G.arcnum=a;

 for(i=0;i<G.vexnum;++i) G.vex[i].number=i; /* 初始化每一个景点的编号 */

 /* 初始化每一个景点名及其景点描述 */
 
 strcpy(G.vex[0].sight,"秋水湖 ");
 strcpy(G.vex[0].description,"师大特色湖(北门旁)");
 strcpy(G.vex[0].elaborate,"师大风景独好的地方，为师大增添水的美。（临近北门）");
 strcpy(G.vex[1].sight,"图书馆");
 strcpy(G.vex[1].description,"亚洲著名图书馆(秋水湖旁)");
 strcpy(G.vex[1].elaborate,"作为学子奋苦的地方，这里庄严。临近秋水湖，使图书馆成为了另类的观光楼。（秋水湖旁）");
 strcpy(G.vex[2].sight,"音乐厅");
 strcpy(G.vex[2].description,"艺术的殿堂。(图书馆旁)");
 strcpy(G.vex[2].elaborate,"这里经常有着艺术学院表演，给学校勾勒了艺术的音符。（图书馆东南200米）");
 strcpy(G.vex[3].sight,"体育馆");
 strcpy(G.vex[3].description,"室内比赛场地(音乐厅旁)");
 strcpy(G.vex[3].elaborate,"这里周围的体育场地，让学校变得朝气蓬勃。（音乐厅以西150米）");
 strcpy(G.vex[4].sight,"时间广场");
 strcpy(G.vex[4].description,"教学区的中心(图书馆旁)");
 strcpy(G.vex[4].elaborate,"广场周围就是教学区。（图书馆以南200米）");
 strcpy(G.vex[5].sight,"钢笔尖");
 strcpy(G.vex[5].description,"是师大的一大标志。");
 strcpy(G.vex[5].elaborate,"同学们去教学区，大多都要经过钢笔尖，这里不仅意味着学生的勤谨，也是师大的一大标志。（时间广场以西200米）");
 strcpy(G.vex[6].sight,"风雨操场");
 strcpy(G.vex[6].description,"师大最大的操场");
 strcpy(G.vex[6].elaborate,"是新生迎新场地，运动会场地，军训阅兵场地等。（大型体育广场以西）");
 strcpy(G.vex[7].sight,"西门");
 strcpy(G.vex[7].description,"师大人流量最大的地方");
 strcpy(G.vex[7].elaborate,"师大人流量最大的，除了教学楼，就是西门了。交通便利。");
 strcpy(G.vex[8].sight,"北门");
 strcpy(G.vex[8].description,"师大的正门");
 strcpy(G.vex[8].elaborate,"作为师大门面的北门，简约大气的大门，体现师大的精神面貌。是自驾车出入师大唯一通道。");
 
 /* 初始化每一对顶点之间的距离。这里把所有的边假定为20000,含义是这两个景点之间是不可到达 */
 for(i=0;i<20;++i)
  for(j=0;j<20;++j) 
   G.arcs[i][j].adj=Max;
  
   /*
   
     下边是可直接到达的景点间的距离,由于两个景点间距离是互相的,
     所以要对图中对称的边同时赋值。
     
  */
  G.arcs[0][1].adj=G.arcs[1][0].adj=50;
  G.arcs[1][2].adj=G.arcs[3][1].adj=200;
  G.arcs[2][3].adj=G.arcs[3][0].adj=300;
  G.arcs[1][4].adj=G.arcs[4][1].adj=200;
  G.arcs[3][4].adj=G.arcs[4][2].adj=200;
  G.arcs[2][4].adj=G.arcs[5][3].adj=100;
  G.arcs[3][6].adj=G.arcs[2][5].adj=25;
  G.arcs[5][4].adj=G.arcs[6][4].adj=200;
  G.arcs[5][6].adj=G.arcs[7][4].adj=250;
  G.arcs[5][7].adj=G.arcs[7][2].adj=250;
  G.arcs[0][5].adj=G.arcs[8][7].adj=200;
  G.arcs[0][8].adj=G.arcs[8][7].adj=400;
}

void narrate() /* 说明函数 */
{
 int i,k=0;
 printf("\n\t***************欢迎使用%s校园导游程序**************\n",nameofschool);
 printf("\t__________________________________________________________________\n");
 printf("\t\t景点名称\t\t\t\t景点描述\t\t\t\n");
 printf("\t________________________________|_________________________________\n");
 for(i=0;i<NUM;i++)
 {
  printf("\t%c (%2d)%-10s\t\t|\t%-25s%c\n",2,i,G.vex[i].sight,G.vex[i].description,3); /* 输出景点列表 %输出字符串–表示左对齐 10表示所占字符宽度 s表示按字符串输出 */
  k=k+1;
 }
 printf("\t________________________________|_________________________________\n");
}

void ShortestPath(int num) /* 迪杰斯特拉算法最短路径函数 num为入口点的编号 */
/*若P[w][v]为TRUE，则w是从num到v当前求得最短路径上的顶点 */
{ 
 int v,w,i,t;  /* i、w和v为计数变量 */
 int final[20]; /*final[v]=TRUE表示v属于S集合*/
 int min;
 for(v=0;v<NUM;v++)
 {
  final[v]=FALSE;  /* 假设从顶点num到顶点v没有最短路径 */
  D[v]=G.arcs[num][v].adj;/* 将与之相关的权值放入D中存放 */
  for(w=0;w<NUM;w++) /* 设置为空路径 */
   P[v][w]=FALSE;
  if(D[v]<20000)  /* 存在路径 */
  {
   P[v][num]=TRUE; 
   P[v][v]=TRUE; 
  }
 }
 D[num]=0;
 final[num]=TRUE;      /* 初始化num顶点属于S集合 */
 /* 开始主循环,每一次求得num到某个顶点的最短路径,并将其加入到S集合 */
 for(i=0;i<NUM;++i)     /* 其余G.vexnum-1个顶点 */
 {
  min=Max;     /* 当前所知离顶点num的最近距离 */
  for(w=0;w<NUM;++w)
   if(!final[w])    /* w顶点在v-s中 */
    if(D[w]<min)   /* w顶点离num顶点更近 D[w]为num到w的最短路径长度 */
    {
     v=w;
     min=D[w];
    } 
    final[v]=TRUE;   /* 离num顶点更近的v加入到s集合 */
    for(w=0;w<NUM;++w)  /* 更新当前最短路径极其距离 */
     if(!final[w]&&((min+G.arcs[v][w].adj)<D[w]))/* 不在s集合,并且比以前所找到的路径都短就更新当前路径 */
     {
      D[w]=min+G.arcs[v][w].adj;
      for(t=0;t<NUM;t++)
       P[w][t]=P[v][t];/*以便于之后的循环赋值*/
      P[w][w]=TRUE;
     }
 }
}

void output(int sight1,int sight2)    /* 输出函数 */
{
 int a,b,c,d,q=0;
 a=sight2;    /* 将景点二赋值给a */
 if(a!=sight1)    /* 判断景点一和景点二是否重合 */
 {
  printf("\n\t从%s到%s的最短路径是",G.vex[sight1].sight,G.vex[sight2].sight);/* 输出提示信息 */ 
  printf("\t(最短距离为 %dm.)\n\n\t",D[a]);  /* 输出sight1到sight2的最短路径长度,存放在D[]数组中 */
  printf("\t%s",G.vex[sight1].sight);   /* 输出景点一的名称 */
  d=sight1;      /* 将景点一的编号赋值给d */
  for(c=0;c<NUM;++c)
  {
gate:;        /* 标号,可以作为goto语句跳转的位置 */
     P[a][sight1]=FALSE;
     for(b=0;b<NUM;b++)
     {
      if(G.arcs[d][b].adj<20000&&P[a][b])  /* 如果景点一和它的一个临界点之间存在路径且顶点在最短路径上 */
      {
       printf("-->%s",G.vex[b].sight);  /* 输出此节点的名称 */
       q=q+1;     /* 计数变量加一,满8控制输出时的换行 */
       P[a][b]=0;
       d=b;     /* 将b作为出发点进行下一次循环输出,如此反复 */
       if(q%8==0) printf("\n");
       goto gate;/*无条件跳转*/
      }
     }
  }
 }
 
}

void Searchpath1(MGraph g)/*查询两个景点的编号*/
{
	int l=0;
	int k=0;
	int i,j;
	 printf("选择出发景点:");
	 scanf("%d",&i);
	 printf("选择目地景点:");
	 scanf("%d",&j);
	 for(;k<g.vexnum;k++)/*g.vexnumber表示网中的顶点个数*/
		 if(i==g.vex[k].number) i=k;/*在网中找到其编号与输入的出发景点的编号相同的顶点*/ 
		 for(;l<g.vexnum;l++)
			 if(j==g.vex[l].number) j=l;/*在网中找到其编号与输入的目地景点的编号相同的顶点*/ \
				 printf("\n从%s到%s的所有游览路径有:\n\n",g.vex[i].sight,g.vex[j].sight);/*输出出发景点和目地景点的名称*/
			 disppath(g,i,j);/*调用disppath函数,用来输出两个景点间的所有路径*/
}

void disppath(MGraph g,int i,int j)
{
	int k;
	p[0]=i;
	for(k=0;k<g.vexnum;k++)
		visited[i]=FALSE;/*初始化各顶点的访问标志位,即都为未访问过的*/
	a=0;/*初始化路径的条数*/
	path(g,i,j,0);/*通过调用path函数,找到从vi到vj的所有路径并输出*/
}

void path(MGraph g,int i,int j,int k)
/*确定路径上第k+1个顶点的序号*/
{
	int s;
	if(p[k]==j)/*当寻找到的顶点为j时即为找到一条路径*/
	{
		a++;/*路径的条数值加1*/
		printf("第%d条:\t",a);
		for(s=0;s<=k-1;s++)/*输出一条路径*/
		{
			printf("%s",g.vex[p[s]].sight);
			printf("->");
		}
		//cout<<g.vex[p[s]].sight;
		printf("%s\n",g.vex[p[s]].sight);                    
	}
	s=0;
	while(s<g.vexnum)
	{
		if(s!=i)/*保证路径中不再重复出现起点*/
		{
			if(g.arcs[p[k]][s].adj!=Max&&visited[s]==0)
				/*当vk与vs之间有边存在且vs未被访问过*/
			{
				visited[s]=1;/*置访问标志位为1,即已访问的*/
				p[k+1]=s;/*将顶点s加入到p数组中*/
                path(g,i,j,k+1);/*递归调用之*/
                visited[s]=0;/*重置访问标志位为0,即未访问的,以便该顶点能被重新使用*/
			}
		}
		s++;
	}
}

int Addnewsight(int n)
{
	int i;
	char sight[100],description[1000],elaborate[1000];
	int length;
		printf("请输入新景点的名称:\n");
		scanf("%s",&sight);
		printf("请输入新景点的简单介绍:\n");
		scanf("%s",&description);
		printf("请输入新景点的详细介绍:\n");
		scanf("%s",&elaborate);
		strcpy(G.vex[n].sight,sight);
	    strcpy(G.vex[n].description,description);
		strcpy(G.vex[n].elaborate,elaborate);
		G.vex[n].number=n;
		for(i=0;i<n;i++)/*依次添加新景点到每个景点的距离*/
		{   system("clear"); /* 清屏函数 */
            narrate(); 
			printf("请输入此景点到第%d个景点的距离(单位:m)(同一景点或不可到达用20000表示):\n",i);
			scanf("%d",&length);
			if(length!=20000)
				G.arcnum++;
			G.arcs[n][i].adj=G.arcs[i][n].adj=length;
		}
		n++;
		G.vexnum++;
	return n;
}

int Deletesight(int n)
{
	int i;
	int j;
	char c;
	int num;
	char name[20];
		system("clear");
        c=SearchMenu();
        switch (c)
		{
         case '1':  
			 system("clear");
             narrate();
             printf("\n\n\t\t请输入您要删除景点的编号:");
             scanf("%d",&num);
             for(i=0;i<NUM;i++)
			 {
				 if(num==G.vex[i].number)
				 {
					 for(j=0;j<NUM;j++)
					 {
						 if(G.arcs[i][j].adj!=20000)
							 G.arcnum--;
						 G.arcs[i][j].adj=G.arcs[j][i].adj=20000;
					 }
					
				 }
				}
			 for(;num<NUM;num++)/*后续景点向前移动*/
					{
						strcpy(G.vex[num].sight,G.vex[num+1].sight);
						strcpy(G.vex[num].description,G.vex[num+1].description);
					}
					 n--;
     printf("\n\t\t\t按任意键返回...");
     getchar();
     getchar();
     break;
   if(i==NUM)
   {
    printf("\n\n\t\t\t没有找到！");
    printf("\n\n\t\t\t按任意键返回...");
    getchar();
    getchar();
   }
   break;
  case '2':
   system("clear");
   narrate();
   printf("\n\n\t\t请输入您要删除景点的名称:");
   scanf("%s",name);
   for(i=0;i<NUM;i++)
   {
    if(!strcmp(name,G.vex[i].sight)) /*找到输入名称的景点编号*/
    {
		 num=i;
		 for(j=0;j<NUM;j++)
		 {
			if(G.arcs[i][j].adj!=20000)
			    G.arcnum--;
			G.arcs[i][j].adj=G.arcs[j][i].adj=20000;
		 }
	}
   }
   for(;num<NUM;num++)
		 {
			 strcpy(G.vex[num].sight,G.vex[num+1].sight);
			 strcpy(G.vex[num].description,G.vex[num+1].description);
		 }
		 n--;
     printf("\n\t\t\t按任意键返回...");
     getchar();
     getchar();
     break;
   if(i==NUM)
   {
    printf("\n\n\t\t\t没有找到！");
    printf("\n\n\t\t\t按任意键返回...");
    getchar();
    getchar();
   }
   break;
  }
		return n;
}

char Changemenu()
{
char c;
 int flag;/*判断输入是否正确*/
 do{
  flag=1;
  system("clear");
  narrate();
  printf("\n\t\t\t┏━━━━━━━━━━━━━━━┑\n");
  printf("\t\t\t┃                              ┃\n");
  printf("\t\t\t┃      1、修改景点信息         ┃\n");
  printf("\t\t\t┃      2、修改道路信息         ┃\n");
  printf("\t\t\t┃      e、返回                 ┃\n");
  printf("\t\t\t┃                              ┃\n");
  printf("\t\t\t┗━━━━━━━━━━━━━━━┛\n");
  printf("\t\t\t\t请输入您的选择:");
  scanf("%c",&c);
  if(c=='1'||c=='2'||c=='e')
   flag=0;
 }while(flag);
 return c;
}

char Sightmenu()
{
	char c;
	int flag;
	do{
		flag=1;
		system("clear");
        narrate();
  printf("\n\t\t\t┏━━━━━━━━━━━━━━━┑\n");
  printf("\t\t\t┃                              ┃\n");
  printf("\t\t\t┃      1、修改景点名称         ┃\n");
  printf("\t\t\t┃      2、修改景点描述         ┃\n");
  printf("\t\t\t┃      e、返回                 ┃\n");
  printf("\t\t\t┃                              ┃\n");
  printf("\t\t\t┗━━━━━━━━━━━━━━━┛\n");
  printf("\t\t\t\t请输入您的选择:");
  scanf("%c",&c);
  if(c=='1'||c=='2'||c=='e')
   flag=0;
 }while(flag);
 return c;
}

void Changesight()
{
	int a,b,length;
	char sight[100];
	char description[1000];
	char p;
	char q;
	int i;
	int num;	
	p=Changemenu();
	switch(p)
	{
	case'1':
		system("clear");
             narrate();
             printf("\n\n\t\t请输入您要修改的景点编号:");
             scanf("%d",&num);
             for(i=0;i<NUM;i++)
			 {
				 if(G.vex[i].number==num)
				 {
					 q=Sightmenu();
					 if(q=='1')
					 {
						 printf("请输入修改后的景点名称:\n");
                         scanf("%s",&sight);
						 strcpy(G.vex[num].sight,sight);
						 printf("\t\t\t\t修改成功！\n");
					 }
					 else if(q=='2')
					 {
						 printf("请输入修改后的景点信息:\n");
						 scanf("%s",&description);
						 strcpy(G.vex[num].description,description);
						 printf("\t\t\t\t修改成功！\n");
					 }
					 else if(q=='e')
						 p=Changemenu();
		
				 }
			}		
     printf("\n\t\t按任意键返回...");
     getchar();
     getchar();
     break;
   if(i==NUM)
   {
    printf("\n\n\t\t\t\t没有找到！");
    printf("\n\n\t\t\t按任意键返回...");
    getchar();
    getchar();
   }
   break;
 
		case '2':
		
			printf("\t\t请输入道路一侧的景点序号:");
			scanf("%d",&a);
			printf("\t\t请输入道路另一侧的景点序号:");
			scanf("%d",&b);
			printf("\t\t请输入修改后的道路长度:");
			scanf("%d",&length);
			G.arcs[a][b].adj=G.arcs[b][a].adj=length;
			printf("\t\t\t\t修改成功！\n");
            printf("\t\t");
			getchar();
			system("PAUSE");/*冻结函数*/
			break;	
	}
}	

void NewCreateUDN() /* 造新图函数 */
{ 
 int i,j,h,b,k,r,q;
 char newname[100];
 char sight[100];
 char description[1000];
 int length;
NUM=0;
 printf("请输入新学校的名称:\n");
 scanf("%s",&newname);
 strcpy(nameofschool,newname);
 printf("请输入新学校景点的个数:\n");
 scanf("%d",&h);
 printf("请输入新学校景点间路线的总条数:\n");
 scanf("%d",&b);
 G.vexnum=h;  /* 初始化结构中的景点数和边数 */
 G.arcnum=b;
 for(i=0;i<20;++i)
	 G.vex[i].number=i; /* 初始化每一个景点的编号 */

 /* 初始化一个景点名及其景点描述 */

 for(i=0;i<h;i++)
 {
	 printf("请输入景点名称:\n");
	 scanf("%s",&sight);
     strcpy(G.vex[i].sight,sight);
     printf("请输入该景点的描述:\n");
     scanf("%s",&description);
     strcpy(G.vex[i].description,description);
     NUM++;
 }
 /* 这里把所有的边假定为20000,含义是这两个景点之间是不可到达 */
 for(i=0;i<20;++i)
  for(j=0;j<20;++j) 
   G.arcs[i][j].adj=Max;
   /*
   
     下边是可直接到达的景点间的距离,由于两个景点间距离是互相的,
     所以要对图中对称的边同时赋值。    
 */
  for(k=0;k<b;k++)
  {
	  printf("请输入路径一侧景点的序号:\n");
	  scanf("%d",&r);
	  printf("清输入路径另一侧景点的序号:\n");
	  scanf("%d",&q);
	  printf("请输入第%d个景点到第%d个景点路径长度:\n",r,q);
	  scanf("%d",&length);
  G.arcs[r][q].adj=G.arcs[q][r].adj=length;
 }
  getchar();
  printf("\t\t创建%s导游图成功！\n\n\n",nameofschool);
  system("PAUSE");
}
