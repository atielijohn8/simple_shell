#include "shell.h"

/**
 * string_Length - Calculates the length of a string.
 * @s: mesure of the string to be
 * examined
 *
 * Return: integer length of string
 */
int string_Length(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * string_compare - performs lexicogarphic comparison of betwee 
 * two strangs.
 * @s1: first strang
 * @s2: second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int string_compare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_With - Checks if a string starts with a specific substring.
 * @haystack: The string to search.
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *starts_With(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * concatenate_Strings - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination of buffer
 */
char *concatenate_Strings(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
