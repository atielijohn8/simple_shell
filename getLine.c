#include "shell.h"

/**
 * input_buf - buffers chained comds
 * @info: struct
 * @buf:   buffer adress
 * @len: address of len 
 *
 * Return: bytes read
 */
ssize_t input_buf(ShellInformation *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) 
	{
		
		free(*buf);
		*buf = NULL;
		signal(SIGINT, handleSignalInterrupt);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; 
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line 
 * @info:struct
 *
 * Return: bytes read
 */
ssize_t get_input(ShellInformation *info)
{
	static char *buf; 
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	put_Character(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) 
		return (-1);
	if (len)	
	{
		j = i; 
		p = buf + i; 

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{ 
			if (isCommandChaining(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; 
		if (i >= len) 
		{
			i = len = 0; 
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; 
		return (string_Length(p)); 
	}

	*buf_p = buf; 
	return (r); 
}

/**
 * read_buf - reads buffer
 * @info: struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(ShellInformation *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input 
 * @info:  struct
 * @ptr: address  pointer to buffer, can set to  NULL
 * @length: size  preallocated ptr buffer if not equal to NULL
 *
 * Return: s
 */
int _getline(ShellInformation *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = findFirst_Occurrence(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = resize_Memory(p, s, s ? s + k : k + 1);
	if (!new_p) 
		return (p ? free(p), -1 : -1);

	if (s)
		concatenate_N_Characters(new_p, buf + i, k - i);
	else
		copy_N_Characters(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * handleSignalInterrupt - blocks 
 * @sig_num: signal number
 *
 * Return: void
 */
void handleSignalInterrupt(__attribute__((unused))int sig_num)
{
	print_String("\n");
	print_String("$ ");
	put_Character(BUF_FLUSH);
}
