#include "shell.h"

/**
 * listLength - determines length  l list
 * @h: pointer to the first node
 *
 * Return: size of list
 */
size_t listLength(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list
 * @head: pointer to first node
 *
 * Return: array contain strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = listLength(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(string_Length(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = copy_String(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of a list_t l list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		print_String(convert_number(h->num, 10, 0));
		put_Character(':');
		put_Character(' ');
		print_String(h->str ? h->str : "(nil)");
		print_String("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * findNodeStartsWith - returns node whose string starts with prefix
 * @node: pointer 
 * @prefix: string to match
 * @c: the next character after prefix to be matched
 * Return: match node or null
 */
list_t *findNodeStartsWith(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_With(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getNodeIndex - gets the index of a node
 * @head: pointer to list head
 * @node: pointer node
 *
 * Return: index of node or (-1)
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
