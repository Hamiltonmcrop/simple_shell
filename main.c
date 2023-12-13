#include "main.h"
/**
 * main - the main function
 *
 * Return: (Success) 0 always
 * ------- (Fail) we drop out the looser :)
 */
int main(void)
{
	sh_t data;
	int pl;

	mem_byte((void *)&data, 0, sizeof(data));
	signal(SIGINT, dir_source);
	while (1)
	{
		command_index(&data);
		if (show_line(&data) < 0)
		{
			if (isatty(STDIN_FILENO))
				PRINT("\n");
			break;
		}
		if (divide_line(&data) < 0)
		{
			dt_use(&data);
			continue;
		}
		pl = use_line(&data);
		if (pl == 0)
		{
			dt_use(&data);
			continue;
		}
		if (pl < 0)
		{
			show_issue(&data);
			continue;
		}
		if (wash_cmd(&data) < 0)
		{
			show_issue(&data);
			break;
		}
		dt_use(&data);
	}
	dt_use(&data);
	exit(EXIT_SUCCESS);
}

/**
 * show_line - read a line from the standard input
 * @data: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int show_line(sh_t *data)
{
	char *csr_ptr, *end_ptr, c;
	size_t size = BUFSIZE, read_st, length, new_size;

	data->line = malloc(size * sizeof(char));
	if (data->line == NULL)
		return (FAIL);
	if (isatty(STDIN_FILENO))
		PRINT(PROMPT);
	for (csr_ptr = data->line, end_ptr = data->line + size;;)
	{
		read_st = read(STDIN_FILENO, &c, 1);
		if (read_st == 0)
			return (FAIL);
		*csr_ptr++ = c;
		if (c == '\n')
		{
			*csr_ptr = '\0';
			return (SUCCESS);
		}
		if (csr_ptr + 2 >= end_ptr)
		{
			new_size = size * 2;
			length = csr_ptr - data->line;
			data->line = mem_real(data->line, size * sizeof(char),
						new_size * sizeof(char));
			if (data->line == NULL)
				return (FAIL);
			size = new_size;
			end_ptr = data->line + size;
			csr_ptr = data->line + length;
		}
	}
}
#define DELIMITER " \n\t\r\a\v"
/**
 * divide_line - splits line to tokens
 * @data: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int divide_line(sh_t *data)
{
	char *token;
	size_t size = TOKENSIZE, new_size, i = 0;

	if (_strcmp(data->line, "\n") == 0)
		return (FAIL);
	data->args = malloc(size * sizeof(char *));
	if (data->args == NULL)
		return (FAIL);
	token = strtok(data->line, DELIMITER);
	if (token == NULL)
		return (FAIL);
	while (token)
	{
		data->args[i++] =  token;
		if (i + 2 >= size)
		{
			new_size = size * 2;
			data->args = mem_real(data->args, size * sizeof(char *),
					new_size * sizeof(char *));
			if (data->args == NULL)
				return (FAIL);
			size = new_size;
		}
		token = strtok(NULL, DELIMITER);
	}
	data->args[i] = NULL;
	return (0);
}
#undef DELIMITER
#define DELIMITER ":"
/**
 * use_line - parses arguments to valid command
 * @data: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int use_line(sh_t *data)
{
	if (main_path_dir(data) > 0)
		return (SUCCESS);
	if (in_data_form(data) > 0)
	{
		if (handle_builtin(data) < 0)
			return (FAIL);
		return (NEUTRAL);
	}
	least_dir_file(data);
	return (SUCCESS);
}
#undef DELIMITER
/**
 * wash_cmd - process command and execute process
 * @data: a pointer to the struct of data
 *
 * Return: (Success) a positive number
 * ------- (Fail) a negative number
 */
int wash_cmd(sh_t *data)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(data->cmd, data->args, environ) < 0)
		data->error_msg = _strdup("not found\n");
			return (FAIL);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
	return (0);
}
