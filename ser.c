#include <stdio.h>
#include <math.h>
void printTable (double a, double b, int m)
{
	double u, s, v, x, f, g, delta;
	int i,k = 0;
	x = a;
	printf ("+-----------+-----------+-----------+-----------+--------------+\n");
	printf ("|i          |x          |f(x)       |g(x)       |delta         |\n");
	printf ("+-----------+-----------+-----------+-----------+--------------+\n");
	for (i = 0; i < m; i++)
	{	
		u = pow(x,2);
		g = pow(sin(x), 2);
		while ((s + u) != s)
		{
			k++;
			s += u;
			v = ((-4)*pow(x,2))/((2*k+1)*(2*k+2));
			u *= v;
			delta = fabs(s - g);
		}
		if (x >= 0){
			printf ("|%d          | %6lf  |%lf   |%lf   | %le|\n",i, x, s, g, delta);
		printf ("+-----------+-----------+-----------+-----------+--------------+\n");}
		else{
				printf ("|%d          | %6lf |%lf   |%lf   | %le|\n",i, x, s, g, delta);
				printf ("+-----------+-----------+-----------+-----------+--------------+\n");
			}
		s = 0;
		u = 0;
		k = 0;
		x += (b - a)/(m-1);
		
	}
	
	
}

int main ()
{	double A,B;
	int M;
	scanf("%lf %lf", &A, &B);
	while (A > 1 || A < (-1))
	{
		printf("enter the correct A:");
		scanf("%lf", &A);
	}
	while (B > 1 || B < (-1))
	{
		printf("enter the correct B:");
		scanf("%lf", &B);
	}
	scanf("%d", &M);
	printTable(A,B,M);
}