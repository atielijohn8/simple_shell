#include "shell.h"

/**
 *_inputStrPrint - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _inputStrPrint(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_writechar(str[i]);
		i++;
	}
}

/**
 * _writechar - writes the chararguement_countter c to stderr
 * @c: The chararguement_countter to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and error_number is set appropriately.
 */
int _writechar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUFFERFLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUFFERFLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfile_descriptor - writes the chararguement_countter c to given file_descriptor
 * @c: The chararguement_countter to print
 * @file_descriptor: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and error_number is set appropriately.
 */
int _putfile_descriptor(char c, int file_descriptor)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUFFERFLUSH || i >= WRITE_BUF_SIZE)
	{
		write(file_descriptor, buf, i);
		i = 0;
	}
	if (c != BUFFERFLUSH)
		buf[i++] = c;
	return (1);
}

/**
 *_ printStr_fd- prints an input string
 * @str: the string to be printed
 * @file_descriptor: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _printStr_fd(char *str, int file_descriptor)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _putfile_descriptor(*str++, file_descriptor);
	}
	return (i);
}
