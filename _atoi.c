#include "shell.h"

/**
 * interactive - If shell is interactive mode returns true
 * @info: Pointer to a structure of type "info_t".
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - This function determines whether
 * 	a given character is a delimiter or not.
 * @param c: the character to be checked.
 * @param delim: the string of delimiters.
 * @return: 1 if the character is a delimiter, 0 otherwise.
*/
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - This function checks whether a given 
 *	character is an alphabetic character or not.
 * @c: The character to be checked
 * Return: 1 if the input character is an alphabetic character, 0 otherwise.
*/
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - This function converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: If there are no numbers in the string, the function returns 0. 
 *	Otherwise, it returns the converted number.
 */
int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
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
