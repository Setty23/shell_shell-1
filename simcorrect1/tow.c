#include "shell.h"

/**
 * **strtow - functon that splits a string into words.
 * Repeat delimiters are ignored
 * @str: the input string
 * @delim: the delimeter string
 *
 * Return: a pointer to an array of strings,
 * NULL on failure
 */

char **strtow(char *str, char *delim)
{
	int i, j, k, word_len, num_words = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (delim == NULL)
		delim = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimeter(str[i], delim) && (is_delimeter(str[i + 1],
						delim) || !str[i + 1]))
		{
			num_words++;
		}
	if (num_words == 0)
		return (NULL);
	words = malloc((1 + num_words) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimeter(str[i], delim))
			i++;
		word_len = 0;
		while (!is_delimeter(str[i + word_len], delim) && str[i + word_len] != '\0')
			word_len++;
		words[j] = malloc((word_len + 1) * sizeof(char));
		if (words[j] == NULL)
		{
			for (i = 0; i < j; i++)
				free(words[i]);
			free(words);
			return (NULL);
		}
		for (k = 0; k < word_len; k++)
			words[j][k] = str[i++];
		words[j][word_len] = '\0';
	}
	words[j] = NULL;
	return (words);
}

/**
 * **strtow2 - function that splits a string into words
 * @str: the input string
 * @d: the delimeter
 *
 * Return: a pointer to an array of strings,
 * NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, y, a, b, numwords = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	c = malloc((1 + numwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (i = 0, y = 0; y < numwords; y++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		a = 0;
		while (str[i + a] != d && str[i + a] && str[i + a] != d)
			a++;
		c[y] = malloc((a + 1) * sizeof(char));
		if (!c[y])
		{
			for (a = 0; a < y; a++)
				free(c[a]);
			free(c);
			return (NULL);
		}
		for (b = 0; b < a; b++)
			c[y][b] = str[i++];
		c[y][b] = 0;
	}
	c[y] = NULL;
	return (c);
}
