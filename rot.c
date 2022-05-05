#include <stdio.h>
#pragma warning(disable:4996)
#define N 10
void fill (int arr[], int size)
{
	int i;
	size = N;
	for (i = 0; i < size; i++)
	{
		arr[i] = i;
	}
}
void print (int arr[], int size)
{
	int k = 0;
	size = N;
	for(k; k < size; k++)
	{
		printf("%d",arr[k]);
	}
}
void shift1 (int arr[], int size)
{
	int j,buff;
	size = N;
	buff = arr[0];
	for (j=0;j<size-1;j++)
	{
		arr[j] = arr[j+1];
	}
	arr[size-1] = buff;
}
int shift_ver1(int arr[],int size,int delta)
{
	int l=0;
	size=N;
	if ((delta == 0)||(delta == size))
	{
		return 0;
	}
	for(l;l<delta;l++)
	{
		shift1(arr,size);
	}
}
void reverse (int arr[],int left, int right)
{
	int c;
	while (left < right)
	{
	 c = arr[left]; 
        arr[left] = arr[right]; 
        arr[right] = c; 
        left++; 
        right--;
	}
}
void shift_ver2(int arr[],int size, int delta)
{
	reverse(arr,0,size-1);
	reverse(arr,0,size-delta-1);
	reverse(arr,size-delta,size-1);
}

int main ()
{
	int A[N];
	int del,lef,rig;
	fill (A,N);
	scanf ("%i%i%i",&del,&lef,&rig);
	if (del>N)
	{
		del = del%N;
	}
	shift_ver2(A,N,del);
	//reverse (A,lef,rig);
	print (A,N);
	return 0;
}
		