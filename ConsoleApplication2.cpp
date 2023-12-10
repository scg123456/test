#include<stdio.h>
#include<graphics.h>
static int black = 1;
static int white = 2;
bool judge(int r, int c);
int map[27*27][27*27] = {0};
int win = 0;
void draw();
struct Po
{
	int r;
	int c;
	int player;
	bool show;//都是public
}pos = {-1,-1,black,false};
void init()
{
	win = 0;
	pos.player = white;
	pos.show = false;
	for (int i = 1; i <= 27; i++)
	{
		for (int j = 1; j <= 27; j++)
		{
			map[i][j] = 0;
		}
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
void mousepress(ExMessage* msg)
{
	if (msg->message == WM_LBUTTONDOWN)
	{
		if (msg->x > 27*27 || msg->y > 27*27 || msg->x < 27 || msg->y < 27)
		{
			MessageBox(GetHWnd(), (LPCWSTR)L"请在规定区域内下棋。", (LPCWSTR)L"提示", MB_OK);
		}
		if ( map[pos.r][pos.c] == 0)
		{
			map[pos.r][pos.c] = pos.player;
			if (judge(pos.r,pos.c))
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
					int re = MessageBox(GetHWnd(), (LPCWSTR)L"恭喜黑棋获胜，是否重新开始游戏？", (LPCWSTR)L"提示", MB_YESNO);
					if (re == IDYES)
					{
						init();
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
				int re = MessageBox(GetHWnd(), (LPCWSTR)L"恭喜白棋获胜，是否重新开始游戏？", (LPCWSTR)L"提示", MB_YESNO);
				if (re == IDYES)
				{
					init();
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
	initgraph(775, 775);
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
			
	}
	closegraph();
	return 0;
}
void draw()
{
	SetWindowText(GetHWnd(),(LPCWSTR)L"人人对战");
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
	}//若无此段，最后只会五子连珠时显示五个相连的棋子，而不是一个一个显示。
	if (pos.show)
	{
		setcolor(BLUE);
		rectangle((pos.c) * 27 - 13, (pos.r) * 27 - 13, (pos.c + 1) * 27 - 13, (pos.r + 1) * 27 - 13);
	}
}
bool judge(int r,int c)
{
	int play = pos.player;

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