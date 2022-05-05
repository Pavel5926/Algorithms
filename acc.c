#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
typedef int binary_op_t(int sk, int ak);
int binarysum(int sk, int ak)
{
	sk += ak;
	return sk;
}
int binarymax(int sk, int ak)
{
	if (ak > sk)
		sk = ak;
	return sk;
}
int binaryneg(int sk, int ak)
{
	if (ak < 0)
		sk += 1;
	return sk;
}
int accumulate(int const arr[], int n, int s0, binary_op_t* op) 
{
	for (int i = 0; i < n; i++)
	{
		s0 = op(s0, arr[i]);
	}
	return s0;

}
struct subprogram
{
	binary_op_t* operation;
	char name[4];
};
int random(int a, int b)
{
	int tmp = 0;
	tmp = (rand() % (b - a + 1)) + a;
	return tmp;
}
void fillrandom(int arr[], int size, int a, int b)
{
	int i = 0;
	for (i; i < size; i++)
	{
		arr[i] = random(a, b);
	}
}
void print(int const arr[], int size)
{
	int i = 0;
	for (i; i < size; i++)
	{
		printf("%d\n", arr[i]);
	}
}
int main()
{

	const int RANDOM_MIN = -10;
	const int RANDOM_MAX = 10;
	int size, trash, tmp, counter, i;
	size = trash = counter = i = 0;
	int* numbers = NULL;

	printf("vvedite kolichestvo chisel:");
	trash = scanf("%d", &size);

	numbers = malloc(size * sizeof(int));
	if (numbers == NULL)
		return 0;

	fillrandom(numbers, size, RANDOM_MIN, RANDOM_MAX);
	print(numbers, size);
	struct subprogram massive[3] = { &binarysum,"sum",&binarymax, "max", &binaryneg,"neg" };
	int n = sizeof(massive) / sizeof(massive[0]);
	for (int i = 0; i < n; i++)
	{
		if (i != 1)
		{
			tmp = accumulate(numbers, size, 0, massive[i].operation);
			printf("%s %d\n", massive[i].name, tmp);
		}
		else
		{
			tmp = accumulate(numbers, size, RANDOM_MIN, massive[i].operation);
			printf("%s %d\n", massive[i].name, tmp);
		}
	}

	//trash = accumulate(numbers, size, 0, binarysum);
	//printf("sum %d\n",trash);
	//trash = accumulate(numbers, size, RANDOM_MIN, binarymax);
	//printf("max %d\n", trash);
	//trash = accumulate(numbers, size, 0, binaryneg);
	//printf("neg %d\n", trash);
	//printf("%c", massive[i].name[j]);
}