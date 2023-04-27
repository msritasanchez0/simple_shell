#include "shell.h"

/**
 * _count_words - counts number of words in a string
 * @str: the input string
 * @delim: the delimiter character
 *
 * Return: number of words
 */
static int _count_words(char *str, char delim)
{
	int count = 0, i;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] != delim && (i == 0 || str[i - 1] == delim))
			count++;
	}

	return count;
}

/**
 * _strtok - tokenizes a string
 * @str: the input string
 * @delim: the delimiter character
 *
 * Return: pointer to the next token in the string
 */
static char *_strtok(char *str, char delim)
{
	static char *token;
	char *next_token;

	if (str != NULL)
		token = str;

	if (token == NULL)
		return (NULL);

	next_token = token;
	while (*next_token != '\0' && *next_token != delim)
		next_token++;

	if (*next_token == '\0')
		token = NULL;
	else
	{
		*next_token = '\0';
		token = next_token + 1;
	}

	return (token);
}

/**
 * _strtow - splits a string into words
 * @str: the input string
 * @delim: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **_strtow(char *str, char *delim)
{
	int i, num_words = 0;
	char **tokens, *token;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	num_words = _count_words(str, *delim);
	if (num_words == 0)
		return (NULL);

	tokens = malloc(sizeof(char *) * (num_words + 1));
	if (tokens == NULL)
		return (NULL);

	token = _strtok(str, *delim);
	i = 0;
	while (token != NULL)
	{
		tokens[i] = _strdup(token);
		if (tokens[i] == NULL)
		{
			for (i = 0; i < num_words; i++)
				free(tokens[i]);
			free(tokens);
			return (NULL);
		}

		token = _strtok(NULL, *delim);
		i++;
	}
	tokens[i] = NULL;

	return (tokens);
}
