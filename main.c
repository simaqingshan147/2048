/*2048 -- �½���ѧ�����20-7��뿡�ܳ��������Ʒ*/
#include<stdio.h>
#include<conio.h>  //�����������
#include<time.h>
#include<Windows.h>

/*��������*/
int Step = 0;           //����
long int Score = 0;     //�÷�
long int Time;          //��ʱ
int Box[4][4] = { 0 };  //��Ϸ����:4X4
int AddTemp[4] = { 0 };    //�ϲ����ֺ�������ʱ����

/*��������*/
void GotoXY(int x, int y);    //���ù��λ��
void Color(int x);            //����������ɫ�ͱ���ɫ
void MainMenu(void);          //���˵�
void MenuChoice(void);        //�˵�ѡ��
void DrawGameBox(void);       //������Ϸ����
void ShowRule(void);          //չʾ��Ϸ����
void NumColor(int x);         //����������ɫ
int KeyDown(int key);            //��������
int IfLeft(void);             //�ܷ�����
int IfRight(void);            //�ܷ�����
int IfUp(void);               //�ܷ�����
int IfDown(void);             //�ܷ�����
void Add(int *item);         //�ϲ�����
void DrawNums(void);          //��ӡ��������
void RandomNum(void);         //���������
int MaxNum(void);            //���������
int IfWin(void);             //��Ϸʤ��
int IfLose(void);            //��Ϸʧ��
void GamePlay(void);         //��ʼ��Ϸ
void RePlay(void);           //���¿�ʼ��Ϸ

//���ù��λ��
void GotoXY(int x, int y)
{
	COORD pos = { x,y };   //λ�ýṹ��
	HANDLE Houtput = GetStdHandle(STD_OUTPUT_HANDLE);  //��׼������
	SetConsoleCursorPosition(Houtput, pos);
}

//����������ɫ�ͱ���ɫ
void Color(int x)
{
	HANDLE Houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Houtput, x);
}

//����������ɫ
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

//�ܷ�����
int IfLeft()
{
	int x, y;
	/*������������*/
	for (x = 0;x < 4;++x)
	{
		for (y = 3;y > 0;--y)
		{
			//���������Ϊ��
			if (Box[x][y])
			{
				//���1�����Ժϲ�
				if (Box[x][y] == Box[x][y - 1])
					return 1;
				//���2����Χ�пո�
				if (!Box[x][y - 1])
					return 1;
			}
			else  //������Ϊ��
				return 1;
		}
	}
	return 0;
}

// �ܷ�����
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

// �ܷ�����
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

// �ܷ�����
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

//�ϲ���ͬ����
void Add(int *item)
{
	int i, j = 0;
	memset(AddTemp, 0, 4*sizeof(int));

	/*�ƶ����ֵ���ʱ������*/
	for (i = 0;i < 4;i++)
	{
		//�����0��������
		//ģ����2048�������ո�ϲ��Ĺ���
		if (item[i])
			AddTemp[j++] = item[i];
	}
	/*�ϲ�����*/
	for (i = 0;i < 3;i++)
	{
		if (AddTemp[i] == AddTemp[i + 1])
		{
			Score += (AddTemp[i] * 10);
			AddTemp[i] *= 2;
			AddTemp[i + 1] = 0;
		}
	}
	/*���غϲ����*/
	memset(item, 0, 4*sizeof(int));
	for (i = 0, j = 0;i < 4;i++)
	{
		if (AddTemp[i])
			item[i] = AddTemp[i];
	}
}

//��ӡ��Ϸ����
void DrawGameBox(void)
{
	int x, y;
	Color(7);  //������ɫ
	/*��ӡ����*/
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
	printf("�÷�: %ld", Score);
	GotoXY(45, 2);
	printf("ִ�в���: %d", Step);
	GotoXY(45, 20);
	printf("����ʱ: %lds",(long)time(NULL) - Time);  //��ǰʱ��--��ʼʱ��
}

//��ӡ��������
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

//��ӡ��Ϸ����
void ShowRule(void)
{
	int x, y;
	system("cls");  //��ս���
	Color(15);
	GotoXY(35, 3);
	printf("��Ϸ����");
	/*��ӡ����*/
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
	/*��ӡ��Ϸ����*/
	Color(15);
	GotoXY(13, 7);
	printf("tips1����ҿ���ͨ���� �� �� ����������ƶ�����");
	GotoXY(13, 9);
	printf("tips2����ESC�˳���Ϸ");
	GotoXY(13, 11);
	printf("tips3�����ѡ��ķ����ϣ�������ͬ��������ϲ�");
	GotoXY(13, 13);
	printf("tips4��ÿ�ƶ�һ������λ�������һ��2��4");
	GotoXY(13, 15);
	printf("tips5�����̱������������޷�������Ч�ƶ�����Ϸʧ��");
	GotoXY(13, 17);
	printf("tips6�������ϳ���2048����Ϸʤ��");
}

//���������
void RandomNum(void)
{
	int x, y, Time = 0;
	srand(time(0));
	/*���ȷ����λ*/
	do
	{
		x = rand() % 4;
		y = rand() % 4;
		Time++;
	} while (Box[x][y]&&Time<16);
	/*����λ��ֵ�����*/
	if (Time > 16)  //û�п�λ
		return;
	if (rand() % 4 == 0)  //4���ֵĸ���Ҫ��2С
		Box[x][y] = 4;
	else
		Box[x][y] = 2;
}

//�������ϵ��������
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

//��Ϸʤ��
int IfWin(void)
{
	int flag = 0;
	//��2048��ʤ��
	if (2048 == MaxNum())
	{
		system("cls");
		Color(11);
		GotoXY(6, 6);
		printf("��              ��              ��     ����������     ��       ��");
		GotoXY(6, 7);
		printf(" ��            ����            ��          ��         ����     ��");
		GotoXY(6, 8);
		printf("  ��          ��  ��          ��           ��         �� ��    ��");
		GotoXY(6, 9);
		printf("   ��        ��    ��        ��            ��         ��  ��   ��");
		GotoXY(6, 10);
		printf("    ��      ��      ��      ��             ��         ��   ��  ��");
		GotoXY(6, 11);
		printf("     ��    ��        ��    ��              ��         ��    �� ��");
		GotoXY(6, 12);
		printf("      ��  ��          ��  ��               ��         ��     ����");
		GotoXY(6, 13);
		printf("       ����            ����            ����������     ��      ��");
		flag = 1;
	}
	return flag;
}

//��Ϸʧ��
int IfLose(void)
{
	int flag = 0;
	//û�ж���Ĳ�����ʧ��
	if (IfLeft() + IfRight() + IfUp() + IfDown() == 0)
	{
		system("cls");
		Color(12);
		GotoXY(19, 6);
		printf("����������    ��         ��    ����");
		GotoXY(19, 7);
		printf("��            ����       ��    �� ��");
		GotoXY(19, 8);
		printf("��            �� ��      ��    ��  ��");
		GotoXY(19, 9);
		printf("��            ��  ��     ��    ��   ��");
		GotoXY(19, 10);
		printf("��������      ��   ��    ��    ��    ��");
		GotoXY(19, 11);
		printf("��            ��    ��   ��    ��   ��");
		GotoXY(19, 12);
		printf("��            ��     ��  ��    ��  ��");
		GotoXY(19, 13);
		printf("��            ��      �� ��    �� ��");
		GotoXY(19, 14);
		printf("����������    ��       ����    ����");
		flag = 1;
	}
	return flag;
}

//���Ƽ�������
int KeyDown(int key)
{
	int i, j;
	int tmp[4] = { 0 };
	char ch;
	switch (key)
	{
	case 27: //	ESC��ASCII��
	{
		Color(12);
		GotoXY(20, 20);
		printf("ȷ���˳���Ϸ��? (y/n)");
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
	case 75: //����
	{
		if (IfLeft())
		{
			/*���ƺͺϲ�*/
			for (i = 0;i < 4;i++)
			{
				//����ÿ�е�ֵ
				for (j = 0;j < 4;j++)
					tmp[j] = Box[i][j];
				//����
				Add(tmp);
				//�����ƶ����ֵ
				for (j = 0;j < 4;j++)
					Box[i][j] = tmp[j];
			}
		}
		break;
	}
	case 77: //����
	{
		if (IfRight())
		{
			for (i = 0;i < 4;i++)
			{
				//���Ÿ���ÿ�е�ֵ
				//��Ϊ���ұߵ�Ҫ���Ⱥϲ�
				for (j = 0;j < 4;j++)
					tmp[3 - j] = Box[i][j];
				Add(tmp);
				for (j = 0;j < 4;j++)
					Box[i][j] = tmp[3 - j];
			}
		}
		break;
	}
	case 72:  //����
	{
		if (IfUp())
		{
			for (j = 0;j < 4;j++)
			{
				//����ÿ�е�ֵ
				for (i = 0;i < 4;i++)
					tmp[i] = Box[i][j];
				Add(tmp);
				//���ر��ϲ���ֵ
				for (i = 0;i < 4;i++)
					Box[i][j] = tmp[i];
			}
		}
		break;
	}
	case 80:   //����
	{
		if (IfDown())
		{
			for (j = 0;j < 4;j++)
			{
				//���Ÿ���ÿ�е�ֵ
				//��Ϊ�������Ҫ���Ⱥϲ�
				for (i = 0;i < 4;i++)
					tmp[3 - i] = Box[i][j];
				Add(tmp);
				//���ر��ϲ���ֵ
				for (i = 0;i < 4;i++)
					Box[i][j] = tmp[3 - i];
			}
		}
		break;
	}
	default:  //����������
	{
		return 0;
		break;
	}
	}
	return 1;
}

//���¿�ʼ��Ϸ
void RePlay(void)
{
	//���
	system("cls");
	Score = 0;
	Step = 0;
	memset(Box, 0, 16 * sizeof(int));
	GamePlay();
}

//��ʼ��Ϸ
void GamePlay(void)
{
	int i, j, x, y, n;
	system("cls");       //��ս���
	Time = time(NULL);  //ȷ����ǰʱ��
	DrawGameBox();      //��ӡ��Ϸ����
	RandomNum();        //���������
	DrawNums();         //��ӡ��������

	/*��ʼ��Ϸѭ��*/
	while (1)
	{
		//�����������
		if (KeyDown(_getch()))
		{
			DrawGameBox();
			RandomNum();
			DrawNums();
			Step++;

			//ʤ����ʧ��,һ����Ϸ����
			if (IfWin() || IfLose())
			{
				GotoXY(20, 20);
				Color(12);
				printf("�����룺��1.����һ�� 2.������Ϸ����");
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
	/*��ӡ����2048*/
	Color(11);
	GotoXY(15, 2);
	printf("����������   ����������   ��   ��     ����������");
	GotoXY(15, 3);
	printf("        ��   ��      ��   ��   ��     ��      ��");
	GotoXY(15, 4);
	printf("        ��   ��      ��   ��   ��     ��      ��");
	GotoXY(15, 5);
	printf("����������   ��      ��   ��   ��     ����������");
	GotoXY(15, 6);
	printf("��           ��      ��   ����������  ��      ��");
	GotoXY(15, 7);
	printf("��           ��      ��        ��     ��      ��");
	GotoXY(15, 8);
	printf("����������   ����������        ��     ����������");

	/*��ӡѡ��˵�*/
	Color(7);
	//��ӡ�߿�
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
	//��ӡѡ��
	Color(15);
	GotoXY(33, 12);
	printf("1.��ʼ��Ϸ");
	GotoXY(33, 15);
	printf("2.��Ϸ����");
	GotoXY(33, 18);
	printf("3.�˳�");
}

//�˵�ѡ��
void MenuChoice()
{
	int n;
	GotoXY(28, 21);
	printf("������[1 2 3]��[ ]\b\b");
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

//������
void main(void)
{
	/*��ѭ��*/
	while (1)
	{
		MainMenu();   //��ʾ�˵�
		MenuChoice();   //ѡ��
		getchar();     //����
		system("cls");
	}
}
