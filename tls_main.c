#include "main.h"

/**
 * souce_move - convert integer to array
 * @n: the given number
 *
 * Return: a pointer to the null terminated string
 */
char *souce_move(unsigned int n)
{
	int len = 0, i = 0;
	char *s;

	len = num_len(n);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	*s = '\0';
	while (n / 10)
	{
		s[i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	s[i] = (n % 10) + '0';
	reference_array(s, len);
	s[i + 1] = '\0';
	return (s);
}
/**
 * _atoi - converts character to integer
 * @c: the given character
 *
 * Return: An integer
 */
int _atoi(char *c)
{
	unsigned int val = 0;
	int sign = 1;

	if (c == NULL)
		return (0);
	while (*c)
	{
		if (*c == '-')
			sign *= (-1);
		else
			val = (val * 10) + (*c - '0');
		c++;
	}
	return (sign * val);
}

/**
 * num_len - Determine the number of digit int integer
 * @num: the given number
 *
 * Return: the length of the integer
 */
int num_len(int num)
{
	int len = 0;

	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}
/**
 * show_issue - prints error
 * @data: the data structure pointer
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int show_issue(sh_t *data)
{
	char *idx = souce_move(data->index);

	PRINT("hsh: ");
	PRINT(idx);
	PRINT(": ");
	PRINT(data->args[0]);
	PRINT(": ");
	PRINT(data->error_msg);
	free(idx);
	return (0);
}

/**
 * main_hist - prints error
 * @data: the data structure pointer
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int main_hist(sh_t *data __attribute__((unused)))
{
	char *filename = "history";
	char *line_of_history = "this is a line of history";
	ssize_t fd, w;
	int len;

	if (!filename)
		return (-1);
	fd = open(filename, O_RDWR | O_APPEND);
	if (fd < 0)
		return (-1);
	if (line_of_history)
	{
		while (line_of_history[len])
			len++;
		w = write(fd, line_of_history, len);
		if (w < 0)
			return (-1);
	}
	return (1);
}
