﻿#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include"ai.h"
int storex[27 * 27] = { 0 };
int creatfile = 1;
int creatfileai = 1;
int storey[27 * 27] = {0};
int a[27 * 27] = {0};
int b[27 * 27] = { 0 };
int c[27 * 27] = { 0 };
int d[27 * 27] = { 0 };
int iow[30][30];
int shuzi = 0;
int yesorno = 0;//开局能否回放
int replay = 0;
int xx = 0;
int step = 1;
int storex1[27 * 27] = { 0 };
int storey1[27 * 27] = { 0 };
int shuzi1 = 0;
int ispoe = 0;
int ispoe1 = 1;
int map[30 * 30][30 * 30] = { 0 };
int score[27 * 27][27 * 27];
struct Po
{
	int r;
	int c;
	int player;
	bool show;
}pos = { -1,-1,black,false };
void ai();
bool judge();
int aibeside(int x, int y);
int win = 0;
int bwin = 0;
int wwin = 0;
int iswho = 1;
int firstwho = 0;
void draw();
void drawback();
void drawback1();
void draw1();
bool isfull();
bool mouspre(ExMessage* message);
void mousepressl(ExMessage* msg);
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
	shuzi = 0;
	shuzi1 = 0;
	for (int i = 0; i < 27 * 27; i++)
	{
		storex[i] = 0;
		storey[i] = 0;
		storex1[i] = 0;
		storey1[i] = 0;
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
	for (int i = 1; i <= 27; i++)
	{
		for (int j = 1; j <= 27; j++)
		{
			score[i][j] = 0;
		}
	}
	shuzi = 0;
	shuzi1 = 0;
	for (int i = 0; i < 27 * 27; i++)
	{
		storex[i] = 0;
		storey[i] = 0;
		storex1[i] = 0;
		storey1[i] = 0;
	}
}
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
void mousepress(ExMessage* msg)
{
	if (ispoe == 1)
	{
		if (msg->message == WM_LBUTTONDOWN)
		{
			if (msg->x > 867 || msg->x > 27 * 27 + 13 && msg->x < 747 || msg->y > 27 * 27 + 13 || msg->x < 14 || msg->y < 14 || msg->y > 27 * 27 + 13 || msg->x < 867 && msg->x>27 * 27 + 13 && msg->y < 500 || msg->x < 867 && msg->x>27 * 27 + 13 && msg->y > 515&&msg->y<575|| msg->x < 867 && msg->x>27 * 27 + 13 && msg->y > 590)
			{
				MessageBox(GetHWnd(), "请在规定区域内下棋。", "提示", MB_OK);
				return;
			}
			if (msg->x > 747 && msg->x < 867 && msg->y>500 && msg->y < 515)
			{
				int box = MessageBox(GetHWnd(), "是否返回主界面", "提示", MB_YESNO);
				if (box == IDYES)
				{
					ispoe = 0;
					init();
					cleardevice();
					bwin = 0;
					wwin = 0;
					iswho = 1;
					pos.player = black;
					return;
				}
				else
					return;
			}
			if (msg->x > 747 && msg->x < 867 && msg->y>575 && msg->y < 590)
			{
					int koi = MessageBox(GetHWnd(), "是否回放对局？", "提示", MB_YESNO);
					if (koi == IDYES)
					{
						if (yesorno == 1)
						{
							init();
							for (int i = 1; i <= 27; i++)
							{
								for (int j = 1; j <= 27; j++)
								{
									iow[i][j] = 0;
								}
							}
							replay = 1;
							xx = 0;
							step = 1;
							for (int i = 0; i < 27 * 27; i++)
							{
								if (a[i] != 0 && b[i] != 0)
								{
									map[b[i]][a[i]] = black;

								}
								if (c[i] != 0 && d[i] != 0)
								{
									map[d[i]][c[i]] = white;
								}
							}
							cleardevice();
							return;
						}
					}
					else
						return;
				
			}
			if (msg->x >= 14 && msg->x <= 27 * 27+13 && msg->y >= 14 && msg->y <= 27 * 27+13)
			{
				if (map[pos.r][pos.c] == 0)
				{
					map[pos.r][pos.c] = pos.player;
					if (pos.player == black)
					{
                               storex[shuzi] = pos.c;
								storey[shuzi] = pos.r;
								shuzi++;
					}		
					else
					{
						storex1[shuzi1] = pos.c;
						storey1[shuzi1] = pos.r;
						shuzi1++;
					}
					if (judge())
					{
						yesorno = 1;
						for (int i = 0; i < 27 * 27; i++)
						{
							a[i] = 0;
							b[i] = 0;
							c[i] = 0;
							d[i] = 0;
						}
						for (int i = 0; i < 27 * 27; i++)
						{
							if (storex[i] != 0 && storey[i] != 0)
							{
								a[i] = storex[i];
								b[i] = storey[i];
							}
							 if (storex1[i] != 0 && storey1[i] != 0)
							{
								c[i] = storex1[i];
								d[i] = storey1[i];
							}
						}
						char a[100];
						sprintf(a, "pvp%d.txt", creatfile);
						creatfile++;
						FILE* fp;
						fp = fopen(a, "w+");
						char str[] = "black:";
						fprintf(fp, "%s", str);
						for (int i = 0; i < 27 * 27; i++)
						{
							if (storex[i] != 0 && storey[i] != 0)
							{
								fprintf(fp, "[%d,%d]", storex[i], storey[i]);
							}
						}
						char str1[] = "white:";
						fprintf(fp, "\n%s", str1);
						for (int i = 0; i < 27 * 27; i++)
						{
							if (storex1[i] != 0 && storey1[i] != 0)
							{
								fprintf(fp, "[%d,%d]", storex1[i], storey1[i]);
							}
						}
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
							firstwho = 1;
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
							firstwho = 2;
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
					if (pos.player == black)
						iswho = 1;
					else
						iswho = 2;
				}
			}	
		}
	}	
}//人人对局
void mousepressl(ExMessage* msg)//人机对局中的按键
{
	if (ispoe == 2)
	{
		if (msg->message == WM_LBUTTONDOWN)
		{
			if (msg->x > 867 || msg->x > 27 * 27 + 13 && msg->x < 747 || msg->y > 27 * 27 + 13 || msg->x < 14 || msg->y < 14 || msg->y > 27 * 27 + 13 || msg->x < 867 && msg->x>27 * 27 + 13 && msg->y < 500 || msg->x < 867 && msg->x>27 * 27 + 13 && msg->y > 515 && msg->y < 575 || msg->x < 867 && msg->x>27 * 27 + 13 && msg->y > 590)
			{
				MessageBox(GetHWnd(), "请在规定区域内下棋。", "提示", MB_OK);
				return;
			}
			if (msg->x > 740 && msg->x < 850 && msg->y>495 && msg->y < 520)
			{
				int box = MessageBox(GetHWnd(), "是否返回主界面", "提示", MB_YESNO);
				if (box == IDYES)
				{
					bwin = 0;
					wwin = 0;
					ispoe = 0;
					init1();
					cleardevice();
				}
				else
					return;
			}
			if (msg->x > 747 && msg->x < 867 && msg->y>575 && msg->y < 590)
			{
				int koi = MessageBox(GetHWnd(), "是否回放对局？", "提示", MB_YESNO);
				if (koi == IDYES)
				{
					if (yesorno == 2)
					{
						init();
						for (int i = 1; i <= 27; i++)
						{
							for (int j = 1; j <= 27; j++)
							{
								iow[i][j] = 0;
							}
						}
						replay = 1;
						xx = 0;
						step = 1;
						for (int i = 0; i < 27 * 27; i++)
						{
							if (a[i] != 0 && b[i] != 0)
							{
								map[b[i]][a[i]] = black;

							}
							if (c[i] != 0 && d[i] != 0)
							{
								map[d[i]][c[i]] = white;
							}
						}
						cleardevice();
						return;
					}

				}
				else
					return;
			}
			if (msg->x >= 14 && msg->x <= 27 * 27 + 13 && msg->y >= 14 && msg->y <= 27 * 27 + 13)
			{
				if (map[pos.r][pos.c] == 0)
				{
					map[pos.r][pos.c] = pos.player;
					if (pos.player == black)
					{
						storex[shuzi] = pos.c;
						storey[shuzi] = pos.r;
						shuzi++;
					}
					if (judge())
					{
						firstwho = 1;
						yesorno = 2;
						for (int i = 0; i < 27 * 27; i++)
						{
							a[i] = 0;
							b[i] = 0;
							c[i] = 0;
							d[i] = 0;
						}
						for (int i = 0; i < 27 * 27; i++)
						{
							if (storex[i] != 0 && storey[i] != 0)
							{
								a[i] = storex[i];
								b[i] = storey[i];
							}
							if (storex1[i] != 0 && storey1[i] != 0)
							{
								c[i] = storex1[i];
								d[i] = storey1[i];
							}
						}
						char b[100];
						sprintf(b, "pve%d.txt", creatfileai);
						creatfileai++;
						FILE* fp;
						fp = fopen(b, "w+");
						char str[] = "black:";
						fprintf(fp, "%s", str);
						for (int i = 0; i < 27 * 27; i++)
						{
							if (storex[i] != 0 && storey[i] != 0)
							{
								fprintf(fp, "[%d,%d]", storex[i], storey[i]);
							}
						}
						char str1[] = "white:";
						fprintf(fp, "\n%s", str1);
						for (int i = 0; i < 27 * 27; i++)
						{
							if (storex1[i] != 0 && storey1[i] != 0)
							{
								fprintf(fp, "[%d,%d]", storex1[i], storey1[i]);
							}
						}
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
							}
							else
							{
								exit(0);
							}
						}
					}
					else
						ispoe1 = 2;
				}
			}
		}
	}
}
void mousepreback(ExMessage* msg)
{
	if (replay == 1)
	{
		if (msg->message == WM_LBUTTONDOWN)
		{
			if (msg->x > 745 && msg->x < 867 && msg->y>500 && msg->y < 515)
			{
				int wow = MessageBox(GetHWnd(), "是否返回游戏？", "提示", MB_YESNO);
				{
					if (wow == IDYES)
					{
						replay = 0;
						xx = 1;
						iswho = firstwho;
						pos.player = firstwho;
					}
					else
						return;
				}
			}
		}
	}
}//对局回放
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
				if (replay == 1)
				{
					while (1)
					{
						BeginBatchDraw();
						drawback();
						EndBatchDraw();
						ExMessage msg1;
						if (peekmessage(&msg1, EM_MOUSE))
						{
							switch (msg1.message)
							{
							case WM_LBUTTONDOWN:
								mousepreback(&msg1);
								break;
							}
						}
						if (xx == 1)
						{
							init();
							break;
						}		
					}
				}
				else
				{
					BeginBatchDraw();
					draw();
					EndBatchDraw();
				}		
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
			while (1) 
			{
				if (replay == 1)
				{
					while (1)
					{
						BeginBatchDraw();
						drawback1();
						EndBatchDraw();
						ExMessage msg1;
						if (peekmessage(&msg1, EM_MOUSE))
						{
							switch (msg1.message)
							{
							case WM_LBUTTONDOWN:
								mousepreback(&msg1);
								break;
							}
						}
						if (xx == 1)
						{
							init();
							break;
						}
					}
				}
				else
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
						firstwho = 2;
						yesorno = 2;
						for (int i = 0; i < 27 * 27; i++)
						{
							a[i] = 0;
							b[i] = 0;
							c[i] = 0;
							d[i] = 0;
						}
						for (int i = 0; i < 27 * 27; i++)
						{
							if (storex[i] != 0 && storey[i] != 0)
							{
								a[i] = storex[i];
								b[i] = storey[i];
							}
							if (storex1[i] != 0 && storey1[i] != 0)
							{
								c[i] = storex1[i];
								d[i] = storey1[i];
							}
						}
						char b[100];
						sprintf(b, "pve%d.txt", creatfileai);
						creatfileai++;
						FILE* fp;
						fp = fopen(b, "w+");
						char str[] = "black:";
						fprintf(fp, "%s", str);
						for (int i = 0; i < 27 * 27; i++)
						{
							if (storex[i] != 0 && storey[i] != 0)
							{
								fprintf(fp, "[%d,%d]", storex[i], storey[i]);
							}
						}
						char str1[] = "white:";
						fprintf(fp, "\n%s", str1);
						for (int i = 0; i < 27 * 27; i++)
						{
							if (storex1[i] != 0 && storey1[i] != 0)
							{
								fprintf(fp, "[%d,%d]", storex1[i], storey1[i]);
							}
						}
						if (win == 2)
						{
							int rex = MessageBox(GetHWnd(), "电脑获胜，是否重新开始游戏？", "提示", MB_YESNO);
							wwin++;
							if (rex == IDYES)
							{
								init1();
								ispoe1 = 1;
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
	if (ispoe == 1)
	SetWindowText(GetHWnd(), "人人对战");
	else if(ispoe==2)
		SetWindowText(GetHWnd(), "人机对战");
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
	settextstyle(15, 15, _T("黑体"));
	outtextxy(747, 575, _T("对局回放"));
	setcolor(BLACK);
	rectangle(747, 575, 867, 590);
	if (ispoe == 1)
	{
		if (iswho == 1)
		{
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(37, 37, _T("黑体"));
			outtextxy(230, 750, _T("该黑棋啦"));
		}
		else if (iswho == 2)
		{
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(37, 37, _T("黑体"));
			outtextxy(230, 750, _T("该白棋啦"));
		}
	}
	else if (ispoe == 2)
	{
		if (iswho == 1)
		{
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(37, 37, _T("黑体"));
			outtextxy(230, 750, _T("黑棋先手"));
		}
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
void drawback()
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
	for (int i = 0; i < 27 * 27; i++)
	{
		if (map[b[i]][a[i]] == black)
		{
			if (iow[b[i]][a[i]] == 0)
				iow[b[i]][a[i]] = step;
			if (iow[b[i]][a[i]] != 0)
			{
				setbkmode(TRANSPARENT);
				settextcolor(RED);
				settextstyle(15, 10, _T("黑体"));
				TCHAR s3[1000];
				_stprintf(s3, _T(" % d"), iow[b[i]][a[i]]);
				outtextxy((a[i]-1) *27 , (b[i]) * 27-10 , s3);
			}
			step++;
		}
		 if (map[d[i]][c[i]] == white)
		{
			if (iow[d[i]][c[i]] == 0)
				iow[d[i]][c[i]] = step;
			if (iow[d[i]][c[i]] != 0)
			{
				setbkmode(TRANSPARENT);
				settextcolor(RED);
				settextstyle(15, 10, _T("黑体"));
				TCHAR s3[1000];
				_stprintf(s3, _T(" % d"), iow[d[i]][c[i]]);
				outtextxy((c[i]-1) * 27, (d[i]) * 27-10, s3);
			}
			step++;
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
	outtextxy(747, 500, _T("返回游戏"));
	setcolor(BLACK);
	rectangle(747, 500, 867, 515);			
}
void drawback1()
{
	SetWindowText(GetHWnd(), "人机对战");
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
	for (int i = 0; i < 27 * 27; i++)
	{
		if (map[b[i]][a[i]] == black)
		{
			if (iow[b[i]][a[i]] == 0)
				iow[b[i]][a[i]] = step;
			if (iow[b[i]][a[i]] != 0)
			{
				setbkmode(TRANSPARENT);
				settextcolor(RED);
				settextstyle(0, 0, _T("黑体"));
				TCHAR s3[1000];
				_stprintf(s3, _T(" % d"), iow[b[i]][a[i]]);
				outtextxy((a[i] - 1) * 27, (b[i]) * 27 -10, s3);
			}
			step++;
		}
		if (map[d[i]][c[i]] == white)
		{
			if (iow[d[i]][c[i]] == 0)
				iow[d[i]][c[i]] = step;
			if (iow[d[i]][c[i]] != 0)
			{
				setbkmode(TRANSPARENT);
				settextcolor(RED);
				settextstyle(0, 0, _T("黑体"));
				TCHAR s3[1000];
				_stprintf(s3, _T(" % d"), iow[d[i]][c[i]]);
				outtextxy((c[i]-1) * 27, d[i] * 27 - 10, s3);
			}
			step++;
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
	outtextxy(747, 500, _T("返回游戏"));
	setcolor(BLACK);
	rectangle(747, 500, 867, 515);
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

