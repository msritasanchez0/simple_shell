#include "shell.h"

/**
 **_memset - populates memory with a constant byte value.
 *
 * @s: a pointer to the memory area to be filled.
 * @b: the byte value to be used to fill the memory area pointed to by s
 * @n: the number of bytes to be filled with the byte value b
 *
 * Return: a pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree - deallocates a dynamic array of strings.
 * @pp: a pointer to a dynamic array of strings that need to be deallocated
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - modifies the size of a previously allocated memory block
 * 
 * @ptr: a pointer to the previously allocated block.
 * @old_size: the size of the previously allocated block in bytes.
 * @new_size: the desired size of the new memory block in bytes.
 *
 * Return: a pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
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
