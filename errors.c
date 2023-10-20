#include "shell.h"

/**
 *printError_Message - prints the input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void printError_Message(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		printCharacter(str[i]);
		i++;
	}
}

/**
 * printCharacter - writes the character c to stder
 *                   output
 * @c: The character to print
 *
 * Return: success 1.
 * On error, -1 
 */
int printCharacter(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *  putCharacter_To_File - writes the character c to given file descripter
 * @c: The char to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned
 */
int  putCharacter_To_File(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * putStringTo_File - prints input string
 * @str: the string to be printed
 * @fd:  filedescriptor 
 *
 * Return: the number of chars puts
 */
int  putStringTo_File(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i +=  putCharacter_To_File(*str++, fd);
	}
	return (i);
}

