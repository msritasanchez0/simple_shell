#include "shell.h"

/**
 * is_chain -  checks whether the current character in the
 *	given buffer is a delimiter for a chain
 *
 * @info: a struct containing the required parameters for the function.
 * @buf: a character buffer to search for the delimiter.
 * @p: a pointer to the current position in the buffer.
 *
 * Return: 1if the current character is a delimiter for a chain, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain -  verifies whether we should continue linking
 *	based on the previous status
 *
 * @info: a struct containing the parameters.
 * @buf: a character buffer.
 * @p: a pointer to the current position in the buffer.
 * @i: the starting position in the buffer.
 * @len: the length of the buffer.
 *
 * Returns: Nothing.
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - substitutes an alias in the tokenized string
 *	with its corresponding value
 *
 *  @info: a struct containing necessary parameters for alias substitution
 *
 * Return:an integer value of 1 if alias is replaced successfully, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - substitutes variables in the tokenized string
 *	with their corresponding values
 *
 * @info:  the parameter struct that contains information about the
 *	variables and their values.
 *
 * Return: 1 if the variables are successfully replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string -substitutes a string with a new one.
 *
 * @old: a pointer to the old string that needs to be replaced
 * @new: a pointer to the new string that will replace the old one
 *
 * Return: 1 if the replacement was successful, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
