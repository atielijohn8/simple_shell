#include "shell.h"

/**
 * variableHandler - subsitute varibes with their values
 * @av: array of varibes  command
 * Description: fill the varibales with actual commands
 * Return:void 
 */

void variableHandler(char **av)
{
	int i;
	char process_string[10];
	char *envValue;

	for (i = 0; av[i] != NULL; i++)
	{
		if (av[i][0] == '$')
		{
			if (strcmp(av[i], "$$") == 0)
			{
				sprintf(process_string, "%d", getpid());/*converts pid into string and stores it in process_string */
				free(av[i]);
				av[i] = strdup(process_string);/*duplicates the contents of process_string to av[i]*/
			}
			else if (strcmp(av[i], "$?") == 0)
			{
				envValue = getenv("?");/*retrives the value of environment specified by the string ?*/
				free(av[i]);

				if (envValue != NULL)
				{
					av[i] = strdup(envValue);
				}
				else
				{
					av[i] = strdup("");
				}
			}
			else
			{

			}
		}
	}
}
