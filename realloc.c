#include "shell.h"

/**
 *make_memset - check mem
 *@s: the pointer, memory area
 *@b:  byte to fill *s with
 *@n: amount of bytes to be filled
 *
 *Return: s a pointer to the memory area s
 */
char *make_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * freeMemory - frees a string ,strings
 * @pp: Pointer to the array of strings.
 */
void freeMemory(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * resize_Memory - Adjusts the size of a previously allocated block of memory.
 * @ptr:  Pointer to the previously allocated block.
 * @old_size: byte size of previous block
 * @new_size: byte size ,of new block
 *
 * Return: Pointer to the original block. If reallocation fails, returns NULL.
 */
void *resize_Memory(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
