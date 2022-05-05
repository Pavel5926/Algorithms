#include <stdio.h>
#include <stdlib.h>
char* readline (void)
{
	int symbol,i,k; 
	char *arr;
	char *tmp;
	int byte = 0;
	
	int l = 1 * sizeof(char);
	arr=(char*)malloc(l);
	if (arr == 0)
	{
		printf("OS didn`t give a memory");
		return 0;
	}
	
	while (1)
	{
		printf ("BBEDNTE CTPOKY:");
		symbol = getchar();
		if(symbol == '\n')
		{
			return 0;
		}
		while (symbol != '\n')	
		{
			byte++;
			tmp =(char*) realloc  (arr, (byte + 1)*sizeof (char));
			arr = tmp;
			arr[byte-1] = symbol;	
			//printf("%c", (char)arr[byte-1]);
			printf("");
			fflush(stdout);
			symbol=getchar();
		
		}
		for (i = 0; i < (byte); i++)
		{
			if ( ((char)arr[i]>='a' && (char)arr[i]<='z') || ((char)arr[i]>='A' && (char)arr[i]<='Z')|| ((char)arr[i]>='0' && (char)arr[i]<='9') )
			{
				k = i;
			}
		
		}
		for (i = 0; i < byte-1 ; i++)
		{
			if (( ((char)arr[i]>='a' && (char)arr[i]<='z') || ((char)arr[i]>='A' && (char)arr[i]<='Z')|| ((char)arr[i]>='0' && (char)arr[i]<='9') )&&(i < k))
			{
				printf ("%c, ", (char)arr[i]);
			}
		}
		if ( ((char)arr[k]>='a' && (char)arr[k]<='z') || ((char)arr[k]>='A' && (char)arr[k]<='Z')|| ((char)arr[k]>='0' && (char)arr[k]<='9') )
		{
		printf("%c",arr[k]);
		}
		printf("\n");
		arr = (char*)malloc(l);
		byte = 0;
		k = 0;
		if (arr == 0)
		{
		printf("OS didn`t give a memory");
		return 0;
		}
		
	}
	}

int main ()
{	
	readline();
}
