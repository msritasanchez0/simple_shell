

#include "shell.h"

/**
 * is_excmd - function that checks if a file is an executable command
 * @info: information structure
 * @path: file path
 * Return: 1 if true, 0 otherwise
 */
int is_excmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - function that duplicates chars
 * @pstr: the path string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *dup_chars(char *pstr, int start, int stop)
{
	static char buf[1024];
	int m = 0, n = 0;

	for (n = 0, m = start; m < stop; m++)
		if (pstr[m] != ':')
			buf[n++] = pstr[m];
	buf[n] = 0;
	return (buf);
}

/**
 * find_path - function that finds command in string path
 * @info: the information structure
 * @pstr: the path str
 * @cmd: command to find
 * Return: full path of command or NULL
 */
char *find_path(info_t *info, char *pstr, char *cmd)
{
	int m = 0, curr_pos = 0;
	char *pth;

	if (!pstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pstr[m] || pstr[m] == ':')
		{
			pth = dup_chars(pstr, curr_pos, m);
			if (!*pth)
				_strcat(pth, cmd);
			else
			{
				_strcat(pth, "/");
				_strcat(pth, cmd);
			}
			if (is_cmd(info, pth))
				return (pth);
			if (!pstr[m])
				break;
			curr_pos = m + 1;
		}
		m++;
	}
	return (NULL);
}
