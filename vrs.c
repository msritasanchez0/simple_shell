#include "shell.h"

/**
 * replace_substring - replaces a substring in a string with another string
 * @str: pointer to string to modify
 * @old: pointer to substring to replace
 * @new: pointer to replacement string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_substring(char **str, const char *old, const char *new)
{
    char *pos = *str;
    int count = 0;
    size_t old_len = strlen(old);
    size_t new_len = strlen(new);

    while ((pos = strstr(pos, old)) != NULL) {
        char *temp = malloc(strlen(*str) - old_len + new_len + 1);
        if (temp == NULL) {
            perror("malloc");
            return 0;
        }
        strncpy(temp, *str, pos - *str);
        strncpy(temp + (pos - *str), new, new_len);
        strcpy(temp + (pos - *str) + new_len, pos + old_len);
        free(*str);
        *str = temp;
        pos += new_len;
        count++;
    }

    return count;
}

/**
 * is_chain_delimiter - test if current char in buffer is a chain delimiter
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain_delimiter(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;
    int is_delim = 0;

    if (buf[j] == '|' && buf[j + 1] == '|') {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CMD_OR;
        is_delim = 1;
    } else if (buf[j] == '&' && buf[j + 1] == '&') {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CMD_AND;
        is_delim = 1;
    } else if (buf[j] == ';') {
        buf[j] = 0;
        info->cmd_buf_type = CMD_CHAIN;
        is_delim = 1;
    }

    *p = j;
    return is_delim;
}

/**
 * should_continue_chaining - checks whether we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: void
 */
void should_continue_chaining(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->cmd_buf_type == CMD_AND && info->status) {
        buf[i] = 0;
        j = len;
    } else if (info->cmd_buf_type == CMD_OR && !info->status) {
        buf[i] = 0;
        j = len;
    }

    *p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 * @argv_idx: index of the argument to replace
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info, int argv_idx)
{
    list_t *node;
    char *p;

    node = node_starts_with(info->alias, info->argv[argv_idx], '=');
    if (!node)
        return (0);
    free(info->argv[argv_idx]);
    p = _strchr(node->str, '=');
    if (!p)
        return (0);
    p = _strdup(p + 1);
    if (!p)
        return (0);
    info->argv[argv_idx] = p;
    return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
    int i = 0;

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
        if (replace_alias(info, i))
            continue;
        if (replace_env(info, i))
            continue;
        replace_string(&info->argv[i], _strdup(""));
    }
    return (0);
}
