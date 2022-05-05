#include <stdio.h>
#include <stdlib.h>
#include "Sor_header.h"
#define N 10

void Print_Array(int arr[], int size)
{
	for (int i = 0; i < size; i++)
		printf("%i ", arr[i]);
	printf("\n");
}
int Left_Insert(int arr[], int sortedsize, int element)
{
	int j = sortedsize;
	while ((j > 0) && (arr[j - 1] > element))
	{
		arr[j] = arr[j - 1];
		j--;
	}
	arr[j] = element;
	return j;
}
void Left_Insertion_Sort(int arr[], int n)
{
	int temp, i, j;
	for (i = 0; i < n ; i++)
	{
		Left_Insert(arr, i, arr[i]);
	}
}
void Right_Insertion_Sort(int arr[], int n)
{
	int temp, i, j;
	for (i = n - 1; i > -1; i--)
	{
		temp = arr[i];
  		j = i;
		while ((j < n-1) && (arr[j+1] < temp))
		{
			arr[j] = arr[j + 1];
			j++;
		}
		arr[j] = temp;
	}
}
void Binary_Insetrion_Sort(int arr[], int n)
{
	int temp, left, right, middle, j;
	j = 0;
	for (int i = 1; i < n; i++)
	{
			temp = arr[i];
			left = 0;
			right = i;
			while (left < right)
			{
				middle = (left + right) / 2;
				if (arr[middle] <= temp)
					left = middle + 1;
				else
					right = middle;
			}
			for (j = i; j > left; j--)
			{
				arr[j] = arr[j - 1];
				//arr[right] = temp;
			}
			arr[right] = temp;
	}
}
void Pairwise_Insertion_Sort(int arr[], int n)
{
	int temp1, temp2, tempmax, tempmin, i, j, k;
	j = 0;
	for (i = 1; i < n; i += 2)
	{
		temp1 = arr[i];
		temp2 = arr[i - 1];
		if (temp1 > temp2)
		{
			tempmax = temp1;
			tempmin = temp2;
		}
		else
		{
			tempmax = temp2;
			tempmin = temp1;
		}
		k = Left_Insert(arr, j, tempmax);
		for (int m = j + 1; m > k; m--)
		{
			arr[m] = arr[m - 1];
		
		}
		//Print_Array(arr, n);
		Left_Insert(arr, k, tempmin);
		//Print_Array(arr, n);
		j += 2;


	}

	
}
void qsortWrap(int arr[], int size) {
	qsort(arr, size, 4, intGt);
}
int intGt(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}
__declspec(dllexport) sort_info_t* GetSortList(int* count)
{
	*count = 5;
	sort_info_t* SortList = malloc(sizeof(sort_info_t) * (*count));
	SortList[0].sort = qsortWrap;
	SortList[0].family = SORT_QUICK;
	SortList[0].complexity = SORT_QUADRATIC;
	SortList[0].name = "Qsort standard library";

	SortList[1].sort = Left_Insertion_Sort;
	SortList[1].family = SORT_INSERTION;
	SortList[1].complexity = SORT_QUADRATIC;
	SortList[1].name = "Left insertion sort";

	SortList[2].sort = Right_Insertion_Sort;
	SortList[2].family = SORT_INSERTION;
	SortList[2].complexity = SORT_QUADRATIC;
	SortList[2].name = "Right insertion sort";

	SortList[3].sort = Binary_Insetrion_Sort;
	SortList[3].family = SORT_INSERTION;
	SortList[3].complexity = SORT_QUADRATIC;
	SortList[3].name = "Binary insertion sort";

	SortList[4].sort = Pairwise_Insertion_Sort;
	SortList[4].family = SORT_INSERTION;
	SortList[4].complexity = SORT_QUADRATIC;
	SortList[4].name = "Pairwise insertion sort";
	return SortList;
}
