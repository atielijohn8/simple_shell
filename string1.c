#include "shell.h"

/**
 * copy_String - string copy
 * @dest:  destination
 * @src: source string
 *
 * Return: pointer to destination
 * of the string
 */
char *copy_String(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * duplicate_String - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer of the duplicated string
 */
char *duplicate_String(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *print_String - prints input string
 *@str: string to be printed
 *
 * Return: Nothing
 */
void print_String(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		put_Character(str[i]);
		i++;
	}
}

/**
 * put_Character - writes the char to stdout
 * @c:  character to print
 *
 * Return: success (1).
 * On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int put_Character(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}
