/*2048 -- 新疆大学计算机20-7班冯俊杰程序设计作品*/
#include<stdio.h>
#include<conio.h>  //控制输入输出
#include<time.h>
#include<Windows.h>

/*基本参数*/
int Step = 0;           //步数
long int Score = 0;     //得分
long int Time;          //用时
int Box[4][4] = { 0 };  //游戏界面:4X4
int AddTemp[4] = { 0 };    //合并数字函数的临时数组

/*基本函数*/
void GotoXY(int x, int y);    //设置光标位置
void Color(int x);            //设置字体颜色和背景色
void MainMenu(void);          //主菜单
void MenuChoice(void);        //菜单选择
void DrawGameBox(void);       //绘制游戏网格
void ShowRule(void);          //展示游戏规则
void NumColor(int x);         //设置数字颜色
int KeyDown(int key);            //键盘输入
int IfLeft(void);             //能否左移
int IfRight(void);            //能否右移
int IfUp(void);               //能否上移
int IfDown(void);             //能否下移
void Add(int *item);         //合并数字
void DrawNums(void);          //打印棋盘数字
void RandomNum(void);         //生成随机数
int MaxNum(void);            //返回最大数
int IfWin(void);             //游戏胜利
int IfLose(void);            //游戏失败
void GamePlay(void);         //开始游戏
void RePlay(void);           //重新开始游戏

//设置光标位置
void GotoXY(int x, int y)
{
	COORD pos = { x,y };   //位置结构体
	HANDLE Houtput = GetStdHandle(STD_OUTPUT_HANDLE);  //标准输出句柄
	SetConsoleCursorPosition(Houtput, pos);
}

//设置字体颜色和背景色
void Color(int x)
{
	HANDLE Houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Houtput, x);
}

//设置数字颜色
void NumColor(int x)
{
	switch (x)
	{
	case 2:Color(1);break;
	case 4:Color(2);break;
	case 8:Color(3);break;
	case 16:Color(4);break;
	case 32:Color(5);break;
	case 64:Color(6);break;
	case 128:Color(7);break;
	case 256:Color(8);break;
	case 512:Color(9);break;
	case 1024:Color(10);break;
	case 2048:Color(11);break;
	default:Color(12);break;
	}
}

//能否左移
int IfLeft()
{
	int x, y;
	/*遍历所有网格*/
	for (x = 0;x < 4;++x)
	{
		for (y = 3;y > 0;--y)
		{
			//如果该网格不为空
			if (Box[x][y])
			{
				//情况1：可以合并
				if (Box[x][y] == Box[x][y - 1])
					return 1;
				//情况2：周围有空格
				if (!Box[x][y - 1])
					return 1;
			}
			else  //该网格为空
				return 1;
		}
	}
	return 0;
}

// 能否右移
int IfRight()
{
	int x, y;
	for (x = 0;x < 4;++x)
	{
		for (y = 0;y < 3;++y)
		{
			if (Box[x][y])
			{
				if (Box[x][y] == Box[x][y + 1])
					return 1;
				if (!Box[x][y + 1])
					return 1;
			}
			else
				return 1;
		}
	}
	return 0;
}

// 能否上移
int IfUp()
{
	int x, y;
	for (y = 0;y < 4;++y)
	{
		for (x = 3;x > 0;--x)
		{
			if (Box[x][y])
			{
				if (Box[x][y] == Box[x - 1][y])
					return 1;
				if (!Box[x - 1][y])
					return 1;
			}
			else
				return 1;
		}
	}
	return 0;
}

// 能否下移
int IfDown()
{
	int x, y;
	for (y = 0;y < 4;++y)
	{
		for (x = 0;x < 3;++x)
		{
			if (Box[x][y])
			{
				if (Box[x + 1][y] == Box[x][y])
					return 1;
				if (!Box[x + 1][y])
					return 1;
			}
			else
				return 1;
		}
	}
	return 0;
}

//合并相同数字
void Add(int *item)
{
	int i, j = 0;
	memset(AddTemp, 0, 4*sizeof(int));

	/*移动数字到临时数组中*/
	for (i = 0;i < 4;i++)
	{
		//如果是0，则跳过
		//模拟了2048中跳过空格合并的过程
		if (item[i])
			AddTemp[j++] = item[i];
	}
	/*合并数字*/
	for (i = 0;i < 3;i++)
	{
		if (AddTemp[i] == AddTemp[i + 1])
		{
			Score += (AddTemp[i] * 10);
			AddTemp[i] *= 2;
			AddTemp[i + 1] = 0;
		}
	}
	/*返回合并结果*/
	memset(item, 0, 4*sizeof(int));
	for (i = 0, j = 0;i < 4;i++)
	{
		if (AddTemp[i])
			item[i] = AddTemp[i];
	}
}

//打印游戏棋盘
void DrawGameBox(void)
{
	int x, y;
	Color(7);  //网格颜色
	/*打印网格*/
	for (y = 3;y < 20;y++)
	{
		for (x = 20;x < 61;x++)
		{
			GotoXY(x, y);
			if (y == 3 || y == 7 || y == 11 || y == 15 || y == 19)
				printf("-");
			else
			{
				printf("|         |         |         |         |");
				break;
			}
		}
	}
	
	GotoXY(20, 2);
	printf("得分: %ld", Score);
	GotoXY(45, 2);
	printf("执行步数: %d", Step);
	GotoXY(45, 20);
	printf("已用时: %lds",(long)time(NULL) - Time);  //当前时间--开始时间
}

//打印棋盘数字
void DrawNums(void)
{
	int x, y;
	for (x = 0;x < 4;x++)
	{
		for (y = 0;y < 4;y++)
		{
			if (Box[x][y])
			{
				GotoXY(25 + y * 10, 5 + x * 4);
				NumColor(Box[x][y]);
				printf("%d", Box[x][y]);
			}
		}
	}
}

//打印游戏规则
void ShowRule(void)
{
	int x, y;
	system("cls");  //清空界面
	Color(15);
	GotoXY(35, 3);
	printf("游戏规则");
	/*打印方框*/
	Color(7);
	for (y = 5;y < 20;y++)
	{
		for (x = 10;x < 70;x++)
		{
			GotoXY(x, y);
			if (y == 5 || y == 19)
				printf("=");
			else if (x == 10 || x == 68)
				printf("||");
		}
	}
	/*打印游戏规则*/
	Color(15);
	GotoXY(13, 7);
	printf("tips1：玩家可以通过↑ ↓ ← →方向键来移动方块");
	GotoXY(13, 9);
	printf("tips2：按ESC退出游戏");
	GotoXY(13, 11);
	printf("tips3：玩家选择的方向上，若有相同的数字则合并");
	GotoXY(13, 13);
	printf("tips4：每移动一步，空位随机出现一个2或4");
	GotoXY(13, 15);
	printf("tips5：棋盘被数字填满，无法进行有效移动，游戏失败");
	GotoXY(13, 17);
	printf("tips6：棋盘上出现2048，游戏胜利");
}

//生成随机数
void RandomNum(void)
{
	int x, y, Time = 0;
	srand(time(0));
	/*随机确定空位*/
	do
	{
		x = rand() % 4;
		y = rand() % 4;
		Time++;
	} while (Box[x][y]&&Time<16);
	/*给空位赋值随机数*/
	if (Time > 16)  //没有空位
		return;
	if (rand() % 4 == 0)  //4出现的概率要比2小
		Box[x][y] = 4;
	else
		Box[x][y] = 2;
}

//求棋盘上的最大数字
int MaxNum(void)
{
	int i, j, max = INT_MIN;
	for (i = 0;i < 4;++i)
	{
		for (j = 0;j < 4;++j)
		{
			if (Box[i][j] > max)
				max = Box[i][j];
		}
	}
	return max;
}

//游戏胜利
int IfWin(void)
{
	int flag = 0;
	//有2048即胜利
	if (2048 == MaxNum())
	{
		system("cls");
		Color(11);
		GotoXY(6, 6);
		printf("■              ■              ■     ■■■■■     ■       ■");
		GotoXY(6, 7);
		printf(" ■            ■■            ■          ■         ■■     ■");
		GotoXY(6, 8);
		printf("  ■          ■  ■          ■           ■         ■ ■    ■");
		GotoXY(6, 9);
		printf("   ■        ■    ■        ■            ■         ■  ■   ■");
		GotoXY(6, 10);
		printf("    ■      ■      ■      ■             ■         ■   ■  ■");
		GotoXY(6, 11);
		printf("     ■    ■        ■    ■              ■         ■    ■ ■");
		GotoXY(6, 12);
		printf("      ■  ■          ■  ■               ■         ■     ■■");
		GotoXY(6, 13);
		printf("       ■■            ■■            ■■■■■     ■      ■");
		flag = 1;
	}
	return flag;
}

//游戏失败
int IfLose(void)
{
	int flag = 0;
	//没有多余的步数即失败
	if (IfLeft() + IfRight() + IfUp() + IfDown() == 0)
	{
		system("cls");
		Color(12);
		GotoXY(19, 6);
		printf("■■■■■    ■         ■    ■■");
		GotoXY(19, 7);
		printf("■            ■■       ■    ■ ■");
		GotoXY(19, 8);
		printf("■            ■ ■      ■    ■  ■");
		GotoXY(19, 9);
		printf("■            ■  ■     ■    ■   ■");
		GotoXY(19, 10);
		printf("■■■■      ■   ■    ■    ■    ■");
		GotoXY(19, 11);
		printf("■            ■    ■   ■    ■   ■");
		GotoXY(19, 12);
		printf("■            ■     ■  ■    ■  ■");
		GotoXY(19, 13);
		printf("■            ■      ■ ■    ■ ■");
		GotoXY(19, 14);
		printf("■■■■■    ■       ■■    ■■");
		flag = 1;
	}
	return flag;
}

//控制键盘输入
int KeyDown(int key)
{
	int i, j;
	int tmp[4] = { 0 };
	char ch;
	switch (key)
	{
	case 27: //	ESC的ASCII码
	{
		Color(12);
		GotoXY(20, 20);
		printf("确定退出游戏吗? (y/n)");
		ch = _getch();
		if (ch == 'Y' || ch == 'y')
			exit(0);
		else
		{
			GotoXY(20, 20);
			printf("          ");
		}
		break;
	}
	case 75: //左移
	{
		if (IfLeft())
		{
			/*左移和合并*/
			for (i = 0;i < 4;i++)
			{
				//复制每行的值
				for (j = 0;j < 4;j++)
					tmp[j] = Box[i][j];
				//左移
				Add(tmp);
				//返回移动后的值
				for (j = 0;j < 4;j++)
					Box[i][j] = tmp[j];
			}
		}
		break;
	}
	case 77: //右移
	{
		if (IfRight())
		{
			for (i = 0;i < 4;i++)
			{
				//倒着复制每行的值
				//因为最右边的要最先合并
				for (j = 0;j < 4;j++)
					tmp[3 - j] = Box[i][j];
				Add(tmp);
				for (j = 0;j < 4;j++)
					Box[i][j] = tmp[3 - j];
			}
		}
		break;
	}
	case 72:  //上移
	{
		if (IfUp())
		{
			for (j = 0;j < 4;j++)
			{
				//复制每列的值
				for (i = 0;i < 4;i++)
					tmp[i] = Box[i][j];
				Add(tmp);
				//返回被合并的值
				for (i = 0;i < 4;i++)
					Box[i][j] = tmp[i];
			}
		}
		break;
	}
	case 80:   //下移
	{
		if (IfDown())
		{
			for (j = 0;j < 4;j++)
			{
				//倒着复制每列的值
				//因为最下面的要最先合并
				for (i = 0;i < 4;i++)
					tmp[3 - i] = Box[i][j];
				Add(tmp);
				//返回被合并的值
				for (i = 0;i < 4;i++)
					Box[i][j] = tmp[3 - i];
			}
		}
		break;
	}
	default:  //按下其他键
	{
		return 0;
		break;
	}
	}
	return 1;
}

//重新开始游戏
void RePlay(void)
{
	//清空
	system("cls");
	Score = 0;
	Step = 0;
	memset(Box, 0, 16 * sizeof(int));
	GamePlay();
}

//开始游戏
void GamePlay(void)
{
	int i, j, x, y, n;
	system("cls");       //清空界面
	Time = time(NULL);  //确定当前时间
	DrawGameBox();      //打印游戏网格
	RandomNum();        //生成随机数
	DrawNums();         //打印棋盘数字

	/*开始游戏循环*/
	while (1)
	{
		//捕获键盘输入
		if (KeyDown(_getch()))
		{
			DrawGameBox();
			RandomNum();
			DrawNums();
			Step++;

			//胜利或失败,一轮游戏结束
			if (IfWin() || IfLose())
			{
				GotoXY(20, 20);
				Color(12);
				printf("请输入：（1.再来一局 2.结束游戏）：");
				scanf_s("%d", &n);
				switch (n)
				{
				case 1:
					RePlay();
					break;
				case 2:
					exit(0);
					break;
				default:
					exit(0);break;
				}
			}
		}
	}
}

void MainMenu(void)
{
	int i, j;
	/*打印标题2048*/
	Color(11);
	GotoXY(15, 2);
	printf("■■■■■   ■■■■■   ■   ■     ■■■■■");
	GotoXY(15, 3);
	printf("        ■   ■      ■   ■   ■     ■      ■");
	GotoXY(15, 4);
	printf("        ■   ■      ■   ■   ■     ■      ■");
	GotoXY(15, 5);
	printf("■■■■■   ■      ■   ■   ■     ■■■■■");
	GotoXY(15, 6);
	printf("■           ■      ■   ■■■■■  ■      ■");
	GotoXY(15, 7);
	printf("■           ■      ■        ■     ■      ■");
	GotoXY(15, 8);
	printf("■■■■■   ■■■■■        ■     ■■■■■");

	/*打印选项菜单*/
	Color(7);
	//打印边框
	for (j = 0;j < 21;j++)
	{
		for (i = 15;i < 63;i++)
		{
			GotoXY(i, j);
			if (j == 10 || j == 20)
				printf("=");
			else if (i == 15 || i == 61)
				printf("||");
		}
	}
	//打印选项
	Color(15);
	GotoXY(33, 12);
	printf("1.开始游戏");
	GotoXY(33, 15);
	printf("2.游戏规则");
	GotoXY(33, 18);
	printf("3.退出");
}

//菜单选择
void MenuChoice()
{
	int n;
	GotoXY(28, 21);
	printf("请输入[1 2 3]：[ ]\b\b");
	scanf_s("%d", &n);
	switch (n)
	{
	case 1:
		system("cls");
		GamePlay();
		break;
	case 2:
		ShowRule();
		break;
	case 3:
		exit(0);
		break;
	default:
		break;
	}
}

//主函数
void main(void)
{
	/*主循环*/
	while (1)
	{
		MainMenu();   //显示菜单
		MenuChoice();   //选择
		getchar();     //缓冲
		system("cls");
	}
}
