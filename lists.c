#include "shell.h"

/**
 * add_node - function that adds a node at the beginning of the list
 * @hd: address to the pointer of the head node
 * @str: string area of node
 * @num: node index used by history
 *
 * Return: list size
 */
list_t *add_node(list_t **hd, const char *str, int num)
{
	list_t *new_hd;

	if (!hd)
		return (NULL);

	new_hd = malloc(sizeof(list_t));
	if (!new_hd)
		return (NULL);

	_memset((void *)new_hd, 0, sizeof(list_t));
	new_hd->num = num;

	if (str)
	{
		new_hd->str = _strdup(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}

	new_hd->next = *hd;
	*hd = new_hd;

	return (new_hd);
}

/**
 * add_node_end - function that adds a node to the end of the list
 * @hd: the memory address of pointer to head node
 * @str: string area of node
 * @num: node index used by history
 *
 * Return: list size
 */
list_t *add_node_end(list_t **hd, const char *str, int num)
{
	list_t *new_node, *node;

	if (!hd)
		return (NULL);

	node = *hd;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
			}
		}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*hd = new_node;

	return (new_node);
}

/**
 * print_list_str - function that prints only
 * the string element of a linked list
 * @g: the pointer to the first node
 *
 * Return: list size
 */
size_t print_list_str(const list_t *g)
{
	size_t j = 0;

	while (g)
	{
		_puts(g->str ? g->str : "(nil)");
		_puts("\n");
		g = g->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_at_index - function that deletes node for index
 * @hd: the address to pointer of first node
 * @index: the index of the node to be deleted
 *
 * Return: 1 on success, 0 otherwise
 */
int delete_node_at_index(list_t **hd, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int n = 0;

	if (!hd || !*hd)
		return (0);

	if (!index)
	{
		node = *hd;
		*hd = (*hd)->next;
		free(node->str);
		free(node);
		return (1);
	}

	node = *hd;
	while (node)
	{
		if (n == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		n++;
		prev_node = node;
		node = node->next;
	}

	return (0);
}

/**
 * free_list - function that frees all nodes of a list
 * @hd_ptr: the address to pointer of head node

Return: void
*/
void free_list(list_t **hd_ptr)
{
list_t *node, *next_node, *hd;

if (!hd_ptr || !*hd_ptr)
return;
hd = *hd_ptr;
node = hd;
while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}
*hd_ptr = NULL;
}
