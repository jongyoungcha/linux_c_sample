#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_CITY_CNT  100000
#define CITY_REX_RULE "^[[:alpha:]]{1,20}"
#define CITY_DB_PATH  "./city_db.db"

regex_t _regex;
long _cache_size = 0;
char _input[100] = {0, };

int init_regex();

int push_city();
int show_city_list();
int apply_city_LRU();

int init_regex()
{
	int ret = 0;
	ret = regcomp(&_regex, CITY_REX_RULE, REG_EXTENDED);
	if (ret < 0)
	{
		fprintf(stderr, "regcomp() was failed...\n");
		return -1;
	}
	
	return 0;
}

/* int push_cityname(char* city_name) */
/* { */
/* 	int ret = 0; */
/* 	char msgbuf[100] = {0,}; */
/* 	if (city_name) */
/* 	{ */
/* 		ret = regexec(&_regex, city_name, 0, NULL, 0); */
/* 		if (ret == 0) */
/* 		{ */
/* 			fprintf(stdout, "Match\n"); */

/* 			return 0; */
/* 		} */
/* 		else if (ret == REG_NOMATCH) */
/* 		{ */
/* 			fprintf(stderr, "No match\n"); */
/* 			return -1; */
/* 		} */
/* 		else */
/* 		{ */
/* 			regerror(ret, &_regex, msgbuf, sizeof(msgbuf)); */
/* 			fprintf(stderr, "Regex match failed : %s\n", msgbuf); */
/* 			return -1; */
/* 		} */
/* 	} */
/* 	else */
/* 	{ */
/* 		return -1; */
/* 	} */
/* } */


int push_city()
{
	FILE* fp_citydb = NULL;
	int len_city = 0;

	printf("please input the name of city : ");
	fgets(_input, sizeof(_input), stdin);

	len_city = strlen(_input);
	if (len_city < 1 && len_city > 20)
	{
		fprintf(stderr, "cache size should be between 0 and 20.\n");
		return -1;
	}
	
	fp_citydb = fopen(CITY_DB_PATH, "a+");
	
	if (fp_citydb == NULL)
	{
		fprintf(stderr, "Opening DB file was failed...\n");
		return -1;
	}

	fputs(_input, fp_citydb);

	if (fp_citydb)
	{
		fclose(fp_citydb);
	}
	
	return 0;
}

int show_city_list()
{
	FILE* fp_citydb = NULL;
	char city_name_record[20];

	fp_citydb = fopen(CITY_DB_PATH, "r");
	if (fp_citydb == NULL)
	{
		fprintf(stderr, "Opening DB file was failed...\n");
		return -1;
	}

	while(fgets(city_name_record, sizeof(city_name_record), fp_citydb) != NULL)
	{
		printf("** %s", city_name_record);
	}

	/* fgets(city_name_record, sizeof(city_name_record), fp_citydb); */
	/* printf("** %s\n", city_name_record); */
	/* fgets(city_name_record, sizeof(city_name_record), fp_citydb); */
	/* printf("** %s\n", city_name_record); */

	if (fp_citydb)
	{
		fclose(fp_citydb);
	}

	return 0;
}


void set_cache_size()
{
	long cache_size_temp = 0;
	char* ptr_failed = NULL;
	
	printf("please input cache size : ");
	fgets(_input, sizeof(_input), stdin);
	cache_size_temp = strtol(_input, &ptr_failed, 10);
	
	if (cache_size_temp == 0)
	{
		fprintf(stderr, "strtol() was failed...\n");
		return;
	}

	if (cache_size_temp < 0 || cache_size_temp > 30)
	{
		fprintf(stderr, "cache size should be between 0 and 30.\n");
		return;
	}

	_cache_size = cache_size_temp;
	fprintf(stderr, "changing cache size was complete successfully!!!\n");
}


void print_menu()
{
	printf("\n");
	printf("1. push city name.\n");
	printf("2. show city list.\n");
	printf("3. set cache size.\n");
	printf("4. apply cities to cache.\n");
	printf("0. quit.\n");
	printf("\n");
}


int main(int argc, char* argv[])
{
	int ret = 0;
	long selection = 0;
	char* ptr_failed = NULL;

	if (init_regex() < 0)
	{
		exit(EXIT_FAILURE);
	}

	for (;;)
	{
		print_menu();
		printf("please input the number of a feature : ");
		fgets(_input, sizeof(_input), stdin);
		selection = strtol(_input, &ptr_failed, 10);

		switch(selection)
		{
		case 1:
			push_city();
			break;

		case 2:
			show_city_list();
			break;

		case 3:
			set_cache_size();
			break;

		case 4:
			break;

		case 0:
			printf("quit the program...\n");
			exit(EXIT_SUCCESS);
		default:
			printf("please reinput your selection...\n");
			continue;
		}
	}


	return 0;
}
