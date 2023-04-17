#include<stdio.h>
#include<easyx.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#define NODE 40  //每个格子的大小为40

   typedef struct//用于游戏中的主体
   {
	   int x;
	   int y;
    }node;
   typedef enum//枚举蛇移动方向
   {
	   eLeft,
	   eRight,
	   eDown,
	   eUp

   }direction;

   direction d = eRight;
   direction a = eLeft;
   direction w = eUp;
   direction s = eDown;

   //绘制游戏背景函数
   void paintline()
   {

	   for (int i = 0; i <= 800; i += NODE)
	   {
		   line(i, 0, i, 600);
	   }
	   for (int j = 0; j <= 600; j += NODE)
	   {
		   line(0, j, 800, j);
	   }
   }

   //绘制蛇的函数
   void paintsnake(node* snake, int n)
   {
	   int left, top, right, bottom;
	   for (int i1 = 0; i1 < n; i1++)
	   {
		   left = snake[i1].x * NODE;
		   top = snake[i1].y * NODE;
		   right = (snake[i1].x + 1) * NODE;
		   bottom = (snake[i1].y + 1) * NODE;
		   solidrectangle(left,top,right,bottom);
			   
	   }
   }

   //定义蛇移动的函数
   node snakeMove(node* snake, int len,int direct)
   {
	   node lasttail = snake[len - 1];//记录蛇尾数据
	   for (int i2 = len - 1; i2 > 0; i2--)
	   {
		   snake[i2] = snake[i2 - 1];
	   }
	   node newhead;
	   newhead = snake[0];
	   if (direct == eLeft)
	   {
		   newhead.x--;
	   }
	   else if (direct == eUp)
	   {
		   newhead.y--;
	   }
	   else if (direct == eRight)
	   {
		   newhead.x++;
	   }
	   else if(direct==eDown)
	   {
		   newhead.y++;
	   }
	   snake[0] = newhead;
	   return lasttail;//获取蛇尾数据
   }

   //定义蛇移动方向改变的函数
   void directionChange(direction *pd)
   {
	   if (_kbhit() != 0)
	   {
		   
		   char c = _getch();
		   switch (c)
		   {
		   case'w':
			   if (*pd != s)
			   {
				   *pd = w;
			   }
			   break;
		   case's':
			   if (*pd != w)
			   {
				   *pd = s;
			   }
			   break;
		   case'a':
			   if (*pd != d)
			   {
				   *pd = a;
			   }
			   break;
		   case'd':
			   if (*pd != a)
			   {
				   *pd = d;
			   }
			   break;
		   }
	   }
   }

   //确定食物的坐标
   node createfood(node *snake,int lenth)
   {
	   node food;
	   while (1)
	   {
		   food.x = rand() % (800 / NODE);
		   food.y = rand() % (600 / NODE);

		   int i3;
		   for (i3 = 0; i3 < lenth; i3++)
		   {
			   if (snake[i3].x == food.x && snake[i3].y == food.y)
			   {
				   break;
			   }
		   }
		   if (i3 < lenth)
		   {
			   continue;
		   }
		   else
		   {
			   break;
		   }
	   }
	   return food;
   }

   //绘制食物
   void paintFood(node food)
   {
	   int left_food, top_food, right_food, bottom_food;
	   left_food = food.x * NODE;
	   top_food = food.y * NODE;
	   right_food = (food.x + 1) * NODE;
	   bottom_food = (food.y + 1) * NODE;
	   setfillcolor(RGB(254, 255, 0));
	   solidrectangle(left_food, top_food, right_food, bottom_food);
	   
	   
   }

   //判断游戏结束:撞墙、吃到自己
   bool isGameover(node* snake, int Lenth)
   {
	   if (snake[0].x < 0 || snake[0].x>800 / NODE)
	   {
		   return true;
	   }
	   if (snake[0].y < 0 || snake[0].y>600 / NODE)
	   {
		   return true;
		}
	   for (int i4 = 1; i4 < Lenth; i4++)
	   {
		   if (snake[i4].x == snake[0].x && snake[i4].y == snake[0].y)
		   {
			   return true;
		   }
	   }
	   return false;
   }

   //游戏重开，复位
   void rest(node* snake, int* reLenth, direction* reDirect)
   {
	   snake[0] = { 5,7 };
	   snake[1] = { 4,7 };
	   snake[2] = { 3,7 };
	   snake[3] = { 2,7 };
	   snake[4] = { 1,7 };
	   *reLenth = 5;
	   *reDirect = d;

   }

   //主函数体
int main()
{
	//创建一个800*600的窗体
	initgraph(800, 600);
	
	//背景颜色
	setbkcolor(RGB(204, 255, 153));
	cleardevice();

	//绘制线格
	paintline();

	//绘制蛇的初始位置
	node snake[100] = { {5,7},{4,7},{3,7},{2,7},{1,7} };
	int lenth = 5;
	setfillcolor(RGB(255, 229, 229));
	paintsnake(snake, lenth);

	//设置蛇的移动控制为“wasd”
	direction D=d;

	//设置食物
	srand(unsigned int(time(NULL)));
	node food = createfood(snake, lenth);
	paintFood(food);
	while (1)
	{
		cleardevice();
		paintline();
		paintFood(food);
		setfillcolor(RGB(255, 179, 179));
		paintsnake(snake, lenth);
		Sleep(400);

		directionChange(&D);
		node lastTail=snakeMove(snake, lenth, D);
		if (food.x == snake[0].x && food.y == snake[0].y)
		{
			if (lenth < 100)
			{
				snake[lenth] = lastTail;
				lenth++;
			}
			food = createfood(snake, lenth);
		}
		if (isGameover(snake, lenth) == true)
		{
			rest(snake, &lenth, &D);
			food = createfood(snake, lenth);
		}

	}

	getchar();
	closegraph();
	return 0;

}