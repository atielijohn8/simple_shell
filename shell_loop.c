#include "shell.h"

/**
 *  customShellMain - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int  customShellMain(ShellInformation *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (process_Interactive_Mode(info))
			print_String("$ ");
		printCharacter(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = findBuiltinCommand(info);
			if (builtin_ret == -1)
				 findExecutableCommand(info);
		}
		else if (process_Interactive_Mode(info))
			put_Character('\n');
		freeShellInfo(info, 0);
	}
	write_history(info);
	freeShellInfo(info, 1);
	if (!process_Interactive_Mode(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * findBuiltinCommand - finds  builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1  builtin not found,
 *			0  builtin executed successfully,
 *			1  builtin found but not successful,
 *			-2  builtin signals exit()
 */
int findBuiltinCommand(ShellInformation *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_Custom_Shell},
		{"env", manageEnvironment},
		{"help", displayHelp},
		{"history", access_History},
		{"setenv", setEnvironmentVariable},
		{"unsetenv", unsetEnvironmentVariable},
		{"cd", changeDirectory},
		{"alias", aliasCommand},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (string_compare(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 *  findExecutableCommand - finds a comd in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void  findExecutableCommand(ShellInformation *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_Delimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = findExecutablePath(info, getEnvironmentVariable(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		executeCommand(info);
	}
	else
	{
		if ((process_Interactive_Mode(info) || getEnvironmentVariable(info, "PATH=")
			|| info->argv[0][0] == '/') && isBuiltinCommand(info, info->argv[0]))
			executeCommand(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * executeCommand - forks a an exec thread to run command
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void executeCommand(ShellInformation *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			freeShellInfo(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
