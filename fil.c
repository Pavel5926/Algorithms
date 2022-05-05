#define N 9
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void FillFloats(float arr[], int length)
{	
	int i = 0;
	srand(time(0));
	for (i; i < N; i++)
	{
		arr[i] = rand() % 100;
	}

}
void PrintFloats(float arr[], int length)
{
	int i = 0;
	printf("{");
	for (i; i < N-1; i++)
	{
		
		printf("%.1f", arr[i]);
		printf(",");
		
	}
	printf("%.1f",arr[i]);
	printf("}\n");
}

void WriteText(char const* filename, float arr[], int length)
{
	int i = 0;
	FILE* f = fopen("massive.txt", "w+");

	for (i; i < N; i++)
	{
		fprintf(f, "%.1f ", arr[i]);
	}
	fclose(f);
}
void WriteBinary(char const *filename, float arr[], int length)
{
	FILE* g = fopen("masbinary.bin","w+");
	fwrite(arr,sizeof(float),N, g);
	fclose(g);
	
}
float* ReadText(char const *filename, int* length)
{	int t = 1;
	float number; 
	float *arr;
	float *tmp;
	int byte =0;
	FILE *h = fopen ("massive.txt", "r+");
	if (h == NULL)
	{
		printf("NOT FOUND");
	}
	int l = 1 * sizeof(float);
	arr=(float*)malloc(l);
	if (arr == 0)
	{
		printf("OS didn`t give a memory");
		return 0;
	}
	
	while (t != EOF)	
	{
		t = fscanf(h,"%f",&number);
		byte++;
		tmp =(float*) realloc  (arr, (byte + 1)*sizeof (float));
		arr = tmp;
		arr[byte-1] = number;	
	}
	fclose(h);
	*length = byte;
	PrintFloats(arr,byte);
	return arr;
}
float* ReadBinary (char const* filename, int* length)
{	
	int size;
	float* arr;
	FILE* k = fopen ("masbinary.bin","rb");
	fseek(k, 0, SEEK_END);
	size = ftell(k);
	fseek (k,0, SEEK_SET);
	*length = size/sizeof(float);
	arr = (float*)malloc(size);
	fread(arr,sizeof(float),*length,k);
	fclose (k);
	PrintFloats(arr,*length);
	return arr;
	
}	void FileDump(char const* filename)
{
	char element;
	FILE* k;
	int i=0;
	k = fopen("masbinary.bin", "rb");
	if (k == NULL)
	{
		printf("File not found");
	}
	element=fgetc(k);
	while(element!= EOF)
	{
		
		if (i % 16 == 0)
		{
			printf("\n");
			printf("%p: ", ftell(k)-1);
		}
		printf("%02hhX ", (unsigned char)element);
		i++;
		if (element ==  EOF)
		{
			return ;
		}
		element=fgetc(k);
	}
	
	fclose(k);
}
int main()
{
	int Length = 0;
	float A[N];
	FillFloats(A, N);
	PrintFloats(A, N);
	WriteText("massive.txt", A, N);
	WriteBinary("masbinary.bin", A, N);
	ReadText("massive.txt",&Length);
	ReadBinary("masbinary.bin",&Length);
	FileDump("massive.txt");
	printf("\n");
	FileDump("masbinary.bin");
}