#include <math.h>
#include <stdio.h>
#include "labengine.h"
#define KMAX 7
#define MAX_DISTANCE    2.0
#define MAX_ITERATIONS  1023

typedef struct {
    double x, y;
} point_t;

typedef struct {
    point_t a, b;
} rect_t;

typedef struct {
    rect_t screen;
    rect_t math;
} viewport_t;

//a color set to apply in the new MAN task

typedef struct {
  unsigned char r, g, b;
} color_t;

static color_t s_palette[] = {
  {0x00, 0x00, 0xFF},
  {0x00, 0xFF, 0xFF},
  {0xFF, 0xFF, 0x00},
  {0xFF, 0x00, 0x00},
  {0xFF, 0xFF, 0x00},
  {0x00, 0xFF, 0xFF},
  {0x00, 0x00, 0xFF},
};

const int MAX_COLORS = sizeof(s_palette) / sizeof(s_palette[0]);

point_t Transform(point_t p, rect_t const* from, rect_t const* to) {
    point_t res = {
      to->a.x + (p.x - from->a.x) * (to->b.x - to->a.x) / (from->b.x - from->a.x),
      to->a.y + (p.y - from->a.y) * (to->b.y - to->a.y) / (from->b.y - from->a.y)
    };
    return res;
}


void DrawAxes(viewport_t const* view) {
    point_t a = view->screen.a;
    point_t b = view->screen.b;
    point_t zero = { 0.0, 0.0 };
    zero = Transform(zero, &view->math, &view->screen);
    LabDrawRectangle((int)a.x, (int)a.y, (int)b.x + 1, (int)b.y + 1);
    if (zero.x >= a.x && zero.x <= b.x)
        LabDrawLine((int)zero.x, (int)a.y, (int)zero.x, (int)b.y + 1);
    if (zero.y >= a.y && zero.y <= b.y)
        LabDrawLine((int)a.x, (int)zero.y, (int)b.x + 1, (int)zero.y);
}

labbool_t IsInsideDisk(point_t p, point_t arg) {
    return p.x * p.x + p.y * p.y < 1.0;
}

int IsInsideJulia(point_t p, point_t arg) {
    int i;
    point_t c = arg;
    point_t z = p;
    double t;

    for (i = 0; i < MAX_ITERATIONS; i++) {
        if (z.x * z.x + z.y * z.y > MAX_DISTANCE * MAX_DISTANCE)
            return MAX_ITERATIONS - i;

        t = 2 * z.x * z.y + c.y;
        z.x = z.x * z.x - z.y * z.y + c.x;
        z.y = t;
    }

    return MAX_ITERATIONS - i;
}
int IsOutsideMandelbrot(point_t p, point_t arg) {
    int i;
    point_t c = p;
    point_t z = { 0,0 };
    double t;

    for (i = 0; i < MAX_ITERATIONS; i++) {
        if (z.x * z.x + z.y * z.y > MAX_DISTANCE * MAX_DISTANCE)
        {
            return MAX_ITERATIONS - i;
        }

        t = 2 * z.x * z.y + c.y;
        z.x = z.x * z.x - z.y * z.y + c.x;
        z.y = t;
    }

    return MAX_ITERATIONS - i;
}

void DrawSet(viewport_t const* view, labbool_t(*isInside)(point_t, point_t), point_t arg) {
    int n = 0;
    int k = 0;
    double x, y, t,alpha;
    point_t p;
    for (x = view->screen.a.x; x <= view->screen.b.x; x++) {
        for (y = view->screen.a.y; y <= view->screen.b.y; y++) {
            p.x = x;
            p.y = y;
            p = Transform(p, &view->screen, &view->math);
            n = isInside(p, arg);
            if (n != 0) {
                t = (double)n / (double)(MAX_ITERATIONS + 1);
                t = t * t * t;
                k = floor(t * (KMAX - 1));
                alpha = t * (KMAX - 1) - floor(t * (KMAX - 1));
                //printf("Color: %i, %lf\n", k,alpha);
                color_t Color;
                Color.r = (1 - alpha) * s_palette[k].r + alpha * s_palette[k + 1].r;
                Color.g = (1 - alpha) * s_palette[k].g + alpha * s_palette[k + 1].g;
                Color.b = (1 - alpha) * s_palette[k].b + alpha * s_palette[k + 1].b;
                LabSetColorRGB(Color.r, Color.g, Color.b);
                LabDrawPoint((int)x, (int)y);
            }
            /*if (n != 0)
            {
                if (n % 2 == 0)
                {
                    LabSetColor(LABCOLOR_DARK_CYAN);
                }
                else
                {
                    LabSetColor(LABCOLOR_WHITE);
                }
                LabDrawPoint((int)x, (int)y);
            }*/
        }
    }
}

void Run(void)
{
    int width = LabGetWidth();
    int height = LabGetHeight();
    viewport_t view[2] = { {
      {0.0, 0.0, (double)(width / 2 - 1), (double)(height - 1)},
      {-2.0, 3.0, 2.0, -3.0},
    }, {
      {(double)(width / 2), 0.0, (double)(width - 1), (double)(height - 1)},
      {-0.7454356, 0.1129986, -0.7454215, 0.113019},
    } };
    point_t c = { -0.835, 0.2321 };
        DrawAxes(&view[0]);
        DrawSet(&view[0], IsInsideJulia, c);

        DrawAxes(&view[1]);
        DrawSet(&view[1], IsOutsideMandelbrot, c);

        LabDrawFlush();
        LabInputKey();
}

int main(void) {
    if (LabInit()) {
        Run();
        LabTerm();
    }
    return 0;
}