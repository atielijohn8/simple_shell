#include "shell.h"

/**
 * getHistoryFile -  history file
 * @info: parameter struct
 *
 * Return: allocated string containg his file
 */

char *getHistoryFile(ShellInformation *info)
{
	char *buf, *dir;

	dir = getEnvironmentVariable(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (string_Length(dir) + string_Length(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	copy_String(buf, dir);
	concatenate_Strings(buf, "/");
	concatenate_Strings(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file
 * @info: the parameter struct
 *
 * Return: 1  success, else -1
 */
int write_history(ShellInformation *info)
{
	ssize_t fd;
	char *filename = getHistoryFile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		 putStringTo_File(node->str, fd);
		 putCharacter_To_File('\n', fd);
	}
	 putCharacter_To_File(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads hisfrom file
 * @info:  struct
 *
 * Return: histcount success, 0 otherwise
 */
int read_history(ShellInformation *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		deleteNodeAtIndex(&(info->history), 0);
	renumberHistory(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history 
 * @info: Structure containing possible arguments. 
 * @buf: buffer
 *
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(ShellInformation *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumberHistory - renumbers the history linked list after changes
 *                   take place
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumberHistory(ShellInformation *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
