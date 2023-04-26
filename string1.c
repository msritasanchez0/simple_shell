

#include "shell.h"

/**
 * _strcpy - function that copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdup - function that duplicates a string
 * @str: the string we are duplicating
 * Return: pointer to string duplicated
 */
char *_strdup(const char *str)
{
	int l = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		l++;
	ret = malloc(sizeof(char) * (l + 1));
	if (!ret)
		return (NULL);
	for (l++; l--;)
		ret[l] = *--str;
	return (ret);
}

/**
 * _puts - function that prints string input
 * @str: the string to be printed
 * Return: Nothing
 */
void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
 * _putchar - function that writes char to stdout
 * @h: the char to print
 * Return:1 On success
 * -1 is returned on error
 */
int _putchar(char h)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (h == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(1, buf, a);
		a = 0;
	}
	if (h != BUF_FLUSH)
		buf[a++] = h;
	return (1);
}
