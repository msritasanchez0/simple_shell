#include "shell.h"

/**
 * bfree - The function deallocate releases the memory
 *	associated with a pointer and sets its address to NULL.
 * 
 * @ptr: a pointer to the memory to be deallocated.
 *
 * Return: 1 if the memory was successfully deallocated; otherwise, 0
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
