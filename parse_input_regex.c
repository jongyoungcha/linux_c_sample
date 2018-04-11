#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	char inputted[20] = {0};
	char msgbuf[100];
	regex_t regex;
	int ret = 0;
	
	char* comp_rule = "^[1-9][SDT][\\#\\*]*[1-9][SDT][\\#\\*]*[1-9][SDT][\\#\\*]*\n";
	/* char* comp_rule = "^([1-9][SDT][\\*\\#]*]){3}"; */
	
	fgets(inputted, 20, stdin);
	printf("%s", inputted);
	
	ret = regcomp(&regex, comp_rule , 0);
	if (ret < 0)
	{
		fprintf(stderr, "regcomp() was failed...\n");
		return -1;
	}

	ret = regexec(&regex, inputted, 0, NULL, 0);
	if (!ret)
	{
		fprintf(stdout, "Match\n");
	}
	else if (ret == REG_NOMATCH)
	{
		fprintf(stderr, "No match\n");
	}
	else
	{
		regerror(ret, &regex, msgbuf, sizeof(msgbuf));
		fprintf(stderr, "Regex match failed:%s\n", msgbuf);
		exit(1);
	}
	
	
	return 0;
}
