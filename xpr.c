#include <stdio.h>
#include <math.h>
# define _USE_MATH_DEFINES
int main (void)
{
const int r=500;
double m;
double d;
double l;
printf("Enter weight:");
scanf("%lf", &m);
while (m<=0) {
printf ("enter the correct weigt:");
scanf("%lf", &m);
}
printf("Enter length:");
scanf("%lf", &l);
while (l<=0) {
printf ("enter the correct length:");
scanf("%lf", &l);
}
d=2*sqrt(m/(r*l*M_PI));
printf("result d = %lf", d);
}