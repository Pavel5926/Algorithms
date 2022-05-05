#pragma warning (disable:4996)
#include <stdio.h>
#define N 9
void MemoryDump(void const* ptr, int size)
{
	unsigned char* p = ptr;
	int i;
	
	for (i = 0; i < size; i++)
	{
		
		
		if (i % 16 == 0)
		{
			printf("\n");
			printf("%p: ", (p+i));
		}
		printf("%02hhX ", *p);
	}
}
void FillInt(int a[], int size) 
{
	int six = 600;
	int i = 0;
	for (i; i < N; i++)
	{
		a[i] = six;
		six += 2;
	}

}
void FillDouble(double a[], int size)
{
	double six = 600;
	int i = 0;
	for (i; i < N; i++)
	{	
		a[i] = six;
		six += 2;
	}
}
void PrintInt(int a[], int size)
{
	int i = 0;
	for (i; i < N; i++)
	{
		printf("%d ", a[i]);
	}
}
void PrintDouble(double a[], int size) 
{
	int i = 0;
	for (i; i < N; i++)
	{
		printf("%f ", a[i]);
	}
}

int main()
{
	int A[N];
	double B[N];
	FillInt(A, N);
	FillDouble(B, N);
	PrintInt(A, N);
	printf("\n");
	PrintDouble(B, N);
	printf("\n");
	MemoryDump(A, sizeof(A));
	printf("\n");
	MemoryDump(B, sizeof(B));
}