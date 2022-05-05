#include "labengine.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
typedef struct
{
	int x, y;
} coordinate;
coordinate HalfSum(coordinate a, coordinate b)
{
	a.x = (a.x + b.x) / 2;
	a.y = (a.y + b.y) / 2;
	return a;
}
void Curve(coordinate a, coordinate b, int n)
{
	if (n == 0)
	{
		LabDrawLine(a.x, a.y, b.x, a.y);
		LabDrawLine(b.x, a.y, b.x, b.y);
		LabDrawFlush();
	}
	else
	{
		Curve(a, HalfSum(a, b), (n - 1));
		Curve(HalfSum(a, b), b, (n - 1));
	}
}
coordinate DotB(coordinate a, coordinate e)
{
	coordinate b = { (a.x + (e.x - a.x) * 1 / 3), (a.y + (e.y - a.y) * 1 / 3) };
	return b;
}
coordinate DotD(coordinate a, coordinate e)
{
	coordinate d = { a.x + (e.x - a.x) * 2 / 3, a.y + (e.y - a.y) * 2 / 3 };
	return d;
}
coordinate DotC(coordinate b, coordinate d)
{
	coordinate c = { b.x + (d.x - b.x) * cos(M_PI / 3) + sin(M_PI / 3) * (d.y - b.y), b.y - (d.x - b.x) * sin(M_PI / 3) + cos(M_PI / 3) * (d.y - b.y) };
	return c;
}
void KochDraw(coordinate a, coordinate e, int n)
{
	if (n == 0)
	{
		LabDrawLine(a.x, a.y, e.x, e.y);
		LabDrawFlush();
	}
	else
	{ 
		KochDraw(a, DotB(a, e), n - 1);
		KochDraw(DotB(a, e), DotC(DotB(a, e), DotD(a, e)), n - 1);
		KochDraw(DotC(DotB(a, e), DotD(a, e)), DotD(a, e), n - 1);
		KochDraw(DotD(a, e), e, n - 1); 
	}
}
int main(void)
{
	if (LabInit())
	{
		int width = LabGetWidth();
		int height = LabGetHeight();
		int number = 0;
		labkey_t key;
		coordinate a = { 300,100 }, b = { 300,300 }, c = { a.x + (b.x - a.x) * cos(M_PI / 3) - (b.y - a.y) * sin(M_PI / 3) ,a.y + (b.y - a.y) * cos(M_PI / 3) + (b.x - a.x) * sin(M_PI / 3) };
		KochDraw(a, b, number);
		KochDraw(b, c, number);
		KochDraw(c, a, number);
		while ((key = LabInputKey()) != LABKEY_ESC)
		{
			switch (key) 
			{
			case '+' :
				number++;
				break;
			case '-':
				number--;
				if (number < 0) 
				{
					printf("Error number < 0");
					return 0;
				}
				break;
			}
			LabClear();
			//Curve(a, b, number);
			KochDraw(a, b, number);
			KochDraw(b, c, number);
			KochDraw(c, a, number);
		}
		LabInputKey();
		LabTerm();
	}

	return 0;
}