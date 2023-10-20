#include "shell.h"

/**
 * access_History - show hist list
 *              with line numbers, starting at 0.
 * @info: Structure containing possible arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int access_History(ShellInformation *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to be  string
 * @info:  struct
 * @str: string alias
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(ShellInformation *info, char *str)
{
	char *p, c;
	int ret;

	p = findFirst_Occurrence(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = deleteNodeAtIndex(&(info->alias),
		getNodeIndex(info->alias, findNodeStartsWith(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to be string
 * @info: p struct
 * @str: the string alias
 *
 * Return:  0 on success, 1 on error
 */
int set_alias(ShellInformation *info, char *str)
{
	char *p;

	p = findFirst_Occurrence(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints  alias string
 * @node: the alias node
 *
 * Return:  0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = findFirst_Occurrence(node->str, '=');
		for (a = node->str; a <= p; a++)
			put_Character(*a);
		put_Character('\'');
		print_String(p + 1);
		print_String("'\n");
		return (0);
	}
	return (1);
}

/**
 * aliasCommand - immmitates the alias builtin (man alias)
 * @info: Structure containing possible arguments. Used to maintain
 *          constant function prototype.
 *  Return: (0)
 */
int aliasCommand(ShellInformation *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = findFirst_Occurrence(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(findNodeStartsWith(info->alias, info->argv[i], '='));
	}

	return (0);
}
