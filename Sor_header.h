#pragma once
#include <stdio.h>
typedef void (*sort_func_t)(int arr[], int size);
// ��������� ����������
typedef enum
{
	// (�� ����������)
	SORT_NA = -1,
	// ������������
	SORT_SELECTION, SORT_INSERTION, SORT_BUBBLE,
	// ���������������
	SORT_SHELL,
	// �������������
	SORT_COMB, SORT_MERGE, SORT_QUICK, SORT_HEAP,
	// ��������
	SORT_COUNT, SORT_RADIX, SORT_BUCKET,
} sort_family_t;
// �������������� ���������
typedef enum
{
	SORT_QUADRATIC,
	SORT_SUBQUADRATIC,
	SORT_QUASILINEAR,
	SORT_LINEAR
}sort_complexity_t;
// �������� ����� �������� ����������
typedef struct
{
	sort_func_t sort; // ������� ����������
	sort_family_t family; // ������� ���������
	sort_complexity_t complexity; // �������������� ���������
	char const* name; // ���, ����������� ��������
} sort_info_t;

int Left_Insert(int arr[], int sortedsize, int element);
void Left_Insertion_Sort(int arr[], int n);
void Right_Insertion_Sort(int arr[], int n);
void Binary_Insetrion_Sort(int arr[], int n);
void Pairwise_Insertion_Sort(int arr[], int n);
void qsortWrap(int arr[], int size);
int intGt(const void* a, const void* b);
__declspec(dllexport) sort_info_t* GetSortList(int* count);
