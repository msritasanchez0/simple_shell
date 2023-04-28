#include "shell.h"
char **commands = NULL;
char *line = NULL;
char *shell_name = NULL;
int status = 0;
/**
 * main - the main shell code
 * @argc: number of arguments passed
 * @argv: program arguments to be parsed
 * Return: 0 on success
 */
int main(int argc __attribute__((unused)), char **argv)
{
<<<<<<< HEAD
	info_t info[] = { INFO_INIT };
	int fd = STDERR_FILENO;

	/* increment fd by 3 using inline assembly */
	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
=======
char **current_command = NULL;
int i, type_command = 0;
size_t n = 0;
signal(SIGINT, ctrl_c_handler);
shell_name = argv[0];
while (1)
{
non_interactive();
print(" ($) ", STDOUT_FILENO);
if (getline(&line, &n, stdin) == -1)
{
free(line);
exit(status);
}
remove_newline(line);
remove_comment(line);
commands = tokenizer(line, ";");
for (i = 0; commands[i] != NULL; i++)
{
current_command = tokenizer(commands[i], " ");
if (current_command[0] == NULL)
{
free(current_command);
break;
}
type_command = parse_command(current_command[0]);
/* initializer -   */
initializer(current_command, type_command);
free(current_command);
}
free(commands);
}
free(line);
return (status);
>>>>>>> cf3803d841549339ecd770dee9fe4e9abb41e45b
}
