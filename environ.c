#include "shell.h"

/**
 * manageEnvironment - print current environment
 * @info: Structure containing possible arguments. Used to maintain
 *          const function prototypes.
 * Return: Always 0
 */
int manageEnvironment(ShellInformation *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * getEnvironmentVariable - shows  the value of an environ variable
 * @info: Structure containing posssible arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *getEnvironmentVariable(ShellInformation *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_With(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnvironmentVariable - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing possible arguments. that maintain
 *        const function prototypes.
 *
 *  Return:  0
 */
int setEnvironmentVariable(ShellInformation *info)
{
	if (info->argc != 3)
	{
		printError_Message("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnvironmentVariable - Remove environment variable
 * @info: Structure containing possible arguments. Used to maintain
 *        cons function prototype.
 *
 *  Return: Always 0
 */
int unsetEnvironmentVariable(ShellInformation *info)
{
	int i;

	if (info->argc == 1)
	{
		printError_Message(" few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_EnvironmentList - populates environ l list
 * @info: Structure containing possible arguments. Used to maintain
 *          const function prototypes.
 * Return:  0
 */
int populate_EnvironmentList(ShellInformation *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

