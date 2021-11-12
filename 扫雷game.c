#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"

void InitBoard(char board[ROWS][COLS],int rows,int cols,char set)
{
	int i=0;
	int j=0;
	for(i=0;i<rows;i++)
	{
		for(j=0;j<cols;j++)
		{
			board[i][j]=set;
		}
	}
}
//打印棋盘
void DisplayBoard(char board[ROWS][COLS],int row,int col)
{
	int i=0;
	int j=0;
	//打印列号
	for(i=0;i<=col;i++)
	{
		printf("%d ",i);
	}
	printf("\n");
	for(i=1; i <= row; i++)
	{
		//打印行号
		printf("%d ",i);
		for(j=1;j<=col;j++)
		{
			printf("%c ",board[i][j]);
		}
		printf("\n");
	}
}


void SetMine(char board[ROWS][COLS],int row,int col)
{
	int count =EASY_COUNT;
	while(count)
	{
		int i=rand()%row+1;
		int j=rand()%col+1;
		if(board[i][j]=='0')
		{
			board[i][j]='1';
			count--;
		}
	}
}
//'1'-'0'=1
//'3'-'0'=3,字符3减去字符0等于数字3
int get_mine_count(char mine[ROWS][COLS],int x,int y)
{
	
	return mine[x-1][y]+mine[x-1][y-1]+mine[x][y-1]+mine[x+1][y-1]+mine[x+1][y]+
		mine[x+1][y+1]+mine[x][y+1]+mine[x-1][y+1]-8*'0';
}

void FindMine(char mine[ROWS][COLS],char show[ROWS][COLS],int row,int col)
{
	int x=0;
	int y=0;
	int win=0;
	while(win<row*col-EASY_COUNT)
	{
		printf("请输入要排查的坐标：>\n");
		scanf("%d%d",&x,&y);
		//判断输入的这一点有没有雷
		//判断这一点是否合法
		if(x>=1 && x<=row && y>=1 && y<=col)
		{
			//如果有雷
			//1.踩雷
			if(mine[x][y]=='1')
			{
				printf("很遗憾，你被炸死了\n");
				DisplayBoard(mine,row,col);
				break;
			}
			//没踩到,计算周围有几颗雷
			else
			{
				int count = get_mine_count(mine,x,y);
				show[x][y]=count + '0';
				DisplayBoard(show,row,col);
				win++;
			}
		}
		//不合法
		else
		{
			printf("坐标非法，请重新输入\n");
		}
	}
	if(win==row*col-EASY_COUNT)
	{
		printf("恭喜你，排雷成功\n");
		DisplayBoard(mine,row,col);
	}
}
