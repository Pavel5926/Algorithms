#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <Sor_header.h>
#include <locale.h>

#pragma warning(disable:4996)

#define REPEAT_COUNT 10 //���������� ����������
#define MIN_SIZE 1000 //���. ������ �������
#define MAX_SIZE 5000 //����. ������ �������
#define STEP_SIZE 500 //������ ����
#define N (MAX_SIZE - MIN_SIZE) / (STEP_SIZE)+1 //���������� ����������� ��������
//�������� �������
void CreateArr(int arr[], int size, unsigned int seed)
{
	srand(seed);
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 100000;
	}
}
//������ �������
void PrintArray(int arr[], int size)
{
	int i = 0;
	for (i = 0; i < size; i++) {
		printf("%i ", arr[i]);
	}
	printf("\n");
}


double TimeProfile(sort_func_t* sort(int arr, int size), int seed, int size)
{
	LARGE_INTEGER clockFrequency, before, after;
	double delta;
	QueryPerformanceFrequency(&clockFrequency); //������� ����� ����
	int* arr_arr[REPEAT_COUNT];
	for (int i = 0; i < REPEAT_COUNT; i++)
	{
		arr_arr[i] = malloc(size * sizeof(int));
		if (arr_arr[i] == NULL)
		{
			//����� ������������ ������
			perror("");
			return -1;
		}
		//��������� ������� ��� �������. ������� �� ����� ���������������� ����.
		CreateArr(arr_arr[i], size, seed);
	}
	//�������� ������� �� ����������
	QueryPerformanceCounter(&before);
	for (int i = 0; i < REPEAT_COUNT; i++)
	{
		sort(arr_arr[i], size);
	}
	//�������� ������� ����� ����������
	QueryPerformanceCounter(&after);
	delta = (double)(after.QuadPart - before.QuadPart) / (((long long)REPEAT_COUNT) * clockFrequency.QuadPart);

	for (int i = 0; i < REPEAT_COUNT; i++)
	{
		free(arr_arr[i]);
	}
	return delta;
}


int main(void) 
{
	setlocale(LC_ALL, "Russian");
	//�������� ����������
	HMODULE Sort = LoadLibrary(L"SOR_SOURCE.dll");
	if (!Sort)
	{
		exit(-1);
	}
	sort_info_t* (*GetSort) (int*) = (sort_info_t * (*) (int*)) GetProcAddress(Sort, "GetSortList"); //����� GetSortList �� ����������
	int size;
	sort_info_t* SortList = GetSort(&size);
	//�������� �����
	FILE* file = fopen("Sort_Time_Test.csv", "w");
	if (file == NULL)
	{
		printf(" can't open file\n");
		return;
	}
	int arr_seed[N];
	int seed = (int)time(0);
	CreateArr(arr_seed, N, seed);
	double time[N];
	//��������� �������
	fprintf(file, "sort;");
	for (int i = 0; i < N - 1; i++) 
	{
		fprintf(file, "%d;", MIN_SIZE + i * STEP_SIZE);
	}
	fprintf(file, "%d\n", MAX_SIZE);

	for (int j = 0; j < size; j++) 
	{
		for (int i = 0; i < N; i++)
		{
			//������ �����
			time[i] = TimeProfile(SortList[j].sort, arr_seed[i], MIN_SIZE + i * STEP_SIZE);
		}
		//����� �������� ����������
		fprintf(file, "%s%c", SortList[j].name, ';');
		//����� ��������
		for (int i = 0; i < N - 1; i++) 
		{
			fprintf(file, "%.9lf%c", time[i], ';');
		}
		fprintf(file, "%.9lf\n", time[N - 1]);
	}
	fclose(file);
	FreeLibrary(Sort);
	return 0;
}