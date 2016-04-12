#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main1() {
	char key_module[] = "settings";
	char key_module1[] = "module(settings)";
	char key_word[] = "}";
	char key_words[] = "show_warning_view";
	FILE *pf = fopen("C:\\Users\\franc\\Desktop\\system.txt","r");
	
	if (pf == NULL) {
		printf("open faile!");
	}else 
	{
		printf("open suceess!\n");
		while (!feof(pf)) 
		{
			char str[128] = { 0 };
			fgets(str, 128, pf);
			char *p = strstr(str, key_module);
			if (p != NULL)
			{
				printf("%s\n", str);
				
			}			
		}
	}
	
	fclose(pf);
	system("pause");
}

main2() {
	char s[] = "ab-cd : ef;gh :i-jkl;mnop;qrs-tu: vwx-y;z";
	char *delim = "-: ";
	char *p;
	printf("%s ", strtok(s, delim));
	while ((p = strtok(NULL, delim)))
		printf("%s ", p);

	printf("\n");
	system("pause");
}

/**
* Split a string into some strings according to a list of separators.
*
* @Param dest						out: storage the strings has be split.
* @Param count						out: the number of strings has be split successfully, 0 for failed to split.
* @Param s_str						in:  the strings for split.
* @Param separator					in:  the list of split separators.
* @Param number_separator			in:  the numbers of separators.
* @Param compress_separator		in:  will be create a empty string when two split adjacent
*										 if compress_separator > 0 and not for compress_separator == 0
* @Param keep_separator			in:  the separators will be put into parameter 'dest' if keep_separator > 0
*/
int strsplit(char ***dest, int *count, char *s_str, char **separator, int number_separators, int compress_separator, int keep_separator)
{
	int i = 0;
	char **result = NULL;
	char **temp_result = NULL;
	unsigned int curt_size = 0;
	unsigned int new_size = 0;
	char *look_ahead = NULL;
	char *most_front_separator_start = NULL;
	char *most_front_separator_end = NULL;
	char *separator_start = NULL;
	int find_a_separator = 0;
	int find_a_string = 0;

	*count = 0;
	*dest = NULL;

	/* check parameters */
	if (
		dest == NULL
		|| s_str == NULL || *s_str == '\0'
		|| separator == NULL
		|| number_separators <= 0
		|| compress_separator < 0
		|| keep_separator < 0
		)
		return -1;

	for (i = 0; i < number_separators; i++)
		if (separator[i] == NULL || *separator[i] == '\0')
			return -1;

	for (look_ahead = s_str; *look_ahead != '\0'; look_ahead = most_front_separator_end)
	{
		most_front_separator_start = look_ahead + strlen(look_ahead);
		most_front_separator_end = look_ahead + strlen(look_ahead);
		find_a_separator = 0;

		/* find the next separator. */
		for (i = 0; i < number_separators; i++)
		{
			separator_start = strstr(look_ahead, separator[i]);
			if (separator_start == NULL)
				continue;

			find_a_separator = 1;
			/* update the most front separator. */
			if (separator_start < most_front_separator_start)
			{
				most_front_separator_start = separator_start;
				most_front_separator_end = most_front_separator_start + strlen(separator[i]);
			}
		}

		find_a_string = (look_ahead == most_front_separator_start) ? 0 : 1;

		/* allow put the new string into result if need. */
		new_size = (find_a_string > 0) ? (curt_size + 1) : ((compress_separator > 0) ? curt_size : (curt_size + 1));
		/* allow put the separator into result if need. */
		new_size = (keep_separator > 0) ? (new_size + 1) : new_size;
		if (new_size == curt_size)
			continue;

		temp_result = (char **)malloc((new_size) * sizeof(char *));
		if (temp_result == NULL)
		{
			if (result != NULL)
			{
				for (i = 0; i < curt_size; i++)
					if (result[i] != NULL)
						free(result[i]);
				free(result);
				result = NULL;
			}

			return -2;
		}

		/* copy the pointers of string find early. */
		memset(temp_result, 0, new_size);
		for (i = 0; i < curt_size; i++)
			temp_result[i] = result[i];

		if (find_a_string == 0)
		{
			if (compress_separator == 0)
			{
				temp_result[curt_size] = (char *)malloc(sizeof(char));
				if (temp_result[curt_size] == NULL)
				{
					if (temp_result != NULL)
					{
						for (i = 0; i < curt_size; i++)
							if (temp_result[i] != NULL)
								free(temp_result[i]);
						free(temp_result);
						temp_result = NULL;
					}

					return -2;
				}
				memset(temp_result[curt_size], 0, 1);
			}
		}
		else
		{
			/* put the new string into result. */
			temp_result[curt_size] = (char *)malloc((most_front_separator_start - look_ahead + 1) * sizeof(char));
			if (temp_result[curt_size] == NULL)
			{
				if (temp_result != NULL)
				{
					for (i = 0; i < curt_size; i++)
						if (temp_result[i] != NULL)
							free(temp_result[i]);
					free(temp_result);
					temp_result = NULL;
				}

				return -2;
			}
			memset(temp_result[curt_size], 0, most_front_separator_start - look_ahead + 1);
			strncpy(temp_result[curt_size], look_ahead, most_front_separator_start - look_ahead);
			temp_result[curt_size][most_front_separator_start - look_ahead] = '\0';
		}

		if (keep_separator > 0)
		{
			/* put the separator into result. */
			temp_result[new_size - 1] = (char *)malloc(most_front_separator_end - most_front_separator_start + 1);
			if (temp_result[new_size - 1] == NULL)
			{
				if (temp_result != NULL)
				{
					for (i = 0; i < new_size - 1; i++)
						if (temp_result[i] != NULL)
							free(temp_result[i]);
					free(temp_result);
					temp_result = NULL;
				}

				return -2;
			}
			memset(temp_result[new_size - 1], 0, most_front_separator_end - most_front_separator_start + 1);
			strncpy(temp_result[new_size - 1], most_front_separator_start, most_front_separator_end - most_front_separator_start);
			temp_result[new_size - 1][most_front_separator_end - most_front_separator_start] = '\0';
		}

		/* update result. */
		free(result);
		result = temp_result;
		temp_result = NULL;
		curt_size = new_size;
	}

	*dest = result;
	*count = curt_size;

	return 0;
}

void main(int argc, char *argv[])
{
	char *separator[] = { "="};
	char *str = "fm_max=108000";
	char **result = NULL;
	int n_str = 0;
	int i = strsplit(&result, &n_str, str, separator, 1, 1, 1);
	printf("%s\n", result[2]);
	/*for (i = 0; i < n_str; i+=2)
		printf("%s\n", result[i]);

	for (i = 0; i < n_str; i++)
		free(result[i]);*/
	free(result);
	system("pause");
	//return 0;
}