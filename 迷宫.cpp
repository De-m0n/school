#include<iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
using namespace std;

void EnQueue(int i,int j,int k);//入队节点 
void DeQueue(int *i,int *j,int *k);//获得当前节点序号和迷宫坐标后，出队 
bool GetNextPos(int *i,int *j,int count);//获得下一点位置 
void ShortestPath_BFS(int i,int j,int map[15][16],int gate);// 广度优先遍历求最短路径 
void ShortestPath();// 最短路径 
int map[15][16];

struct Node
{
	int parent_id;//父节点位置 
	int node_id;//节点序号
	int x,y;//节点对应坐标 
}Q[10*10];

int front=0,rear=0;

void ReadMap(int map[15][16],int gate)
{
    FILE *fp;
    fp=fopen("map.txt","r");
    if(fp==NULL)
	{
        printf("Cannot open the file,strike any key to exit!\n");
        exit(0);
    }
	fseek(fp,(gate-1)*(5+255)+5,SEEK_SET);
    for(int i=0;i<15;i++)
   {
   		for(int j=0;j<16;j++)
   		{
   			map[i][j]=fgetc(fp);
		}
   }
	fclose(fp);
}

void DrawMap(int map[15][16] )
{
	printf("\n");
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
		{
		    switch(map[i][j])
			{
			case 48://空地
				printf("  ");
				break;
			case 49://墙壁
				printf("■") ;
				break;
			case 53://人 
				printf("鼠");
				break;
			case 2://路径
				printf("*") ;
				break;
			}
		}	
		printf("\n");
	}
}

int Control(int map[15][16],int gate)
{
	int x,y;
	int i,j;
	for(int i=0;i<15;i++)	
		for(int j=0;j<15;j++)
		if(map[i][j]==53)
		{
			x=i;
			y=j;
		}
	int  ch;
	ch=getch();	 
	switch(ch)
	{
		case 'w':
		case 'W':
		case 72://向上
				if(map[x-1][y]==48)//人前面是空地或者目的地 
				{
					map[x][y]-=5;
					map[x-1][y]+=5;
				}
				break;
		case 'a':
		case 'A':
		case 75://向左
				if(map[x][y-1]==48)
				{
					map[x][y]-=5;
					map[x][y-1]+=5;
				}
				break;
		case 's':
		case 'S':
		case 80://向下
				if(map[x+1][y]==48)
				{
					map[x][y]-=5;
					map[x+1][y]+=5;
				}
				break;
		case 'd':
		case 'D':
		case 77://向右	
				if(map[x][y+1]==48)
				{
					map[x][y]-=5;
					map[x][y+1]+=5;
				}
				break;
		case 'h':
				cout<<"输入要变块的位置：";
				scanf("%d%d",&i,&j);
				i-=1;
				j-=1;
				if(map[i][j]==49)
				{
					map[i][j]=48;
				 } 
				else if(map[i][j]==48)
				{
					map[i][j]=49;
				}
				system("cls");
				DrawMap(map); 
				break;
	} 
}


int Judgement(int map[15][16],int gate)
 {
 	for(int i=0;i<15;i++)
 	{                  
 		for(int j=0;j<16;j++)    
		{                    
			if(map[i][j]==53)
			{    
				if(i==13&&j==14)      
				return 0;//继续游戏                                                                       
			} 
		}		
	}
	return 1;
 }


void adc()
{
	int map[15][16],gate=1;
	int n,i=7,j=7;
    int t;
    int o=0;
    n=10;
    t=time(NULL);
    int score=0;
	ReadMap(map,gate);
	while(1){
		if(Judgement(map,gate)!=1)
		{
			int k; 
			printf("闯关成功\n");
			printf("最短路径为：\n");
			ShortestPath_BFS(i,j,map,gate);
			ShortestPath();
			printf("是否继续游戏？是-1 否-0");
			cin>>k;
			if(k==1)
			{
				gate++;
				ReadMap(map,gate);
				system("cls");
				DrawMap(map);
				score+=100;
				i=0;
			}
			else if(k==0)
			{
				exit(0);
			}
		}
		system("cls");
		cout<<"当前分数为："<<score<<endl; 
		cout<<"游戏机中按h键编辑迷宫"<<endl; 
		cout<<"请在十秒内走出迷宫!"<<endl; 
		if(t!=time(NULL)){	
           o++;
           t=time(NULL);
           if(o>n){
                printf("游戏结束！\n"); 
				break;
           }
        }
		DrawMap(map);
		Control(map,gate);
		
	}
}

void ShortestPath_BFS(int i,int j,int map[15][16],int gate)
{
	ReadMap(map,gate);
	int count,m,n,k; 
	EnQueue(i,j,-1);
	map[i][j] = 2;
	while(1)
	{
		count=1;
		DeQueue(&i,&j,&k);
		n=i,m=j;//记录当前位置 
		while(GetNextPos(&i,&j,count)) 
		{
			if(map[i][j]==48) 
			{ 	
				EnQueue(i,j,k); 
				map[i][j] = 2; 
				if(i == 13 && j == 14) 
					return; //遍历结束后返回 
			}
			i = n; j = m; //保证遍历当前坐标的所有相邻位置
			count++; 
		}
	}
}

	void ShortestPath() 
	{
		int i,j,k,sum=0;
		k = rear-1; 
		while(k != -1) 
		{
			i = Q[k].x; 
			j = Q[k].y;
			map[i][j] = 2; 
			k = Q[k].parent_id; 
		}
		for(i = 0;i < 15;i++) 
{

for(j = 0;j < 15;j++)
{
if(map[i][j]==2) 
{sum++; cout<<"□";} 
else 
cout<<"■"; 
}
cout<<endl; 
}	
		cout<<"最短路径长度："<<sum<<endl; 
	}

void DeQueue(int *i,int *j,int *k) //获取当前节点的序号和对应的迷宫坐标，然后出列
{
	*i = Q[front].x; 
	*j = Q[front].y; 
	*k = Q[front].node_id; 
	front++; //出列一个节点
}

void EnQueue(int i,int j,int k) //入队一个节点
{ 
	Q[rear].x = i; 
	Q[rear].y = j; //保存当前节点对应的坐标位置
	Q[rear].parent_id = k; //保存父节点的序号 
	Q[rear].node_id = rear; //保存当前节点序号 
	rear++;
}

bool GetNextPos(int *i ,int *j,int count) //得到下一个邻接点的位置 
{
	switch(count) 
	{
		case 1:(*j)++; return 1; //右
		case 2:(*i)++; return 1; //下
		case 3:(*j)--; return 1; //左
		case 4:(*i)--; return 1; //上
		default: 
		return 0; 
	} 
}

void adc1()
{
	int map[15][16],gate;
	int n;
    int t;
    int i=0;
    n=10;
    t=time(NULL);
    int score=0;
    cout<<"请输入要玩的关卡（1-4）："; 
    cin>>gate;
	ReadMap(map,gate);
	while(1){
		if(Judgement(map,gate)!=1)
		{
			printf("恭喜过关！\n"); 
			
			break; 
			gate++;
			ReadMap(map,gate);
			system("cls");
			DrawMap(map);
			score+=100;
			i=0;
		}
		system("cls");
		cout<<"请在10秒内走出迷宫"<<endl;
		cout<<"游戏机中按h键编辑迷宫"<<endl; 
		if(t!=time(NULL)){//倒计时	
           i++;
           t=time(NULL);
           if(i>n){
                printf("游戏结束！\n"); 
				break;
           }
        }
        DrawMap(map);
		Control(map,gate);
	}
}

int main()
{
	int c;
	cout<<"迷宫V1.0"<<endl;
	cout<<"1.开始游戏"<<"2.闯关"<<endl;
	while(1)
	{
		cout<<"请输入选项：";
		cin>>c;
		if(c==1) 
		{
			adc();
		} 
		else if(c==2) 
		{
		 	adc1();
		}
		else
		{
			printf("输入错误，请重新输入!\n"); 
		}
	} 
	return 0;
}
