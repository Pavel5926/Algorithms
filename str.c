#include <stdio.h>
#include <stdlib.h>

void reverseArray(char str[], int start, int end)
{
    while (start < end) 
	{
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
void swapWords (char str[], int startlet1, int endlet1, int startlet2, int endlet2) 
{
	reverseArray(str, startlet1, endlet1);
	//printf("%s\n", str);
    reverseArray(str, startlet2, endlet2);
	//printf("%s\n", str);
    reverseArray(str, endlet1+1, startlet2-1);
	//printf("%s\n", str);
	reverseArray(str,startlet1, endlet2);
}
int main ()
{ 	int i = 0;
	int firstletind1 = -1 , wordlength1 = -1, firstletind2 = -1, wordlength2 = -1 ;
	char A[150];
	while (1)
	{
	gets(A);
	firstletind1 = -1;
	wordlength1 = -1;
	firstletind2 = -1;
	wordlength2 = -1;
	i = 0;
	if (A[0]==0)
	{	
		break;
	}

	//printf("%s\n",A);
	int l = 0;
	while (A[l])
	l++;
	//printf("%d\n",l);
	while (A[i])
	{
		//для знаков если есть
		while ( (A[i]<='a' || A[i]>='z') && (A[i]<='A' || A[i]>='Z')&&(A[i]<='0' || A[i]>='9') )
		{
			i++;
			
		}
		firstletind1 = i;
		//первое слово
		while ( (A[i+1]>='a' && A[i+1]<='z') || (A[i+1]>='A' && A[i+1]<='Z')|| (A[i+1]>='0' && A[i+1]<='9') )
		{
			i++;
		}
		wordlength1 = i;
		//для знаков
		i++;
		while ( (A[i]<='a' || A[i]>='z') && (A[i]<='A' || A[i]>='Z')&&(A[i]<='0' || A[i]>='9') )
		{
			i++;
		}
		firstletind2 = i;
		//для второго слова
		while ( (A[i+1]>='a' && A[i+1]<='z') || (A[i+1]>='A' && A[i+1]<='Z')||(A[i+1]>='0' && A[i+1]<='9') )
			{
				i ++;
			}
		wordlength2 = i; 
		i++;
		if (((firstletind1 < 0) || (wordlength1 < 0) || (firstletind2 < 0) || (wordlength2 < 0) )|| (i > l))
		{
			break;
		}
		swapWords(A,firstletind1, wordlength1, firstletind2, wordlength2);
	}
	
		printf("%s\n",A);
		
	
	}

}
	