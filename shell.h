#ifndef SHELL_H
#define SHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
<<<<<<< HEAD
#include <stdlib.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

typedef struct liststr list_t;
struct liststr
{
	int num;
	char *str;
	list_t *next;
};

typedef struct passinfo info_t;
struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
};

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

typedef struct builtin builtin_table;
struct builtin
{
	char *type;
	int (*func)(info_t *);
};

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int loophsh(char **);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);
=======
#include <dirent.h>
#include <signal.h>
/*constants*/
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1
#define min(x, y) (((x) < (y)) ? (x) : (y))
/**
 * structmap-a struct that maps a command name to a function
 * @command_name: name of the command
 * @func: the function that executes the command
 */
typedef struct map
{
char *command_name;
void (*func)(char **command);
} function_map;
extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;
/*helpers*/
void print(char *, int);
char **tokenizer(char *, char *);
void remove_newline(char *);
>>>>>>> cf3803d841549339ecd770dee9fe4e9abb41e45b
int _strlen(char *);
void _strcpy(char *, char *);
/*helpers2*/
int _strcmp(char *, char *);
char *_strcat(char *, char *);
<<<<<<< HEAD
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
char **strtow(char *, char *);
char **strtow2(char *, char);
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);
int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);
int _myhistory(info_t *);
int _myalias(info_t *);
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
void clear_info(info_t *);
void set_info(info_t *, char **...);

#endif /* _SHELL_H_ */
=======
int _strspn(char *, char *);
int _strcspn(char *, char *);
char *_strchr(char *, char);
/*helpers3*/
char *_strtok_r(char *, char *, char **);
int _atoi(char *);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void ctrl_c_handler(int);
void remove_comment(char *);
/*utils*/
int parse_command(char *);
void execute_command(char **, int);
char *check_path(char *);
void (*get_func(char *))(char **);
char *_getenv(char *);
/*built_in*/
void env(char **);
void quit(char **);
/*main*/
extern void non_interactive(void);
extern void initializer(char **current_command, int type_command);
#endif /*SHELL_H*/
>>>>>>> cf3803d841549339ecd770dee9fe4e9abb41e45b
