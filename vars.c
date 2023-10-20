#include "shell.h"

/**
 * isCommandChaining - test if current char in buffer is a chain delimeter
 * @info:  struct
 * @buf:  buffer
 * @p: address of current position in the
 * buffer
 *
 * Return: 1 delimeter, 0 otherwise
 */
int isCommandChaining(ShellInformation *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') 
	{
		buf[j] = 0; 
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - continue chaining based on last status
 * @info:  struct
 * @buf:  buffer
 * @p: address of current position in buf
 * @i: buffer starting position
 * @len:buffer length
 *
 * Return: void
 */
void check_chain(ShellInformation *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replaceAlias - replacetes an aliases in the tokenized string
 * @info: struct
 *
 * Return: 1 replaced, 0 otherwise
 */
int replaceAlias(ShellInformation *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = findNodeStartsWith(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = findFirst_Occurrence(node->str, '=');
		if (!p)
			return (0);
		p = duplicate_String(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info:  struct
 *
 * Return: 1  replaced, 0 otherwise
 */
int replace_vars(ShellInformation *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!string_compare(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				duplicate_String(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!string_compare(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				duplicate_String(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = findNodeStartsWith(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				duplicate_String(findFirst_Occurrence(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], duplicate_String(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address to the  old string
 * @new: new string
 *
 * Return: 1 replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
