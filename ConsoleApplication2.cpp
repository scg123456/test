#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
int ispoe = 0;
int ispoe1 = 1;
const int black = 1;
const int white = 2;
bool judge();
int map[30*30][30*30] = {0};
int score[27 * 27][27 * 27];
int win = 0;
int bwin = 0;
int wwin = 0;
int iswho = 1;
void draw();
bool isfull();
bool mouspre(ExMessage* message);
void mousepressl(ExMessage* msg);
struct Po
{
	int r;
	int c;
	int player;
	bool show;
}pos = {-1,-1,black,false};
void init()
{
	win = 0;
	pos.show = false;
	for (int i = 1; i <= 27; i++)
	{
		for (int j = 1; j <= 27; j++)
		{
			map[i][j] = 0;
		}
	}
	for (int i = 1; i <= 27; i++)
	{
		for (int j = 1; j <= 27; j++)
		{
			score[i][j] = 0;
		}
	}
}
void init1()
{
	win = 0;
	pos.player = black;
	pos.show = false;
	for (int i = 1; i <= 27; i++)
	{
		for (int j = 1; j <= 27; j++)
		{
			map[i][j] = 0;
		}
	}
}
void draw1();
void ai();
void mousemove(ExMessage* msg)
{
	pos.show = false;
	for (int i = 1; i <= 27; i++)
	{
		for (int j = 1; j <=27; j++)
		{
			int gx = j * 27;
			int gy = i * 27;
			if (abs(msg->x - gx) < 13.5 && abs(msg->y - gy) <13.5)
			{
				pos.show = true;
				pos.r =i;
				pos.c = j;
			}
		}
	}
}
void mousepress(ExMessage* msg)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (msg->x > 867 || msg->x > 27 * 27 + 13 && msg->x < 747 || msg->y > 27 * 27 + 13 || msg->x < 14 || msg->y < 14 || msg->y > 27 * 27 + 13 || msg->x < 867 && msg->x>27 * 27 + 13 && msg->y < 500 || msg->x < 867 && msg->x>27 * 27 + 13 && msg->y > 515)
		{
			MessageBox(GetHWnd(), "请在规定区域内下棋。", "提示", MB_OK);
			return;
		}//747, 500, 867, 515
		if (msg->x > 747 && msg->x < 867 && msg->y>500 && msg->y < 515)
		{
			int box = MessageBox(GetHWnd(), "是否返回主界面", "提示", MB_YESNO);
			if (box == IDYES)
			{
				ispoe = 0;
				init();
				cleardevice();
				return;
			}
			else
				return;
		}
		if ( map[pos.r][pos.c] == 0)
		{
			map[pos.r][pos.c] = pos.player;
			if (judge())
			{
				if(win==1)
				{
					for (int i = 1; i <= 27; i++)
					{
						for (int j = 1; j <= 27; j++)
						{
							if (map[i][j] == black)
							{
								setfillcolor(BLACK);
								solidcircle(j * 27, i * 27, 13);
							}
						}
					}
					int re = MessageBox(GetHWnd(), "恭喜黑棋获胜，是否重新开始游戏？", "提示", MB_YESNO);
					iswho = 1;
					bwin++;
					if (re == IDYES)
					{
						init();
						pos.player = white;
					}
					else
					{
						exit(0);
					}
				}
				if (win == 2)
			{
				for (int i = 1; i <= 27; i++)
				{
					for (int j = 1; j <= 27; j++)
					{
						if (map[i][j] == white)
						{
							setfillcolor(WHITE);
							solidcircle(j * 27, i * 27, 13);
						}
					}
				}
				int re = MessageBox(GetHWnd(), "恭喜白棋获胜，是否重新开始游戏？", "提示", MB_YESNO);
				iswho = 2;
				wwin++;
				if (re == IDYES)
				{
					init1();
					
				}
				else
				{
					exit(0);
					
				}
			}
			}
			pos.player = (pos.player == black ? white : black);
		}
	}
}
int main()
{

	initgraph(875, 800);
	ExMessage message;
	while (1)
	{
		BeginBatchDraw();
		if (ispoe == 0)
		{
			draw1();
		}
		else
			draw();
		EndBatchDraw();
		getmessage(&message);
		if (mouspre(&message))
		{
			goto L;
		}
		if (ispoe == 1)
		{
			while (1)
			{
				BeginBatchDraw();
				draw();
				EndBatchDraw();
				ExMessage msg;
				if (peekmessage(&msg, EM_MOUSE))
				{
					switch (msg.message)
					{
					case WM_MOUSEMOVE:
						mousemove(&msg);
						break;
					case WM_LBUTTONDOWN:
						mousepress(&msg);
						break;
					}
				}
				if (ispoe == 0)
					break;
			}
		}
		else if (ispoe == 2)
		{
			while (1) {
				BeginBatchDraw();
				draw();
				EndBatchDraw();
				ExMessage msg;
				if (ispoe1 == 1) {
					if (peekmessage(&msg, EM_MOUSE)) {
						switch (msg.message) {
						case WM_MOUSEMOVE:
							mousemove(&msg);
							break;
						case WM_LBUTTONDOWN:
							mousepressl(&msg);
							break;
						}
					}
					if (ispoe == 0)
						break;
				}
				else {
					ai();
					if (judge())
					{
						if (win == 2)
						{
							int rex = MessageBox(GetHWnd(), "电脑获胜，是否重新开始游戏？", "提示", MB_YESNO);
							wwin++;
							if (rex == IDYES)
							{
								ispoe1 = 1;
								init();
							}
							else
							{
								exit(0);
							}
						}
					}
					else
						ispoe1 = 1;
				}
			}
		}
	L:;
	}	 
	return 0;
}
void draw1()
{
	SetWindowText(GetHWnd(), "主界面");
	IMAGE bk;
	loadimage(&bk, "resx/nihao.jpg",875,800);
	putimage(0, 0, &bk);
	setlinestyle(PS_SOLID, 2);
	setlinecolor(BLACK);
	rectangle(345, 350, 525, 410);
	rectangle(345, 450, 525, 510);
	rectangle(345, 550, 585, 610);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(100, 100, _T("黑体"));
	outtextxy(150, 125, "五子棋");
	settextstyle(50, 50, _T("黑体"));
	outtextxy(540, 275, "—沈岩");
	settextstyle(60, 60, _T("黑体"));
	outtextxy(345, 350, "PVP");
	settextstyle(60, 60, _T("黑体"));
	outtextxy(345, 450, "PVE");
	settextstyle(60, 60, _T("黑体"));
	outtextxy(345, 550, "EXIT");
}
void draw()
{
	SetWindowText(GetHWnd(), "人人对战");
	int s = 27;
	setbkcolor(RGB(255, 205, 150));
	cleardevice();
	setlinestyle(PS_SOLID, 1);
	setlinecolor(BLACK);
	for (int i = 1; i <= 27; i++)
	{
		line(i * s, 27, i * s, 27 * 27);
		line(27, i * s, 27 * 27, i * s);
	}
	setlinestyle(PS_SOLID, 2);
	rectangle(27, 27, 27 * 27, 27 * 27);
	setfillcolor(BLACK);
	solidcircle(14 * 27, 14 * 27, 4);
	solidcircle(7 * 27, 21 * 27, 4);
	solidcircle(7 * 27, 7 * 27, 4);
	solidcircle(21 * 27, 7 * 27, 4);
	solidcircle(21 * 27, 21 * 27, 4);
	for (int i = 1; i <= 27; i++)
	{
		for (int j = 1; j <= 27; j++)
		{
			
				if (map[i][j] == black)
				{
					setfillcolor(BLACK);
					solidcircle(j * 27, i * 27, 13);
				}
				else if (map[i][j] == white)
				{
					setfillcolor(WHITE);
					solidcircle(j * 27, i * 27, 13);
				}
			
			
		}
	}
	if (pos.show)
	{
		setcolor(BLUE);
		rectangle((pos.c) * 27 - 13, (pos.r) * 27 - 13, (pos.c + 1) * 27 - 13, (pos.r + 1) * 27 - 13);
	}
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(25, 25, _T("黑体"));
	outtextxy(750, 245, _T("得分"));
	settextstyle(17, 17, _T("黑体"));
	TCHAR s1[1000];
	_stprintf(s1, _T(" % d"), bwin);
	outtextxy(747, 300, _T("黑棋："));
	outtextxy(802, 301, s1);
	TCHAR s2[1000];
	_stprintf(s2, _T(" % d"), wwin);
	outtextxy(747, 400, _T("白棋："));
	outtextxy(802, 401, s2);
	settextstyle(15, 15, _T("黑体"));
	outtextxy(747, 500, _T("返回界面"));
	setcolor(BLACK);
	rectangle(747, 500, 867, 515);
	if (iswho == 1)
	{
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		settextstyle(37, 37, _T("黑体"));
		outtextxy(230, 750, _T("黑棋先手"));
	}
	else if (iswho == 2)
	{
		setbkmode(TRANSPARENT);
		settextcolor(BLACK);
		settextstyle(37, 37, _T("黑体"));
		outtextxy(230, 750, _T("白棋先手"));
	}
	if (isfull())
	{
		int re3=MessageBox(GetHWnd(), "平局，是否重新开始", "提示", MB_YESNO);
		if (re3 == IDYES)
		{
			init();
		}
		else
		{
			exit(0);
		}
		pos.player = (pos.player == black ? white : black);
	}	
}
bool judge()
{
	for (int j = 1; j <= 27 && (win == 0); j++)
	{
		for (int i = 1; i <= 27; i++)
		{

			if ((map[j][i] == 1 && map[j][i + 1] == 1 && map[j][i + 2] == 1 && map[j][i + 3] == 1 && map[j][i + 4] == 1)
				|| (map[i][j] == 1 && map[i + 1][j] == 1 && map[i + 2][j] == 1 && map[i + 3][j] == 1 && map[i + 4][j] == 1))
			{
				win = 1;
				return true;
			}
			if ((map[j][i] == 2 && map[j][i + 1] == 2 && map[j][i + 2] == 2 && map[j][i + 3] == 2 && map[j][i + 4] == 2)
				|| (map[i][j] == 2 && map[i + 1][j] == 2 && map[i + 2][j] == 2 && map[i + 3][j] == 2 && map[i + 4][j] == 2))
			{
				win = 2;
				return true;
			}
			if ((map[j][i] == 1 && map[j + 1][i + 1] == 1 && map[j + 2][i + 2] == 1 && map[j + 3][i + 3] == 1 && map[j + 4][i + 4] == 1)
				|| (map[j][i] == 1 && map[j - 1][i + 1] == 1 && map[j - 2][i + 2] == 1 && map[j - 3][i + 3] == 1 && map[j - 4][i + 4] == 1))
			{
				win = 1;
				return true;
			}
			if ((map[j][i] == 2 && map[j + 1][i + 1] == 2 && map[j + 2][i + 2] == 2 && map[j + 3][i + 3] == 2 && map[j + 4][i + 4] == 2)
				|| (map[j][i] == 2 && map[j - 1][i + 1] == 2 && map[j - 2][i + 2] == 2 && map[j - 3][i + 3] == 2 && map[j - 4][i + 4] == 2))
			{
				win = 2;
				return true;
			}
		}
	}

	return false;
}
bool mouspre(ExMessage* message)
{
	if (ispoe == 0)
	{
		if (message->message == WM_LBUTTONDOWN)
		{
			if (message->x > 345 && message->x < 525 && message->y>350 && message->y < 410)
			{
				ispoe = 1;
				cleardevice();
				return true;
			}
			else if (message->x > 345 && message->x < 585 && message->y>550 && message->y < 610)
			{
				int re1 = MessageBox(GetHWnd(), "是否退出", "提示", MB_YESNO);
				if (re1 == IDYES)
				{
					exit(0);
				}
			}
			else if (message->x > 345 && message->x < 525 && message->y>450 && message->y < 510)
			{
				ispoe = 2;
				cleardevice();
				return true;
			}
		}
	}
		
	
	return false;
}
bool isfull()
{
	for (int i = 1; i <= 27; i++)
	{
		for (int j = 1; j <= 27; j++)
		{
			if (map[i][j] == 0)
			{
				return false;
			}
		}
	}
	return true;
}
int aibeside(int x, int y)
{
	if (map[x + 1][y] == 1 || map[x - 1][y] == 1 || map[x][y + 1] == 1 || map[x][y - 1] == 1)return 2;
	if (map[x + 1][y + 1] == 1 || map[x - 1][y + 1] == 1 || map[x - 1][y - 1] == 1 || map[x + 1][y - 1] == 1)return 1;
	return 0;
}
int aibeside2(int x, int y)
{
	if (map[x + 1][y] == 1 && map[x + 2][y] == 1)return 10;
	if (map[x - 1][y] == 1 && map[x - 2][y] == 1)return 10;
	if (map[x][y + 1] == 1 && map[x][y + 2] == 1)return 10;
	if (map[x][y - 1] == 1 && map[x][y - 2] == 1)return 10;
 
	if (map[x + 1][y + 1] == 1 && map[x + 2][y + 2] == 1)return 10;
	if (map[x - 1][y + 1] == 1 && map[x - 2][y + 2] == 1)return 10;
	if (map[x + 1][y - 1] == 1 && map[x + 2][y - 2] == 1)return 10;
	if (map[x - 1][y - 1] == 1 && map[x - 2][y - 2] == 1)return 10;
	return 0;
} 
int aibeside3(int x, int y)
{
	if (map[x + 1][y] == 1 && map[x + 2][y] == 1 && map[x + 3][y] == 1)return 100;
	if (map[x - 1][y] == 1 && map[x - 2][y] == 1 && map[x - 3][y] == 1)return 100;
	if (map[x][y + 1] == 1 && map[x][y + 2] == 1 && map[x][y + 3] == 1)return 100;
	if (map[x][y - 1] == 1 && map[x][y - 2] == 1 && map[x][y - 3] == 1)return 100;
 
	if (map[x - 1][y - 1] == 1 && map[x - 2][y - 2] == 1 && map[x - 3][y - 3] == 1)return 100;
	if (map[x - 1][y + 1] == 1 && map[x - 2][y + 2] == 1 && map[x - 3][y + 3] == 1)return 100;
	if (map[x + 1][y - 1] == 1 && map[x + 2][y - 2] == 1 && map[x + 3][y - 3] == 1)return 100;
	if (map[x + 1][y + 1] == 1 && map[x + 2][y + 2] == 1 && map[x + 3][y + 3] == 1)return 100;
	return 0;
}
int aibeside4(int x, int y)
{
	if (map[x + 1][y] == 1 && map[x + 2][y] == 1 && map[x + 3][y] == 1 && map[x + 4][y] == 1)return 1000;
	if (map[x - 1][y] == 1 && map[x - 2][y] == 1 && map[x - 3][y] == 1 && map[x - 4][y] == 1)return 1000;
	if (map[x][y + 1] == 1 && map[x][y + 2] == 1 && map[x][y + 3] == 1 && map[x][y + 4] == 1)return 1000;
	if (map[x][y - 1] == 1 && map[x][y - 2] == 1 && map[x][y - 3] == 1 && map[x][y - 4] == 1)return 1000;
 
	if (map[x - 1][y - 1] == 1 && map[x - 2][y - 2] == 1 && map[x - 3][y - 3] == 1 && map[x - 4][y - 4] == 1)return 100;
	if (map[x - 1][y + 1] == 1 && map[x - 2][y + 2] == 1 && map[x - 3][y + 3] == 1 && map[x - 4][y + 4] == 1)return 100;
	if (map[x + 1][y - 1] == 1 && map[x + 2][y - 2] == 1 && map[x + 3][y - 3] == 1 && map[x + 4][y - 4] == 1)return 100;
	if (map[x + 1][y + 1] == 1 && map[x + 2][y + 2] == 1 && map[x + 3][y + 3] == 1 && map[x + 4][y + 4] == 1)return 100;
	return 0;
}
int corner(int x, int y)
{
	if (x == 1 || y == 1 || x == 27 || y == 27)return -1;
	return 0;
}
int attack(int x, int y)
{
	if (map[x + 1][y] == 2 && map[x + 2][y] == 2 && map[x + 3][y] == 2)
		return 1000;
	if (map[x - 1][y] == 2 && map[x - 2][y] == 2 && map[x - 3][y] == 2)
		return 1000;
	if (map[x][y + 1] == 2 && map[x][y + 2] == 2 && map[x][y + 3] == 2)
		return 1000;
	if (map[x][y - 1] == 2 && map[x][y - 2] == 2 && map[x][y - 3] == 2)
		return 1000;
	if (map[x - 1][y - 1] == 2 && map[x - 2][y - 2] == 2 && map[x - 3][y - 3] == 2)
		return 1000;
	if (map[x - 1][y + 1] == 2 && map[x - 2][y + 2] == 2 && map[x - 3][y + 3] == 2)
		return 1000;
	if (map[x + 1][y - 1] == 2 && map[x + 2][y - 2] == 2 && map[x + 3][y - 3] == 2)
		return 1000;
	if (map[x + 1][y + 1] == 2 && map[x + 2][y + 2] == 2&& map[x + 3][y + 3] == 2)
		return 1000;
	return 0;
}
void ai()
{
	for (int i = 1; i < 27; i++)
	{
		for (int j = 1; j < 27; j++)
		{
			score[i][j] = 0;
		}
	}
	for (int i = 1; i < 27; i++)
	{
		for (int j = 1; j < 27; j++)
		{
			if (map[i][j] == 2)
			{
				score[i][j] = -1;
				continue;
			}
 
			if (map[i][j] == 1)
			{
				score[i][j] = -1;
				continue;
			}
 
			score[i][j] += aibeside(i, j);
			score[i][j] += aibeside2(i, j);
			score[i][j] += aibeside3(i, j);
			score[i][j] += aibeside4(i, j);
			score[i][j] += corner(i, j);
			score[i][j] += attack(i, j);
		}
	}
 
back:
	int maxx = 0, maxy = 0, maxscore = 0;
	for (int j = 1; j < 27; j++)
	{
		for (int i = 1; i < 27; i++)
		{
			if (score[i][j] > maxscore)
			{
				maxscore = score[i][j];
				maxx = i;
				maxy = j;
			}
		}
	}
	if (map[maxx][maxy] != 0)
	{
		score[maxx][maxy] = 0;
		goto back;
	}
	map[maxx][maxy] = 2;
	for (int i = 1; i <= 27; i++)
	{
		for (int j = 1; j <= 27; j++)
		{
			
				 if (map[i][j] == white)
				{
					setfillcolor(WHITE);
					solidcircle(j * 27, i * 27, 13);
				}
			

		}
	}
	pos.player = (pos.player == black ? white : black);
}
void mousepressl(ExMessage* msg)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (msg->x > 867 || msg->x > 27 * 27 + 13 && msg->x < 747 || msg->y > 27 * 27 + 13 || msg->x < 14 || msg->y < 14 || msg->y > 27 * 27 + 13 || msg->x < 867 && msg->x>27 * 27 + 13 && msg->y < 500 || msg->x < 867 && msg->x>27 * 27 + 13 && msg->y > 515)
		{
			MessageBox(GetHWnd(), "请在规定区域内下棋。", "提示", MB_OK);
			return;
		}//747, 500, 867, 515
		if (msg->x > 747 && msg->x < 867 && msg->y>500 && msg->y < 515)
		{
			int box = MessageBox(GetHWnd(), "是否返回主界面", "提示", MB_YESNO);
			if (box == IDYES)
			{
				ispoe = 0;
				init1();
				cleardevice();
			}
			else
				return;
		}
		if (map[pos.r][pos.c] == 0)
		{
			map[pos.r][pos.c] = pos.player;
			if (judge())
			{
				if (win == 1)
				{
					for (int i = 1; i <= 27; i++)
					{
						for (int j = 1; j <= 27; j++)
						{
							if (map[i][j] == black)
							{
								setfillcolor(BLACK);
								solidcircle(j * 27, i * 27, 13);
							}
						}
					}
					int re = MessageBox(GetHWnd(), "恭喜黑棋获胜，是否重新开始游戏？", "提示", MB_YESNO);
					iswho = 1;
					bwin++;
					if (re == IDYES)
					{
						init();
						ispoe1 = 1;
						pos.player = white;
					}
					else
					{
						exit(0);
					}
				}
				if (win == 2)
				{
					for (int i = 1; i <= 27; i++)
					{
						for (int j = 1; j <= 27; j++)
						{
							if (map[i][j] == white)
							{
								setfillcolor(WHITE);
								solidcircle(j * 27, i * 27, 13);
							}
						}
					}
					int re = MessageBox(GetHWnd(), "恭喜白棋获胜，是否重新开始游戏？", "提示", MB_YESNO);
					iswho = 2;
					wwin++;
					if (re == IDYES)
					{
						init1();

					}
					else
					{
						exit(0);

					}
				}
			}
			else
				ispoe1 = 2;
			pos.player = (pos.player == black ? white : black);
		}
	}
}
