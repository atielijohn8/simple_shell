#include "shell.h"

/**
 * main - program entry point
 * @ac: arguement count
 * @av: arguement vector of commands
 * Description: this is the core logic of the program
 * Return: status or exit code
 */

int main(int ac, char **av)
{
	char *prompt_text = "kennedy_shell:$ ";
	char *cmd_Litera = NULL;
	char *cmdLiteralDuplicate = NULL;
	size_t numOfChars = 0;/*interger storing number of tokens in the input*/
	ssize_t char_Read;
	const char *delimiter = " \n";
	int numOfTokens = 0;
	char *token;
	int i;
	int interactive;

	/*this line ignores ac*/
	(void)ac;

	/*checks if the program is running interactive mode by using isatty function*/
	interactive = isatty(STDIN_FILENO);

	/*creating infinite loop(input and process)*/
	while (1)
	{
		if (interactive)
		{
			printf("%s", prompt_text);
		}
		/*reading user input using stdin*/
		char_Read = getline(&cmd_Litera, &numOfChars, stdin);

		/*error handling*/
		if (char_Read == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				return (0);
			}

			perror("getline");

			return (-1);
		}

		cmdLiteralDuplicate = malloc(sizeof(char) * (char_Read + 1));

		if (cmdLiteralDuplicate == NULL)
		{
			perror("malloc");
			return (-1);
		}

		strcpy(cmdLiteralDuplicate, cmd_Litera);
		token = strtok(cmd_Litera, delimiter);

		while (token != NULL)
		{
			numOfTokens++;
			token = strtok(NULL, delimiter);
		}

		numOfTokens++;
		av = malloc(sizeof(char *) * numOfTokens);
		token = strtok(cmdLiteralDuplicate, delimiter);

		for (i = 0; token != NULL; i++)
		{
			av[i] = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(av[i], token);
			token = strtok(NULL, delimiter);
		}
		av[i] = NULL;
		runCommand(av);

		for (i = 0; i < numOfTokens - 1; i++)
		{
			free(av[i]);
		}

		free(av);
		free(cmdLiteralDuplicate);
		free(cmd_Litera);
		cmd_Litera = NULL;
		numOfTokens = 0;

		if (!interactive)
		{
			return (0);
		}
	}
	return (0);
}
