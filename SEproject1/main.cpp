#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <graphics.h>

#define PI	3.14159265
#define LEFT	150	//����������߽�
#define TOP		50	//���������ϱ߽�
#define RIGHT	650	//���������ұ߽�
#define BOTTOM	550	//���������±߽�

int m;		//Բ������
double max_proportion = 0;	//��������������
struct circle	//Բ
{
	int x;	//������
	int y;	//������
	int radius;	//�뾶
}*mu, temp;

int isCovered(struct circle A, struct circle B)	//�ж�����Բ�Ƿ��ཻ
{
	int distance = sqrt(pow((float)A.x - B.x, 2) + pow((float)A.y - B.y, 2));	//����Բ�ļ��
	if (distance < A.radius + B.radius)
		return 1;
	else
		return 0;
}

int main()
{
	while (1)	//����Բ������
	{
		printf("����Բ������:");
		scanf("%d", &m);

		if (m <= 0)
			printf("���������0��������\n");
		else
			break;
	}
	//��ʼ��Բ
	mu = (struct circle *)malloc(m * sizeof(struct circle));
	for (int i = 0; i < m; i++)
	{
		mu[i].x = 0;
		mu[i].y = 0;
		mu[i].radius = 0;
	}

	initgraph(800, 600);
	//������������
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
					for (int i = 0; i < k; i++)	//����Ƿ�������Բ�ص�
					{
						if (isCovered(mu[i], temp))
						{
							stop = 1;
							break;
						}
					}
					if (stop == 1)
						break;

					if (mu[k].radius < r)	//���µ�ǰ����Բ
						mu[k] = {x, y, r};
				}
			}
		}
		circle(mu[k].x, mu[k].y, mu[k].radius);	//����������õ�Բ
	}

	for (int i = 0; i < m; i++)
	{
		max_proportion += PI * pow(2.0 * mu[i].radius / (RIGHT - LEFT), 2);
	}
	char str[20];
	sprintf(str, "�������:%lf", max_proportion);
	outtextxy(10, 10, str);

	_getch();
	return 0;
}