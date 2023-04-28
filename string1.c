#include "shell.h"

/**
 * _strlen -  calculates the number of characters in a given string.
 *
 * @s: a pointer to the string whose length is to be calculated.
 *
 * Return: an integer representing the length of the string.
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - compares two strings in lexicographic order.
 *
 * @s1: the first string to be compared.
 * @s2:  the second string to be compared.
 *
 * Return: a negative integer if s1 is lexicographically less than s2,
 *	a positive integer if s1 is lexicographically greater than s2,
 *	and zero if the strings are equal.
 */
int _strcmp(char *s1, char *s2)
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
 * starts_with - determines whether the string haystack begins
 *	with the substring needle.
 *
 * @haystack: the string to searched
 * @needle: the substring to find at the beginning of the haystack string
 *
 * Return: a pointer to the next character in haystack after the needle
 *	substring if it is found; otherwise, returns NULL.
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - appends one string to another.
 *
 * @dest: the destination buffer where the concatenated string will be stored
 * @src: the source buffer containing the string to be appended.
 *
 * Return: a pointer to the destination buffer containing concatenated string
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
