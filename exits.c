#include "shell.h"

/**
 **copy_N_Characters - copies string
 *@dest: the destination string to be copied too
 *@src: tsource string
 *@n: the amount of characters to be copied
 *Return: concatenated string
 */
char *copy_N_Characters(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **concatenate_N_Characters - concatenates 2 strings
 *@dest: the 1 string
 *@src: the 2cstring
 *@n: the amount of bytes to be used maximally used
 *Return:  concatenated string
 */
char *concatenate_N_Characters(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **findFirst_Occurrence - locates string
 *@s: the string to be parsed to
 *@c: the character to look for 
 *Return: pointer to memory
 */
char *findFirst_Occurrence(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

