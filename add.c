#include <stdio.h>
#include <math.h>
#define LENGTH 10
#pragma warning (disable:4996)
void null (int x[], int y[],int xy[], int length)
{ 
	for (int e = 0; e < length; e++)
	{
	 x[e] = 0;
	 y[e] = 0;
	 xy[e] = 0;
	}
}
int fill (int number,int digits[],int length)
{ 
	int i = 0 ;
	while (number)
	{	
		digits[i] = number % 10;
		number = number/10;
		i++ ;
	}
	return ( i );
	
}
void print (int const digits[], int length, int max)
{int a = 0, b = length -1 ;
	
		if ( max > length )
	{ 
	    a = max - length ; 
	    for ( a; a > 0; a-- ) 
	    { 
	    printf("  ") ;
        }   
	}
	
	for ( b; b > -1; b--)
	{
	    printf(" %d", digits[b]) ;	
	}
	

	
	printf("\n") ;	
}
	int add (int x[],int y[], int xy[],int length, int diff)
	{int ost = 0;
		for(int k = 0; k < length; k++)
		{
			xy[k] = (x[k] + y[k] + ost)%10;
			ost = (x[k] + y[k] + ost) / 10;
		}
		if (xy[diff]>=0) 
		{
			diff++;
		}
		return (diff);
	}
	int collect (int digits[],int number, int length)
	{  
		for (int m = 0; m < length; m++)
		{
			number+=(digits[length-m-1]*pow(10,(length-m-1)));
		}
		return(number);
	}	
	int main ()
	{ int n,a, A[LENGTH], b, B[LENGTH], c, C[LENGTH],q = 0,qp,DIFF,zf,zs;
	
		scanf("%i\n%i",&a,&b);
		null (A,B,C,LENGTH);
		zf = fill(a,A,LENGTH);
		zs = fill(b,B,LENGTH);
		DIFF = fmax(zf,zs);
		add  (A,B,C,DIFF+1,DIFF+1);
		print (A,zf,DIFF);
		printf("+\n");
		print (B,zs,DIFF);
		for (n=0;n<DIFF;n++)
		{
			printf("--");
		}
		printf("\n");
		print (C,DIFF,DIFF);
		collect (C,q,LENGTH);
		qp=a+b;
		if ( q = qp )
	{
	    printf("right counted");
	}
	else 
	{
	    printf("not right counted");
	}
	return 0;
	}