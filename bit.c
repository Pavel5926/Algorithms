#include <stdio.h>
#include <math.h>
#include <conio.h>
#pragma warning (disable:4996)
//typedef unsigned char integer_t;
//typedef unsigned short integer_t;
//typedef unsigned int integer_t;
//typedef unsigned long integer_t;
typedef unsigned long long integer_t;
typedef unsigned long long maxint;

integer_t to2 (integer_t nubmer)
{
	int i;
	integer_t b = nubmer;
	for (i = 0; i < sizeof(nubmer) * 8; i++)
	{	
		printf("%llu", (b & ((maxint)1 << (sizeof(nubmer) * 8 - 1))) >> (sizeof(nubmer) * 8 - 1));
		b = b<<1;
		if (i% 8 == 0)
		{
			printf(" ");
		}
			
	}
	return b;
}
integer_t cycleRot (integer_t number, int delta)
{
	while (delta>(sizeof(number)*8))
	{
		delta = delta%(sizeof(number)*8);
	}
		number = (number<<delta) | (number>>((sizeof(number)*8)-delta));
		return number;
	
}
int main ()
{
	maxint B;
	integer_t b,c,d,cycleres;
	int l, lenf, lens, delen, absdelen;
	lenf = lens = 0;
	
	printf("VVEDITE CHISLO:");
	scanf("%llu", &B);
	b = (integer_t)B;
	printf("VVEDITE DELTA:");
	scanf("%u", &l);
	c = b;
	while (B)
	{
	while (c)
	{
		c/=10;
		lenf++;
	}
	cycleres = cycleRot(b,l);
	d = cycleres;
	while (d)
	{
		d/=10;
		lens++;
	}  
	delen = lenf - lens;
	printf("%d, %d\n",lenf,lens);
	if (lenf < lens)
	{	
		absdelen = delen*(-1);
		printf("VI VVELI:");
		for(int j = 0; j < absdelen; j++)
		{
			printf(" ");
		}
		printf("%llu = Ox%0*X = ", (maxint)b, sizeof(b) * 2, (maxint)b);
		to2(b);
		printf("\n");
		printf("  RESULT:%llu = Ox%0*X = ", (maxint)cycleres, sizeof(cycleres) * 2, (maxint)cycleres);
		to2(cycleres);
		printf("\n");
		lenf = lens = delen = 0;
	}
	else 
	{
		printf("VI VVELI:%llu = Ox%0*X = ", (maxint)b, sizeof(b) * 2, (maxint)b);
		to2(b);
		printf("\n");
		printf("  RESULT:");
		for (int i = 0; i < delen; i++)
		{
			printf(" ");
		}
		printf("%llu = Ox%0*X = ", (maxint)cycleres, sizeof(cycleres) * 2, (maxint)cycleres);
		to2(cycleres);
		printf("\n");
		lenf = lens = delen = 0;
	}
	printf("VVEDITE CHISLO:");
	scanf("%llu", &B);
	b = (integer_t)B;
	printf("VVEDITE DELTA:");
	scanf("%u", &l);
	c = b;
	
	}
		printf("VI VVELI:0 = Ox0 = 0");
		printf("\n");
		printf("  RESULT:0 = Ox0 = 0 ");
		printf("\n");
	
}
