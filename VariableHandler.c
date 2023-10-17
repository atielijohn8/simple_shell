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
	char *environ_value;

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
				environ_value = getenv("?");/*retrives the value of environment specified by the string ?*/
				free(av[i]);

				if (environ_value != NULL)
				{
					av[i] = strdup(environ_value);
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
