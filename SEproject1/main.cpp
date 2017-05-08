#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>

#define PI	3.14159265
#define LEFT	150	//矩形区域左边界
#define TOP		50	//矩形区域上边界
#define RIGHT	650	//矩形区域右边界
#define BOTTOM	550	//矩形区域下边界

int m;		//圆的数量
double max_proportion = 0;	//覆盖区域最大面积
struct circle	//圆
{
	int x;	//横坐标
	int y;	//纵坐标
	int radius;	//半径
}*mu, temp;

int isCovered(struct circle A, struct circle B)	//判断两个圆是否相交
{
	int distance = sqrt(pow((float)A.x - B.x, 2) + pow((float)A.y - B.y, 2));	//两个圆心间距
	if (distance < A.radius + B.radius)
		return 1;
	else
		return 0;
}

int main()
{
	while (1)	//输入圆的数量
	{
		printf("输入圆的数量:");
		scanf("%d", &m);

		if (m <= 0)
			printf("请输入大于0的整数！\n");
		else
			break;
	}
	//初始化圆
	mu = (struct circle *)malloc(m * sizeof(struct circle));
	for (int i = 0; i < m; i++)
	{
		mu[i].x = 0;
		mu[i].y = 0;
		mu[i].radius = 0;
	}

	initgraph(800, 600);
	//画出矩形区域
	setcolor(RED);
	rectangle(LEFT, TOP, RIGHT, BOTTOM);
	
	for (int k = 0; k < m; k++)
	{
		for (int x = LEFT + 1; x < RIGHT; x++)
		{
			for (int y = TOP + 1; y < BOTTOM; y++)
			{
				for (int r = 1, stop = 0; r <= x - LEFT && r <= RIGHT - x && r <= y - TOP && r <= BOTTOM - y; r++)
				{
					temp = { x, y, r };
					for (int i = 0; i < k; i++)	//检测是否与现有圆重叠
					{
						if (isCovered(mu[i], temp))
						{
							stop = 1;
							break;
						}
					}
					if (stop == 1)
						break;

					if (mu[k].radius < r)	//更新当前最大的圆
						mu[k] = {x, y, r};
				}
			}
		}
		circle(mu[k].x, mu[k].y, mu[k].radius);	//画出最终算得的圆
	}

	for (int i = 0; i < m; i++)
	{
		max_proportion += PI * pow(2.0 * mu[i].radius / (RIGHT - LEFT), 2);
	}
	char str[20];
	sprintf(str, "覆盖面积:%lf", max_proportion);
	outtextxy(10, 10, str);

	_getch();
	return 0;
}