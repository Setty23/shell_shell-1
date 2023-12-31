#include "shell.h"

/**
 * is_chain - a function that checks if the char is a chain delimeter.
 * @info: structure containing arguments
 * @buf: the character buffer
 * @p: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 if not
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	char *chain_delims = ";&|";
	char c = buf[*p];

	if (c == '\0')
		return (0);
	if (my_strchr(chain_delims, c) != NULL)
	{
		if (c == '|' && buf[*p + 1] == '|')
		{
			*p += 2;
			return (1);
		}

		if (c == '&' && buf[*p + 1] == '&')
		{
			*p += 2;
			return (1);
		}
		*p += 1;
		return (1);
	}
	return (0);
}

/**
 * check_chain - function that checks chain of string
 * @info: the parameter struct containing arguments
 * @buf: the char buffer
 * @p: address of current position in buffer
 * @i: starting position in buffer
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t x = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			x = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			x = len;
		}
	}

	*p = x;
}

/**
 * replace_alias - function that replaces an aliases in the tokenized string
 * @info: the parameter struct containing arguments
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int t;
	list_t *node;
	char *c;

	for (t = 0; t < 10; t++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		c = my_strchr(node->str, '=');
		if (!c)
			return (0);
		c = my_strdup(c + 1);
		if (!c)
			return (0);
		info->argv[0] = c;
	}
	return (1);
}

/**
 * replace_vars - function that replaces environment vars the tokenized strings
 * @info: the parameter struct that contains arguments
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int t = 0;
	list_t *node;

	for (t = 0; info->argv[t]; t++)
	{
		if (info->argv[t][0] != '$' || !info->argv[t][1])
			continue;

		if (!my_strcmp(info->argv[t], "$?"))
		{
			replace_string(&(info->argv[t]),
				my_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!my_strcmp(info->argv[t], "$$"))
		{
			replace_string(&(info->argv[t]),
				my_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[t][1], '=');
		if (node)
		{
			replace_string(&(info->argv[t]),
				my_strdup(my_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[t], my_strdup(""));

	}
	return (0);
}

/**
 * replace_string - function that replaces a string
 * @old: old string to replace
 * @new: new string to replace @old
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
