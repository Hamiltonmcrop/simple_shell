#include "main.h"

/**
 * mem_real - reallocates memory block
 * @ptr: pointer to the previous memory
 * @old_size: the old size
 * @new_size: the new size
 *
 * Return: a pointer to the newly allocated memory
 */
void *mem_real(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *result;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	result = malloc(new_size);
	if (result == NULL)
		return (NULL);
	if (ptr == NULL)
	{
		ary_site(result, '\0', new_size);
		free(ptr);
	}
	else
	{
		file_cpy(result, ptr, old_size);
		free(ptr);
	}
	return (result);
}
/**
 * mem_byte - fills a memory with constant byte
 * @s: pointer to memory area
 * @n: first n bytes
 * @byt: constant byte
 *
 * Return: A pointer to a character
 */
char *mem_byte(char *s, char byt, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = byt;
	}
	return (s);
}
/**
 * dt_use - frees data
 * @data: the data structure
 *
 * Return: (Success) positive number
 * ------- (Fail) negative number
 */
int dt_use(sh_t *data)
{
	free(data->line);
	data->line = NULL;
	free(data->args);
	data->args = NULL;
	free(data->cmd);
	data->cmd = NULL;
	free(data->error_msg);
	data->error_msg = NULL;
	return (0);
}
/**
 * file_cpy - cpies memory area
 * @dest: Destination memory area
 * @src: Source memory area
 * @n: Amount of memory byte
 *
 * Return: A pointer to dest
 */
char *file_cpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}
