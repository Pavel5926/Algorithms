#pragma warning (disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
//////////////////////////////////////////////////////////////////////////////

/**
 * Возвращает вещественное случайное число, равномерно распределённое
 * на полуоткрытом интервале [a, b).
 *
 * @param a  нижняя граница
 * @param b  верхняя граница
 *
 * @return Случайное число от a до b (не включая верхнюю границу).
 */
double random(double a, double b)
{
	double tmp = 0;
	tmp = (rand() / (double)(RAND_MAX + 1)) * (b - a) + a;
	return tmp;
}
/**
 * Заполняет массив равномерно распределёнными случайными числами.
 *
 * @param arr   массив
 * @param size  количество элементов в массиве
 * @param a     нижняя граница
 * @param b     верхняя граница (не включается в интервал)
 *
 * @see Random()
 */
void fillrandom(double arr[], int size, double a, double b)
{
	int i = 0;
	for (i; i < size; i++)
	{
		arr[i] = random(a, b);
	}
}
/**
 * Печатает элементы массива через запятую в фигурных скобках.
 *
 * @param arr   массив
 * @param size  количество элементов в массиве
 */
void print(double const arr[], int size)
{
	int i = 0;
	for (i; i < size; i++)
	{
		printf("%f\n", arr[i]);
	}
}
/**
 * Строит гистограмму значений элементов массива.
 *
 * Заполняет массив counters[] на основании значений элементов массива arr[],
 * подсчитывая, сколько их попало в соответствующий подынтервал
 * полного интервала [a, b). Элементы массива, не попадающие в указанный
 * интервал от a до b игнорируются.
 *
 * @param arr       массив
 * @param size      количество элементов в массиве
 * @param a         нижняя граница
 * @param b         верхняя граница (не включается в интервал)
 * @param counters     заполняемый массив
 * @param numCounters  количество подынтервалов подсчёта
 */
void buildhistogram(double const arr[], int size, double left, double right, int counters[], int numCounters)
{
	int i = 0;
	int j = 0;
	int index = 0;
	for (int k = 0; k < numCounters; k++)
	{
		counters[k] = 0;
	}
	for (j; j < size; j++)
	{
		index = (int)(((arr[j] - left) / (right - left)) * numCounters);
		counters[index] += 1;
	}

}
/**
 * Печатает элементы массива через запятую в фигурных скобках.
 *
 * @param counters     массив
 * @param numCounters  количество элементов в массиве
 */
void printhistogram(int counters[], int numCounters)
{
	printf("{");
	for (int i = 0; i < numCounters - 1; i++)
	{

		printf("%i, ", counters[i]);
	}
	printf("%i", counters[numCounters - 1]);
	printf("}");
	printf("\n");
}
/**
 * Печатает горизонтальную гистограмму значений элементов массива.
 *
 * @param counters     массив интервалов, содержащий количество элементов,
 *                  попавших в соответствующий подынтервал
 * @param numCounters  количество подынтервалов подсчёта
 * @param width     полная ширина поля вывода гистограммы, в знакоместах
 */
void drawhistogram(int counters[], int numCounters, int width)
{
	int maxamount = 0;
	int k = 0;
	for (int i = 0; i < numCounters; i++)
	{
		if (counters[i] > maxamount)
		{
			maxamount = counters[i];
		}
	}

	for (int j = 0; j < numCounters; j++)
	{
		printf("%i ", j);
		for (k; k < (counters[j] * (double)(width)) / maxamount; k++)
		{
			printf("o");
		}
		for (k; k < width; k++)
			printf("%c", 183);
		printf("\n");
		k = 0;
	}
}
int main(void)
{
	setlocale(LC_CTYPE, "Russian");
	const double RANDOM_MIN = 0.0;
	const double RANDOM_MAX = 0.4;
	const int HIST_LINES = 5;
	const int HIST_LENGTH = 16;
	int size;
	int trash;
	double* numbers = NULL;
	double* hist = NULL;
	//vvodim kol-vo chisel
	printf("vvedite kolichestvo chisel:");
	trash = scanf("%d", &size);

	//vydelyayem pamyat`
	numbers = malloc(size * sizeof(double));
	if (numbers == NULL)
		return 0;
	hist = malloc(HIST_LINES * (sizeof(int)));
	if (hist == NULL)
		return 0;
	fillrandom(numbers, size, RANDOM_MIN, RANDOM_MAX);
	print(numbers, size);
	buildhistogram(numbers, size, RANDOM_MIN, RANDOM_MAX, hist, HIST_LINES);
	printhistogram(hist, HIST_LINES);
	drawhistogram(hist, HIST_LINES, HIST_LENGTH);

	//osvobozhdayem pamyat`
	free(hist);
	free(numbers);
	return 0;
}