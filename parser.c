#include "shell.h"

/**
 * is_cmd - checks whether a file is an executable command.
 * 
 * @info: a struct containing information about the file
 * @path: path to the file
 *
 * Return: 1 if the file is an executable command.
 *	0 otherwise.
 */
int is_cmd(info_t *info, char *path)
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
 * dup_chars - creates a copy of the characters in a given range.
 * 
 * @stop: the index of the last character to be duplicated.
 * @pathstr: a string containing the characters to be duplicated.
 * @start: the index of the first character to be duplicated.
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - locates the specified command in the PATH string.
 *
 * @cmd: the command to be located within the PATH string.
 * @info: a structure containing additional information
 * 	related to the command.
 * @pathstr: a string containing the PATH environment variable.
 *
 * Return: If the command is found within the PATH string,
 *	the function returns the full path of the command. 
 *	If the command is not found, the function returns NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
