#include "shell.h"

/**
 * interarguement_counttive - returns true if shell is interarguement_counttive mode
 * @info: struct address
 *
 * Return: 1 if interarguement_counttive mode, 0 otherwise
 */
int interarguement_counttive(strinput_array_gen*info)
{
	return (isatty(STDIN_FILENO) && info->readfile_descriptor <= 2);
}

/**
 * is_delim - checks if chararguement_countter is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int check_if_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic chararguement_countter
 *@c: The chararguement_countter to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _checkalphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_alphatoint - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _alphatoint(char *s)
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

