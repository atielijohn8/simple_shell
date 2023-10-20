#include "shell.h"

/**
 * clear_info - initializes ShellInformation
 * @info: struct address
 */
void clear_info(ShellInformation *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes ShellInformation struct
 * @info: struct address
 * @av: argument av
 */
void set_info(ShellInformation *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = tokenizeString(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = duplicate_String(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replaceAlias(info);
		replace_vars(info);
	}
}

/**
 * freeShellInfo - frees ShellInformation struct
 * @info: struct address
 * @all: true if freeing  fields
 */
void freeShellInfo(ShellInformation *info, int all)
{
	freeMemory(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeLinkedList(&(info->env));
		if (info->history)
			freeLinkedList(&(info->history));
		if (info->alias)
			freeLinkedList(&(info->alias));
		freeMemory(info->environ);
			info->environ = NULL;
		freeBlock((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		put_Character(BUF_FLUSH);
	}
}

