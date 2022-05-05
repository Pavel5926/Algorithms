#pragma once
#include <stdio.h>
typedef void (*sort_func_t)(int arr[], int size);
// Семейства сортировок
typedef enum
{
	// (Не определено)
	SORT_NA = -1,
	// Квадратичные
	SORT_SELECTION, SORT_INSERTION, SORT_BUBBLE,
	// Субквадратичные
	SORT_SHELL,
	// Квазилинейные
	SORT_COMB, SORT_MERGE, SORT_QUICK, SORT_HEAP,
	// Линейные
	SORT_COUNT, SORT_RADIX, SORT_BUCKET,
} sort_family_t;
// Вычислительная сложность
typedef enum
{
	SORT_QUADRATIC,
	SORT_SUBQUADRATIC,
	SORT_QUASILINEAR,
	SORT_LINEAR
}sort_complexity_t;
// Описание одной вариации сортировки
typedef struct
{
	sort_func_t sort; // Функция сортировки
	sort_family_t family; // Базовое семейство
	sort_complexity_t complexity; // Вычислительная сложность
	char const* name; // Имя, описывающее вариацию
} sort_info_t;

int Left_Insert(int arr[], int sortedsize, int element);
void Left_Insertion_Sort(int arr[], int n);
void Right_Insertion_Sort(int arr[], int n);
void Binary_Insetrion_Sort(int arr[], int n);
void Pairwise_Insertion_Sort(int arr[], int n);
void qsortWrap(int arr[], int size);
int intGt(const void* a, const void* b);
__declspec(dllexport) sort_info_t* GetSortList(int* count);
