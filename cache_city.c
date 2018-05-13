#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <glib.h>

#define MAX_CITY_CNT  100000
#define CITY_REX_RULE "^[[:alpha:]]{1,20}"
#define CITY_DB_PATH  "./city_db.db"

typedef struct city_info
{
	int cnt_ref;
	int cache_location;
	char name[20];
} city_info_t;

char* _cache_cities = NULL;
int _crr_cache_sz = 0;

regex_t _regex;
long _cache_size = 10;
char _input[100] = {0,};

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

int init_cache(int cache_size)
{
	int sz_min_cache = 0;
	char* temp_cache = NULL;

	temp_cache = (char*)malloc(sizeof(city_info_t) * cache_size);
	memset(temp_cache, 0x00, sizeof(city_info_t) * cache_size);
	
	if (cache_size > _cache_size)
		sz_min_cache = _cache_size;
	else
		sz_min_cache = cache_size;
		
	if (_cache_cities)
	{
		memcpy(temp_cache, _cache_cities, sizeof(city_info_t) * sz_min_cache);
		free(_cache_cities);
	}
	_cache_cities = temp_cache;

	return 0;
}


// return -1 --> failed...
// return  0 --> 
// return  1 -->
// return  2 -->
int push_city_to_cache(city_info_t* city){
	int ret = 0;
	int idx = 0;
	city_info_t* ptgt_city = NULL;

	if (city)
	{
		idx = city->cache_location;
		ptgt_city = (city_info_t*)&_cache_cities[idx];
		if (ptgt_city)
		{
			if (ptgt_city->cache_location != city->cache_location)
			{
				memcpy(&_cache_cities[idx], city, sizeof(city_info_t));
				return 1;
			}
			else
			{
				if (memcmp(&_cache_cities[idx], city, sizeof(city_info_t)) == 0)
				{
					fprintf(stderr, "The data was same...\n");
					return 0;
					
				}
				else
				{
					memcpy(&_cache_cities[idx], city, sizeof(city_info_t));
				}
			}
		}
	}
	else
	{
		fprintf(stderr, "The argument was NULL...\n");
		return -1;
	}

	return 0;
}


int push_city()
{
	FILE* fp_citydb = NULL;
	int len_city = 0;
	char buf[8192] = {0,};
	/* char city_name[20] = {0,}; */
	long modulo = 0;
	int i = 0;
	int sum = 0;

	printf("please input the name of city : ");
	fgets(_input, sizeof(_input), stdin);

	len_city = strlen(_input);
	if (len_city < 1 && len_city > 20)
	{
		fprintf(stderr, "cache size should be between 0 and 20.\n");
		return -1;
	}

	len_city = strlen(_input);
	_input[--len_city] = '\0';

	for (i=0; i<len_city; i++)
	{
		sum += _input[i];
	}
	modulo = sum % _cache_size;
	
	fp_citydb = fopen(CITY_DB_PATH, "a+");
	
	if (fp_citydb == NULL)
	{
		fprintf(stderr, "Opening DB file was failed...\n");
		return -1;
	}

	snprintf(buf, sizeof(buf), "%s %ld\n", _input, modulo);
	fputs(buf, fp_citydb);

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
	
	if (fp_citydb)
	{
		fclose(fp_citydb);
	}

	return 0;
}


int set_cache_size()
{
	long cache_size_temp = 0;
	char* ptr_failed = NULL;
	
	printf("please input cache size : ");
	fgets(_input, sizeof(_input), stdin);
	cache_size_temp = strtol(_input, &ptr_failed, 10);
	
	if (cache_size_temp == 0)
	{
		fprintf(stderr, "strtol() was failed...\n");
		return -1;
	}

	if (cache_size_temp < 0 || cache_size_temp > 30)
	{
		fprintf(stderr, "cache size should be between 0 and 30.\n");
		return -1;
	}

	_cache_size = cache_size_temp;
	fprintf(stderr, "changing cache size was complete successfully!!!\n");

	return 0;
}


int load_cities_to_cache()
{
	int ret = 0;
	FILE* fp_cities_db = NULL;
	char read_line[100] = {0,};
	city_info_t city;
	char* format = "%s %d\n";
	
	fp_cities_db = fopen(CITY_DB_PATH, "r");
	if (!fp_cities_db)
	{
		fprintf(stderr, "Opening file was failed...\n");
		return -1;
	}

	while(fgets(read_line, sizeof(read_line), fp_cities_db))
	{
		/* printf("readline : %s\n", read_line); */
		if (sscanf(read_line, format, city.name, &(city.cache_location)) == 2)
		{
			push_city_to_cache(&city);
		}
		else
		{
			fprintf(stderr, "parsing failed..\n");
			return -1;
		}
	}

	if (fp_cities_db)
		fclose(fp_cities_db);

	return 0;
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

	init_cache(_cache_size);

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
			if (set_cache_size() == 0)
			{
				init_cache(_cache_size);
			}
			break;

		case 4:
			load_cities_to_cache();
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
