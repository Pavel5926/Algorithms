#include "labengine.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
struct rec_description
{
	int xc;
	int yc;
	int num;
	int rad;
	double angle;
};
void line(int width, int height, double angle, int time)
{
	//LabSetColor(LABCOLOR_RED);
	while (!LabInputKeyReady())
	{
		LabDrawLine(width / 2, height / 2, (int)((height / 2) * cos(angle)) + width / 2, (int)((height / 2) * sin(-angle)) + height / 2);
		LabDrawFlush();
		LabDelay(time);
		LabClear();
		angle += 0.1;
		
	}
}
void right_rectangle(struct rec_description * rec)
{
	double angle = 0;
	int time = 40;
	while (!LabInputKeyReady())
	{
		int x0 = (int)((*rec).xc / 2 + ((*rec).rad) * cos(angle));
		int y0 = (int)((*rec).yc / 2 + (*rec).rad * sin(-angle));
		for (int i = 1; i <= (*rec).num; i++)
		{
			int x1 = (int)((*rec).rad * cos(angle + i * M_PI * 2 / (*rec).num) + (*rec).xc / 2);
			int y1 = (int)((*rec).rad * (-sin(angle + i * M_PI * 2 / (*rec).num)) + (*rec).yc / 2);
			//LabSetColor(LABCOLOR_RED);
			LabDrawLine(x0, y0, x1, y1);
			x0 = x1;
			y0 = y1;
		}
		angle += 0.1;
		LabDrawFlush();
		LabDelay(time);
		if (LabInputKeyReady())
		{
			break;
		}
		LabClear();
	}
}
int main(void)
{
	if (LabInit())
	{
		int width = LabGetWidth();
		int height = LabGetHeight();
		double angle = 0;
		int time = 50;
		int radius = height / 2;
		int number = 10;
		struct rec_description rec =
		{
			width,
			height,
			number,
			radius,
			angle
		};
		if (number <= 1)
		{
			printf("error");
			return 0;
		}
		LabSetColor(LABCOLOR_RED);
		//line(width, height, angle, time);
		right_rectangle(&rec);
		LabTerm();
	}
	return 0;
}