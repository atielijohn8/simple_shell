#include "shell.h"

/**
 * get_Path - Retrieves the full path of a command
 * @command: the command of whose path is sought
 * Description: Find the path os a given command
 * This function attempts to locate  full path of a given command by searching
 * through the directories listed in the PATH environment variable If successful
 * it returns a string containing the full path If the command is not found it will return
 *
 * Return:string representing the full path of the command if found
 */

char *get_Path(char *command)
{
	char *command_path;/*ptr to character array(char*) storing environment variable*/
	char *path_duplicate;/*another ptr to character array used to create duplicate variable of command_path*/
	char *path_token;/*use as a token in parsing the PATH.*/
	char *file_path;/*This is a pointer to a character array (char*) which will be used to construct the complete path to the command.*/
	int cmd_lenght;/*integer used to store the length of the command*/
	int dir_lenght;/*integer used to store the length of the directories in PATH.*/
	struct stat buffer;/*structure used for file information*/

	command_path = getenv("PATH");/*retrieves the value of the PATH environment variable and stores it in command_path*/

	/*checks if command path exists*/
	if (command_path)
	{
		path_duplicate = strdup(command_path);/*creates duplicate of command_path*/
		cmd_lenght = strlen(command);/*calculate command length*/
		path_token = strtok(path_duplicate, ":");/*splits path variable by colons. it retrives 1st dir in path_duplicate*/

		/*loop that iterates over each directory in  path*/
		while (path_token != NULL)
		{
			/*calculates the length of the current directory.*/
			dir_lenght = strlen(path_token);
			/*dynamically allocates memory for file_path to store full path 2 accounts slashes between the directory*/
			file_path = malloc(cmd_lenght + dir_lenght + 2);
			/*copies current directory to file_path*/
			strcpy(file_path, path_token);
			/*This appends the command name to the directory with appropriate separators*/
			strcat(file_path, "/");
			strcat(file_path, command);
			strcat(file_path, "\0");

			/*This checks if the file exists using stat()*/
			if (stat(file_path, &buffer) == 0)
			{
				free(path_duplicate);
				return (file_path);
			}
			else
			{
				free(file_path);
				path_token = strtok(NULL, ":");
			}
		}

		free(path_duplicate);

		/*checks if the command is an absolute path (i.e., it starts with /)*/
		if (stat(command, &buffer) == 0)
		{
			return (strdup(command));
		}

		return (NULL);
	}

	return (NULL);
}

