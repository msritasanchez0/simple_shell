#include "shell.h"

/**
 * check_interactive - checks if shell is running in interactive mode
 * @info: a pointer to a struct containing shell information
 *
 * Return: 1 if shell is interactive, 0 otherwise
 */
int check_interactive(info_t *info)
{
	if (isatty(STDIN_FILENO) && info->readfd <= 2)
		return (1);
	else
		return (0);
}

/**
 * is_delimiter - checks if a character is a delimiter
 * @c: the character to check
 * @delim: a string of delimiters
 *
 * Return: 1 if c is a delimiter, 0 otherwise
 */
int is_delimiter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _isalpha - checks if a character is alphabetic
 * @c: the character to check
 *
 * Return: 1 if c is an alphabetic character, 0 otherwise
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to convert
 *
 * Return: the integer value of s, or 0 if no integer is found
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output = 0;

	for (i = 0; s[i]; i++)
	{
		if (s[i] == '-')
			sign *= -1;
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			output = output * 10 + (s[i] - '0');
		}
		else if (flag == 1)
			break;
	}

	return (output * sign);
}
