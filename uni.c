#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#pragma warning(disable:4996)
typedef struct {
	float radius;
}Krug_characteristic;

typedef struct {
	float width, height;
} Pryamougolnik_characteristic;

typedef struct {
	int number;
	float length;
} Pravilniy_mnogougolnik_characteristic;

typedef enum {
	KRUG,
	PRYAMOUGOLNIK,
	PRAVILNIY_MNOGOUGOLNIK
} Figure_type;

typedef enum  {
	RED,
	GREEN,
	BLUE
} Color_type;
typedef struct  {
	Figure_type type;
	Color_type color;
	union {
		Krug_characteristic krug;
		Pryamougolnik_characteristic pryamougolnik;
		Pravilniy_mnogougolnik_characteristic pravilniy_mnogougolnik;
	} union_of_figure_characterstic;

}common_figure;
void statistic_form(common_figure* arr, int len)
{
	int form_krug = 0;
	int form_pryamougolnik = 0;
	int form_pravilniy_mnogougolnik = 0;
	for (int i = 0; i < len; i++)
	{
		if (arr[i].type == KRUG)
			form_krug++;
		if (arr[i].type == PRYAMOUGOLNIK)
			form_pryamougolnik++;
		if (arr[i].type == PRAVILNIY_MNOGOUGOLNIK)
			form_pravilniy_mnogougolnik++;
	}
	printf("kolichestvo krugov:%i\nkolichestvo pryamougolnikov:%i\nkolichestvo pravilnykh mnogougolnikov:%i\n", form_krug, form_pryamougolnik, form_pravilniy_mnogougolnik);
}
void statistic_color(common_figure* arr, int len)
{
	int color_red = 0;
	int color_green = 0;
	int color_blue = 0;
	for (int i = 0; i < len; i++)
	{
		if (arr[i].color == RED)
			color_red++;
		if (arr[i].color == GREEN)
			color_green++;
		if (arr[i].color == BLUE)
			color_blue++;
	}
	printf("kolichestvo RED:%i\nkolichestvo GREEN:%i\nkolichestvo BLUE:%i\n", color_red, color_green, color_blue);
}
void square_counter(common_figure* arr, int len)
{
	float S = 0;
	for (int i = 0; i < len; i++)
	{
		if (arr[i].type == KRUG)
			S += (float)((M_PI) * (arr[i].union_of_figure_characterstic.krug.radius) * (arr[i].union_of_figure_characterstic.krug.radius));
		if (arr[i].type == PRYAMOUGOLNIK)
			S += (arr[i].union_of_figure_characterstic.pryamougolnik.width) * (arr[i].union_of_figure_characterstic.pryamougolnik.height);
		if (arr[i].type == PRAVILNIY_MNOGOUGOLNIK)
			S += (float)((arr[i].union_of_figure_characterstic.pravilniy_mnogougolnik.number) * pow(arr[i].union_of_figure_characterstic.pravilniy_mnogougolnik.length, 2)) /
		(float)(4 * tan(M_PI / arr[i].union_of_figure_characterstic.pravilniy_mnogougolnik.number));
	}
	printf("summarnaya ploschad %.3f\n", S);
}
int main()
{
	common_figure* figures;
	const char* file = "C:\\Users\\kachok na masse\\Downloads\\uni_shapes.bin";
	FILE* f = fopen(file, "rb");
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	int length = size / sizeof(common_figure);
	figures = malloc(size);
	if (figures == NULL) {
		printf("Error");
		return 0;
	}
	fread(figures, sizeof(common_figure), length, f);
	printf("%d\n", length);
	printf("%ld\n", sizeof(common_figure));
	statistic_form(figures, length);
	statistic_color(figures, length);
	square_counter(figures, length);
	return 0;
}