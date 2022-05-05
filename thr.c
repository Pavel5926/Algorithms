#include <stdio.h>
#include <windows.h>
#include "labengine.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define WIDTH 640
#define HEIGHT 480
#define alpha M_PI/3
typedef struct
{
	double xc;
	double yc;
} point_t;
typedef struct
{
	double xc;
	double yc;
}vec_t;

typedef struct
{
	point_t A;
	point_t C;
}rect_t;
point_t Transform(point_t p, rect_t const* from, rect_t const* to)
{
	point_t p1;
	p1.xc = to->A.xc + (p.xc - from->A.xc) * (to->C.xc - to->A.xc) / (from->C.xc - from->A.xc);
	p1.yc = to->A.yc + (p.yc - from->A.yc) * (to->C.yc - to->A.yc) / (from->C.yc - from->A.yc);
	return p1;
}
vec_t VecTransform(vec_t p, rect_t const* from, rect_t const* to)
{
	vec_t p1;
	p1.xc = to->A.xc + (p.xc - from->A.xc) * (to->C.xc - to->A.xc) / (from->C.xc - from->A.xc);
	p1.yc = to->A.yc + (p.yc - from->A.yc) * (to->C.yc - to->A.yc) / (from->C.yc - from->A.yc);
	return p1;
}
void DrawAxes(rect_t const* math, rect_t const* screen)
{
	point_t zeroscreen;
	point_t zero = { 0,0 };
	zeroscreen = Transform(zero, math, screen);
	LabDrawLine(zeroscreen.xc + LabGetWidth(), zeroscreen.yc, zeroscreen.xc - LabGetWidth(), zeroscreen.yc);
	LabDrawLine(zeroscreen.xc, zeroscreen.yc + LabGetHeight(), zeroscreen.xc, zeroscreen.yc - LabGetHeight());
	LabDrawFlush();
}
void DrawAnalyticalPath(rect_t const* math, rect_t const* screen, vec_t r0, vec_t v0, vec_t a0, double dt)
{
	double t = 0; 
	point_t r;
	r.xc = r0.xc;
	r.yc = r0.yc;
	point_t temp = { 0,0 };
	point_t r1 = { 0,0 };
	point_t temp1 = { 0,0 };
	double h = fabs(2 * v0.yc / a0.yc);
	while (t < h)
	{
		temp.xc = r0.xc + v0.xc * t;
		temp.yc = r0.yc + v0.yc*t + (a0.yc * t * t / 2);
		temp1 = Transform(temp, math, screen);
		r1 = Transform(r, math, screen);
		//LabSetColor(LABCOLOR_DARK_GREEN);
		LabDrawLine(r1.xc, r1.yc, temp1.xc, temp1.yc);
		LabDrawFlush();
		r.xc = temp.xc;
		r.yc = temp.yc;
		t += dt;
	}
}
void DrawEulerPath(rect_t const* math, rect_t const* screen, vec_t r0, vec_t v0, vec_t a0, double dt)
{
	vec_t v = { v0.xc, v0.yc };
	vec_t r = { r0.xc, r0.yc };
	vec_t rscreen = { 0,0 };
	vec_t rtmpscreen = { 0,0 };
	while (r.yc >= 0)
	{
		vec_t dv = { a0.xc * dt, a0.yc * dt };
		vec_t dr = { v.xc * dt, v.yc * dt };
		vec_t rtmp = { r.xc, r.yc };
		v.xc = v.xc + dv.xc;
		v.yc = v.yc + dv.yc;
		r.xc = r.xc + dr.xc;
		r.yc = r.yc + dr.yc;
		rscreen = VecTransform(r, math, screen);
		rtmpscreen = VecTransform(rtmp, math, screen);
		
		LabDrawLine(rtmpscreen.xc, rtmpscreen.yc, rscreen.xc, rscreen.yc);
	}
}
void DrawSimulateEulerPath(rect_t const* math, rect_t const* screen, vec_t r0, vec_t v0, vec_t a0)
{
	vec_t v = { v0.xc, v0.yc };
	vec_t r = { r0.xc, r0.yc };
	vec_t rscreen = { 0,0 };
	vec_t rtmpscreen = { 0,0 };
	double dt = 0;
	double frequency = 0;
	LARGE_INTEGER clockFrequency, before, after;
	QueryPerformanceFrequency(&clockFrequency);
	//frequency = (double)freq.QuadPart / 1000.0;
	QueryPerformanceCounter(&before);
	while (r.yc >= 0)
	{
		QueryPerformanceCounter(&before);
		vec_t dv = { a0.xc * dt, a0.yc * dt };
		vec_t dr = { v.xc * dt, v.yc * dt };
		vec_t rtmp = { r.xc, r.yc };
		v.xc = v.xc + dv.xc;
		v.yc = v.yc + dv.yc;
		r.xc = r.xc + dr.xc;
		r.yc = r.yc + dr.yc;
		rscreen = VecTransform(r, math, screen);
		rtmpscreen = VecTransform(rtmp, math, screen);
		LabDrawLine(rtmpscreen.xc, rtmpscreen.yc, rscreen.xc, rscreen.yc);
		LabDrawFlush();
		QueryPerformanceCounter(&after);
		dt = (double)(after.QuadPart - before.QuadPart) / (clockFrequency.QuadPart);
	}
}
int main(void)
{
	if (LabInit())
	{
		int width = LabGetWidth();
		int height = LabGetHeight();
		point_t A = { 0,0 };
		point_t C = { width, height };
		point_t ma = { -3, 28 };
		point_t mc = { 41, -5 };
		rect_t screen = { A,C };
		rect_t math = { ma,mc };
		vec_t r0 = { 0,0 };
		vec_t g = { 0,-9.8 };
		vec_t v0 = { 20 * cos(alpha),20 * sin(alpha) };
		double dt = 1;
		DrawAxes(&math, &screen);
		LabSetColor(LABCOLOR_DARK_GREEN);
		DrawAnalyticalPath(&math, &screen, r0, v0, g, dt);
		DrawAnalyticalPath(&math, &screen, r0, v0, g, dt/2);
		LabSetColor(LABCOLOR_RED);
		DrawEulerPath(&math, &screen, r0, v0, g, dt);
		DrawEulerPath(&math, &screen, r0, v0, g, dt/2);
		LabSetColor(LABCOLOR_YELLOW);
		DrawSimulateEulerPath(&math, &screen, r0, v0, g);
		LabDrawFlush();
		LabInputKey();
		LabTerm(); 
	}
}