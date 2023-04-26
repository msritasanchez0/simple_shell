#include "shell.h"

/**
 * display_history - displays the command history list, one command per line,
 *                   preceded by line numbers starting at 0.
 * @info: pointer to the info_t struct containing the history list
 * Return: Always 0
 */
int display_history(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - removes an alias from the list of aliases
 * @info: pointer to the info_t struct containing the alias list
 * @str: string representation of the alias to be removed
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = '\0';
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - adds or modifies an alias in the list of aliases
 * @info: pointer to the info_t struct containing the alias list
 * @str: string representation of the alias to be added or modified
 * Return: 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints the value of an alias
 * @node: pointer to the alias node to be printed
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p, *a;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_command - mimics the functionality of the alias builtin (man alias)
 * @info: pointer to the info_t struct containing the alias list
 * Return: Always 0
 */
int alias_command(info_t *info)
{
	int i;
	char *p;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}

