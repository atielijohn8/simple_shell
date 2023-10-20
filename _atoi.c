#include "shell.h"

/**
 * process_Interactive_Mode - returns true if
 *   process_Interactive_Mode mode
 * @info:  at struct address
 *
 * Return: (1 ) process_Interactive_Mode mode (0)otherwise
 */
int process_Interactive_Mode(ShellInformation *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_Delimiter - checks if character is a delim
 * @c: char check
 * @delim: this a string to the
 *         delimiter
 * Return: (1)true (0) otherwise
 */
int is_Delimiter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - for checking  alphabetic character
 *@c:  character to the input
 *Return: 1 if alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - string converstion to interger
 *@s: string to be converted
 *Return: 0 if no number
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

