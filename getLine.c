
#include "shell.h"

/**
 * input_buf -function that buffers chained commands
 * @info: parameter structure
 * @buf:the address of buffer
 * @len: address of len variable
 * Return:thd bytes to read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t m = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		m = getline(buf, &len_p, stdin);
#else
		m = _getline(info, buf, &len_p);
#endif
		if (m > 0)
		{
			if ((*buf)[m - 1] == '\n')
			{
				(*buf)[m - 1] = '\0';
				m--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = m;
				info->cmd_buf = buf;
			}
		}
	}
	return (m);
}

/**
 * get_input - function that gets a line minus the newline
 * @info: parameter structurure
 * Return: the bytes read
 */
ssize_t get_input(info_t *info)
{
	static size_t a, b, len;
	char **buf_p = &(info->arg), *p;
	ssize_t m = 0;
	static char *buf;

	_putchar(BUF_FLUSH);
	m = input_buf(info, &buf, &len);
	if (m == -1)
		return (-1);
	if (len)
	{
		b = a;
		p = buf + a;

		check_chain(info, buf, &b, a, len);
		while (b < len)
		{
			if (is_chain(info, buf, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (m);
}

/**
 * read_buf -the function reads a buffer
 * @info:the parameter structure
 * @buf:the buffer
 * @a:the size
 * Return:m
 */
ssize_t read_buf(info_t *info, char *buf, size_t *a)
{
	ssize_t m  = 0;

	if (*a)
		return (0);
	m = read(info->readfd, buf, READ_BUF_SIZE);
	if (m >= 0)
		*a = m;
	return (m);
}

/**
 * _getline -function that gets the next line of input from STDIN
 * @info:the parameter structure
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static size_t a, len;
	static char buf[READ_BUF_SIZE];
	ssize_t m = 0, s = 0;
	size_t k;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (a == len)
		a = len = 0;

	a = read_buf(info, buf, &len);
	if (m == -1 || (m == 0 && len == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + a, k - a);
	else
		_strncpy(new_p, buf + a, k - a + 1);

	s += k - a;
	a = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - function that blocks control C
 * @sig_num: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

