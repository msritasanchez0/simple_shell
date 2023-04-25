#include "shell.h"

/**
 * _memoset - function that fills memory with a constant byte
 * @p: pointer to the memory area
 * @y: byte to fill memory area with
 * @n: amount of bytes to be filled
 *
 * Return: p
 */
char *_memoset(char *p, char y, unsigned int n)
{
	unsigned int k;

	for (k = 0; k < n; k++)
		p[k] = y;
	return (p);
}

/**
 * ffrees - function that frees string of strings
 * @ss: string of strings to be freed
 *
 * Return: void
 */
void ffrees(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * _reallocate - function that reallocates a memory block
 * @ptr: pointer to previous block that was malloced
 * @old_size: size in bytes of the previous block
 * @new_size: size in bytes of the new block
 *
 * Return: pointer to old block
 */
void *_reallocate(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *t;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	t = malloc(new_size);
	if (!t)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		t[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (t);
}
