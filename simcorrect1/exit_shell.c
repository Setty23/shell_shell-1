#include "shell.h"

/**
 **_strncat - function that concatenates two strings
 *@dest: first string
 *@src: second string
 *@m: the no of bytes to be used
 *Return: concatenated string
 */
char *_strncat(char *dest, char *src, int m)
{
	int l, k;
	char *s = dest;

	l = 0;
	k = 0;
	while (dest[l] != '\0')
		l++;
	while (src[k] != '\0' && k < m)
	{
		dest[l] = src[k];
		l++;
		k++;
	}
	if (k < m)
		dest[l] = '\0';
	return (s);
}

/**
 **_strchr - function that locates a character in a string
 *@str: the string  parsed
 *@d: character
 *Return: (str)  ptr to  memory area
 */
char *_strchr(char *str, char d)
{
	do {
		if (*str == d)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * my_strncpy - Custom implementation of strncpy function
 * @dest: Pointer to the destination buffer
 * @src: Pointer to the source string
 * @n: Maximum number of characters to copy
 *
 * Return: Pointer to the destination buffer (dest)
 */
 
char *my_strncpy(char *dest, const char *src, size_t n)
{
	char *d = dest;

    /* Copy at most n characters from src to dest */
	while (*src && n > 0)
	{
		*d++ = *src++;
		n--;
	}

    /* Fill remaining space in dest with null characters if needed */
	while (n > 0)
	{
		*d++ = '\0';
		n--;
	}
	return (dest);
}
