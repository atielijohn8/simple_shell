#include "shell.h"

/**
 * get_environ - return string of array to env
 * @info: Structure containing possible argument
 *          constant function prototype.
 *
 * Return: Always 0
 */
char **get_environ(ShellInformation *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - delete an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        cons function prototype.
 *  Return: 1delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(ShellInformation *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_With(node->str, var);
		if (p && *p == '=')
		{
			info->env_changed = deleteNodeAtIndex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 *  _setenv- Initialize  new environment var
 *             or modify an existing one
 * @info: Structure containing  arguments.
 *        constant function prototype.
 * @var:  string env var property
 * @value:  string env var value
 *  Return: Always 0
 */
int _setenv(ShellInformation *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(string_Length(var) + string_Length(value) + 2);
	if (!buf)
		return (1);
	copy_String(buf, var);
	concatenate_Strings(buf, "=");
	concatenate_Strings(buf, value);
	node = info->env;
	while (node)
	{
		p = starts_With(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

