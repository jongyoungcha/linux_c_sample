#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int ret = 0;
	
	char* ptr = NULL;
	char input[20];
	long number = 0;
	long randnum = 0;
	long arrnum = 0;
	char* arrbit = 0;
	long* arr1 = NULL;
	long* arr2 = NULL;

	int i = 0;
	int j = 0;
	int seed = 0;

	fgets(input, 20, stdin);
	number = strtol(input, &ptr, 10);
	if (number < 1 && number > 16)
	{
		fprintf(stderr, "number should be between 1 and 16\n");
	}
	arr1 = malloc(sizeof(long) * number);
	arr2 = malloc(sizeof(long) * number);
	
	printf("inputed number : %ld\n", number);
	printf("%ld\n", number = pow(2, number) - 1);

	seed = time(NULL);
	srand(seed);
	for (i=0; i<number; i++)
	{
		printf("randnum = %ld\n", randnum = (rand() % number)+1);
		arr1[i] = randnum;
	}
	printf ("-------------------------\n");
	for (i=0; i<number; i++)
	{
		printf("randnum = %ld\n", randnum = (rand() % number)+1);
		arr2[i] = randnum;
	}

	for (i=0; i<number; i++)
	{
		arrnum = arr1[i] | arr2[i];
		printf("%ld\n", arrnum);
		
		arrbit = malloc(number);
		memset(arrbit, 0x00, number);
		for (j=number-1; j>=0; j--)
		{
			if (arrnum % 2 == 1)
			{
				arrbit[j] = '#';
			}
			else
			{
				arrbit[j] = ' ';
			}
			arrnum = arrnum / 2;
		}
		
		for (j=0; j<number; j++)
		{
			printf("%c", arrbit[j]); 
		}
		
		printf("\n");
	}

	if (arrbit)
	{
		free(arrbit);
	}

	if (arr1)
	{
		free(arr1);
	}

	if (arr2)
	{
		free(arr2);
	}
	
v	return 0;
}
