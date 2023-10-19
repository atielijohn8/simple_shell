#include "shell.h"

/**
 *  main_shell_loop- main shell loop
 * @info: the parameter & return info struct
 * @arguement_vector: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int main_shell_loop(strinput_array_gen*info, char **arguement_vector)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		erase_info(info);
		if (interarguement_counttive(info))
			_puts("$ ");
		_writechar(BUFFERFLUSH);
		r = fetch_input(info);
		if (r != -1)
		{
			def_info(info, arguement_vector);
			builtin_ret = locate_buitin_func(info);
			if (builtin_ret == -1)
				locate_cmd_path(info);
		}
		else if (interarguement_counttive(info))
			_putchar('\n');
		mem_free_info(info, 0);
	}
	write_history(info);
	mem_free_info(info, 1);
	if (!interarguement_counttive(info) && info->status)
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
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int locate_buitin_func(strinput_array_gen*info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcomparision(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void locate_cmd_path(strinput_array_gen*info)
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
		if (!check_if_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info,  getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_exec_thread(info);
	}
	else
	{
		if ((interarguement_counttive(info) ||  getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && CheckIf_FileExec_cmd(info, info->argv[0]))
			fork_exec_thread(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			PrintError(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_exec_thread(strinput_array_gen*info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			mem_free_info(info, 1);
			if (error_number == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				PrintError(info, "Permission denied\n");
		}
	}
}
