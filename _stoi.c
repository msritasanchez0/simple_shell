#include "shell.h"

/**
 * interactive - function that checks whether shell is in interactive mode
 * @info: the pointer to the structure holding shell information
 * Return: 1 if interactive, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - function that check whether char is a delimiter
 * @delim: delimiter string
 * @b:the character to check to check for
 * Return: 1 if true, 0 otherwise
 */
int is_delim(char b, char *delim)
{
	while (*delim != '\0')
	{
		if (*delim == b)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * _isalpha - function that checks whether character is alphabetic
 * @b:parameter char to check
 * Return: 1 if alphabetic, 0 otherwise
 */
int _isalpha(int b)
{
	return ((b >= 'a' && b <= 'z') || (b >= 'A' && b <= 'Z'));
}

/**
 * _atoi - function that converts a string to an integer
 * @s:parameter string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */
int _atoi(char *s)
{
	int m, sign = 1, flag = 0, output = 0;

	unsigned int result = 0;

	for (m = 0; s[m] != '\0' && flag != 2; m++)
	{
		if (s[m] == '-')
			sign *= -1;

		if (s[m] >= '0' && s[m] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[m] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
