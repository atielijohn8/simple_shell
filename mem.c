#include "shell.h"

/**
 * freeBlock - frees a pointer / NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 freed, otherwise 0.
 */
int freeBlock(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
