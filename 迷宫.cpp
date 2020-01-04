#include<iostream>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
using namespace std;

void EnQueue(int i,int j,int k);//��ӽڵ� 
void DeQueue(int *i,int *j,int *k);//��õ�ǰ�ڵ���ź��Թ�����󣬳��� 
bool GetNextPos(int *i,int *j,int count);//�����һ��λ�� 
void ShortestPath_BFS(int i,int j,int map[15][16],int gate);// ������ȱ��������·�� 
void ShortestPath();// ���·�� 
int map[15][16];

struct Node
{
	int parent_id;//���ڵ�λ�� 
	int node_id;//�ڵ����
	int x,y;//�ڵ��Ӧ���� 
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
			case 48://�յ�
				printf("  ");
				break;
			case 49://ǽ��
				printf("��") ;
				break;
			case 53://�� 
				printf("��");
				break;
			case 2://·��
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
		case 72://����
				if(map[x-1][y]==48)//��ǰ���ǿյػ���Ŀ�ĵ� 
				{
					map[x][y]-=5;
					map[x-1][y]+=5;
				}
				break;
		case 'a':
		case 'A':
		case 75://����
				if(map[x][y-1]==48)
				{
					map[x][y]-=5;
					map[x][y-1]+=5;
				}
				break;
		case 's':
		case 'S':
		case 80://����
				if(map[x+1][y]==48)
				{
					map[x][y]-=5;
					map[x+1][y]+=5;
				}
				break;
		case 'd':
		case 'D':
		case 77://����	
				if(map[x][y+1]==48)
				{
					map[x][y]-=5;
					map[x][y+1]+=5;
				}
				break;
		case 'h':
				cout<<"����Ҫ����λ�ã�";
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
				return 0;//������Ϸ                                                                       
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
			printf("���سɹ�\n");
			printf("���·��Ϊ��\n");
			ShortestPath_BFS(i,j,map,gate);
			ShortestPath();
			printf("�Ƿ������Ϸ����-1 ��-0");
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
		cout<<"��ǰ����Ϊ��"<<score<<endl; 
		cout<<"��Ϸ���а�h���༭�Թ�"<<endl; 
		cout<<"����ʮ�����߳��Թ�!"<<endl; 
		if(t!=time(NULL)){	
           o++;
           t=time(NULL);
           if(o>n){
                printf("��Ϸ������\n"); 
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
		n=i,m=j;//��¼��ǰλ�� 
		while(GetNextPos(&i,&j,count)) 
		{
			if(map[i][j]==48) 
			{ 	
				EnQueue(i,j,k); 
				map[i][j] = 2; 
				if(i == 13 && j == 14) 
					return; //���������󷵻� 
			}
			i = n; j = m; //��֤������ǰ�������������λ��
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
{sum++; cout<<"��";} 
else 
cout<<"��"; 
}
cout<<endl; 
}	
		cout<<"���·�����ȣ�"<<sum<<endl; 
	}

void DeQueue(int *i,int *j,int *k) //��ȡ��ǰ�ڵ����źͶ�Ӧ���Թ����꣬Ȼ�����
{
	*i = Q[front].x; 
	*j = Q[front].y; 
	*k = Q[front].node_id; 
	front++; //����һ���ڵ�
}

void EnQueue(int i,int j,int k) //���һ���ڵ�
{ 
	Q[rear].x = i; 
	Q[rear].y = j; //���浱ǰ�ڵ��Ӧ������λ��
	Q[rear].parent_id = k; //���游�ڵ����� 
	Q[rear].node_id = rear; //���浱ǰ�ڵ���� 
	rear++;
}

bool GetNextPos(int *i ,int *j,int count) //�õ���һ���ڽӵ��λ�� 
{
	switch(count) 
	{
		case 1:(*j)++; return 1; //��
		case 2:(*i)++; return 1; //��
		case 3:(*j)--; return 1; //��
		case 4:(*i)--; return 1; //��
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
    cout<<"������Ҫ��Ĺؿ���1-4����"; 
    cin>>gate;
	ReadMap(map,gate);
	while(1){
		if(Judgement(map,gate)!=1)
		{
			printf("��ϲ���أ�\n"); 
			
			break; 
			gate++;
			ReadMap(map,gate);
			system("cls");
			DrawMap(map);
			score+=100;
			i=0;
		}
		system("cls");
		cout<<"����10�����߳��Թ�"<<endl;
		cout<<"��Ϸ���а�h���༭�Թ�"<<endl; 
		if(t!=time(NULL)){//����ʱ	
           i++;
           t=time(NULL);
           if(i>n){
                printf("��Ϸ������\n"); 
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
	cout<<"�Թ�V1.0"<<endl;
	cout<<"1.��ʼ��Ϸ"<<"2.����"<<endl;
	while(1)
	{
		cout<<"������ѡ�";
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
			printf("�����������������!\n"); 
		}
	} 
	return 0;
}
