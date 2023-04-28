#include "shell.h"

/**
 * list_len - The function list_len computes the
 *	size of a linked list
 *
 * @h: a pointer to the first node of the linked list.
 *
 * Return: the length of linked list
 */
size_t list_len(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - The function list_to_strings generates an
 *	array of strings from the list->str data.
 *
 * @head: a pointer to first node in the linked list.
 *
 * Return: An array of strings containing the list->str data.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - The function display_list outputs all the
 *	elements stored in a linked list of type list_t.
 *
 * @h: a pointer to first node in the linked list
 *
 * Return: number of nodes in the linked list
 */
size_t print_list(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - function returns a pointer to the node in
 *	the linked list whose string begins with the specified
 *	prefix and matches the next character after the prefix.
 *
 * @c: the character that follows the prefix and should match
 *	with the node's string
 * @node: pointer to the linked list head
 * @prefix: string to match
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index -  retrieves the position of a node in the list.
 *
 * @head: a pointer to the head of the list
 * @node: a pointer to the node whose position is to be retrieved.
 *
 * Return: The index of the node in the list,
 *	or -1 if the node is not found
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
