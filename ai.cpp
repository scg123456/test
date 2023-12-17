#include<graphics.h>
#include<ai.h>
extern int map[30 * 30][30 * 30];
extern int score[27 * 27][27 * 27];
extern int shuzi1;
extern int storex1[27 * 27];
extern int storey1[27 * 27];
extern struct Po
{
	int r;
	int c;
	int player;
	bool show;
}pos;
int aibeside(int x, int y)
{
	if (map[x + 1][y] == 1 || map[x - 1][y] == 1 || map[x][y + 1] == 1 || map[x][y - 1] == 1)
		return 2;
	if (map[x + 1][y + 1] == 1 || map[x - 1][y + 1] == 1 || map[x - 1][y - 1] == 1 || map[x + 1][y - 1] == 1)
		return 2;
	return 0;
}
int aibeside2(int x, int y)
{
	if (map[x + 1][y] == 1 && map[x + 2][y] == 1)
		return 10;
	if (map[x - 1][y] == 1 && map[x - 2][y] == 1)
		return 10;
	if (map[x][y + 1] == 1 && map[x][y + 2] == 1)
		return 10;
	if (map[x][y - 1] == 1 && map[x][y - 2] == 1)
		return 10;
	if (map[x + 1][y + 1] == 1 && map[x + 2][y + 2] == 1)
		return 10;
	if (map[x - 1][y + 1] == 1 && map[x - 2][y + 2] == 1)
		return 10;
	if (map[x + 1][y - 1] == 1 && map[x + 2][y - 2] == 1)
		return 10;
	if (map[x - 1][y - 1] == 1 && map[x - 2][y - 2] == 1)
		return 10;
	return 0;
}
int aibeside3(int x, int y)
{
	if (map[x + 1][y] == 1 && map[x + 2][y] == 1 && map[x + 3][y] == 1&&map[x+4][y]==2)
		return 100;
	if (map[x - 1][y] == 1 && map[x - 2][y] == 1 && map[x - 3][y] == 1 && map[x - 4][y] == 2)
		return 100;
	if (map[x][y + 1] == 1 && map[x][y + 2] == 1 && map[x][y + 3] == 1 && map[x ][y+4] == 2)
		return 100;
	if (map[x][y - 1] == 1 && map[x][y - 2] == 1 && map[x][y - 3] == 1 && map[x][y - 4] == 2)
		return 100;
	if (map[x - 1][y - 1] == 1 && map[x - 2][y - 2] == 1 && map[x - 3][y - 3] == 1 && map[x-4][y - 4] == 2)
		return 100;
	if (map[x - 1][y + 1] == 1 && map[x - 2][y + 2] == 1 && map[x - 3][y + 3] == 1 && map[x - 4][y + 4] == 2)
		return 100;
	if (map[x + 1][y - 1] == 1 && map[x + 2][y - 2] == 1 && map[x + 3][y - 3] == 1 && map[x + 4][y - 4] == 2)
		return 100;
	if (map[x + 1][y + 1] == 1 && map[x + 2][y + 2] == 1 && map[x + 3][y + 3] == 1 && map[x+ 4][y + 4] == 2)
		return 100;
	if (map[x + 1][y] == 1 && map[x + 2][y] == 1 && map[x + 3][y] == 1 && map[x + 4][y] == 0)
		return 200;
	if (map[x - 1][y] == 1 && map[x - 2][y] == 1 && map[x - 3][y] == 1 && map[x - 4][y] == 0)
		return 200;
	if (map[x][y + 1] == 1 && map[x][y + 2] == 1 && map[x][y + 3] == 1 && map[x][y + 4] == 0)
		return 200;
	if (map[x][y - 1] == 1 && map[x][y - 2] == 1 && map[x][y - 3] == 1 && map[x][y - 4] == 0)
		return 200;
	if (map[x - 1][y - 1] == 1 && map[x - 2][y - 2] == 1 && map[x - 3][y - 3] == 1 && map[x - 4][y - 4] == 0)
		return 200;
	if (map[x - 1][y + 1] == 1 && map[x - 2][y + 2] == 1 && map[x - 3][y + 3] == 1 && map[x - 4][y + 4] == 0)
		return 200;
	if (map[x + 1][y - 1] == 1 && map[x + 2][y - 2] == 1 && map[x + 3][y - 3] == 1 && map[x + 4][y - 4] == 0)
		return 200;
	if (map[x + 1][y + 1] == 1 && map[x + 2][y + 2] == 1 && map[x + 3][y + 3] == 1 && map[x + 4][y + 4] == 0)
		return 200;
	return 0;
}
int aibeside4(int x, int y)
{
	if (map[x + 1][y] == 1 && map[x + 2][y] == 1 && map[x + 3][y] == 1 && map[x + 4][y] == 1)
		return 1500;
	if (map[x - 1][y] == 1 && map[x - 2][y] == 1 && map[x - 3][y] == 1 && map[x - 4][y] == 1)
		return 1500;
	if (map[x][y + 1] == 1 && map[x][y + 2] == 1 && map[x][y + 3] == 1 && map[x][y + 4] == 1)
		return 1500;
	if (map[x][y - 1] == 1 && map[x][y - 2] == 1 && map[x][y - 3] == 1 && map[x][y - 4] == 1)
		return 1500;
	if (map[x - 1][y - 1] == 1 && map[x - 2][y - 2] == 1 && map[x - 3][y - 3] == 1 && map[x - 4][y - 4] == 1)
		return 1500;
	if (map[x - 1][y + 1] == 1 && map[x - 2][y + 2] == 1 && map[x - 3][y + 3] == 1 && map[x - 4][y + 4] == 1)
		return 1500;
	if (map[x + 1][y - 1] == 1 && map[x + 2][y - 2] == 1 && map[x + 3][y - 3] == 1 && map[x + 4][y - 4] == 1)
		return 1500;
	if (map[x + 1][y + 1] == 1 && map[x + 2][y + 2] == 1 && map[x + 3][y + 3] == 1 && map[x + 4][y + 4] == 1)
		return 1500;
	return 0;
}
int corner(int x, int y)
{
	if (x == 1 || y == 1 || x == 27 || y == 27)
		return -1;
	return 0;
}
int attack(int x, int y)
{
	if (map[x + 1][y] == 2 && map[x + 2][y] == 2 && map[x + 3][y] == 2&&map[x+4][y]==1)
		return 1000;
	if (map[x - 1][y] == 2 && map[x - 2][y] == 2 && map[x - 3][y] == 2 && map[x - 4][y] == 1)
		return 1000;
	if (map[x][y + 1] == 2 && map[x][y + 2] == 2 && map[x][y + 3] == 2 && map[x ][y + 4] == 1)
		return 1000;
	if (map[x][y - 1] == 2 && map[x][y - 2] == 2 && map[x][y - 3] == 2 && map[x ][y - 4] == 1)
		return 1000;
	if (map[x - 1][y - 1] == 2 && map[x - 2][y - 2] == 2 && map[x - 3][y - 3] == 2 && map[x-4][y - 4] == 1)
		return 1000;
	if (map[x - 1][y + 1] == 2 && map[x - 2][y + 2] == 2 && map[x - 3][y + 3] == 2 && map[x - 4][y + 4] == 1)
		return 1000;
	if (map[x + 1][y - 1] == 2 && map[x + 2][y - 2] == 2 && map[x + 3][y - 3] == 2 && map[x + 4][y - 4] == 1)
		return 1000;
	if (map[x + 1][y + 1] == 2 && map[x + 2][y + 2] == 2 && map[x + 3][y + 3] == 2 && map[x + 4][y + 4] == 1)
		return 1000;
	if (map[x + 1][y] == 2 && map[x + 2][y] == 2 && map[x + 3][y] == 2&&map[x+4][y]!=1)
		return 1200;
	if (map[x - 1][y] == 2 && map[x - 2][y] == 2 && map[x - 3][y] == 2 && map[x - 4][y] != 1)
		return 1200;
	if (map[x][y + 1] == 2 && map[x][y + 2] == 2 && map[x][y + 3] == 2 && map[x ][y + 4] != 1)
		return 1200;
	if (map[x][y - 1] == 2 && map[x][y - 2] == 2 && map[x][y - 3] == 2 && map[x ][y- 4] != 1)
		return 1200;
	if (map[x - 1][y - 1] == 2 && map[x - 2][y - 2] == 2 && map[x - 3][y - 3] == 2 && map[x-4][y - 4] != 1)
		return 1200;
	if (map[x - 1][y + 1] == 2 && map[x - 2][y + 2] == 2 && map[x - 3][y + 3] == 2 && map[x - 4][y + 4] != 1)
		return 1200;
	if (map[x + 1][y - 1] == 2 && map[x + 2][y - 2] == 2 && map[x + 3][y - 3] == 2 && map[x+ 4][y - 4] != 1)
		return 1200;
	if (map[x + 1][y + 1] == 2 && map[x + 2][y + 2] == 2 && map[x + 3][y + 3] == 2 && map[x + 4][y + 4] != 1)
		return 1200;
	if (map[x + 1][y] == 2 && map[x + 2][y] == 2 && map[x + 3][y] == 2&&map[x+4][y]==2)
		return 10000;
	if (map[x - 1][y] == 2 && map[x - 2][y] == 2 && map[x - 3][y] == 2&&map[x-4][y]==2)
		return 10000;
	if (map[x][y + 1] == 2 && map[x][y + 2] == 2 && map[x][y + 3] == 2&&map[x][y+4])
		return 10000;
	if (map[x][y - 1] == 2 && map[x][y - 2] == 2 && map[x][y - 3] == 2&&map[y][y-4])
		return 10000;
	if (map[x - 1][y - 1] == 2 && map[x - 2][y - 2] == 2 && map[x - 3][y - 3] == 2&&map[x-4][y-4])
		return 10000;
	if (map[x - 1][y + 1] == 2 && map[x - 2][y + 2] == 2 && map[x - 3][y + 3] == 2&&map[x-4][y+4])
		return 10000;
	if (map[x + 1][y - 1] == 2 && map[x + 2][y - 2] == 2 && map[x + 3][y - 3] == 2&&map[x+4][y-4])
		return 10000;
	if (map[x + 1][y + 1] == 2 && map[x + 2][y + 2] == 2 && map[x + 3][y + 3] == 2&&map[x+4][y+4])
		return 10000;
	return 0;
}
void ai()
{
	for (int i = 1; i <= 27; i++)
	{
		for (int j = 1; j <= 27; j++)
		{
			if (map[i][j] != 0)
			{
				score[i][j] = -1;
				continue;
			}
			score[i][j] =score[i][j] + aibeside(i, j) + aibeside2(i, j) + aibeside3(i, j) + aibeside4(i, j) + attack(i, j) + corner(i, j);
		}
	}
back:
	int maxx = 0, maxy = 0, maxscore = 0;
	for (int j = 1; j <= 27; j++)
	{
		for (int i = 1; i <= 27; i++)
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
	storex1[shuzi1] = maxy;
	storey1[shuzi1] = maxx;
	shuzi1++;
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
}