#include "shell.h"

/**
 * clear_info - initializes strinput_array_genstruct
 * @info: struct address
 */
void erase_info(strinput_array_gen*info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes strinput_array_genstruct
 * @info: struct address
 * @arguement_vector: argument vector
 */
void def_info(strinput_array_gen*info, char **arguement_vector)
{
	int i = 0;

	info->fname = arguement_vector[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		switch_alias(info);
		switch_vars(info);
	}
}

/**
 * free_info - frees strinput_array_genstruct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void mem_free_info(strinput_array_gen*info, int all)
{
free_fd(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			list_free_memory(&(info->env));
		if (info->history)
			list_free_memory(&(info->history));
		if (info->alias)
			list_free_memory(&(info->alias));
	free_fd(info->environ);
			info->environ = NULL;
		ptr_free((void **)info->cmd_buf);
		if (info->readfile_descriptor > 2)
			close(info->readfile_descriptor);
		_putchar(BUFFERFLUSH);
	}
}
