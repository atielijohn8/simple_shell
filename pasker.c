#include "shell.h"

/**
 * isBuiltinCommand - determines if a file is an executable comd
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 true, 0 otherwise
 */
int isBuiltinCommand(ShellInformation *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicateCharacters - duplicates characters
 * @pathstr:  PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer  new buffer
 */
char *duplicateCharacters(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * findExecutablePath - finds this command in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the commandto find
 *
 * Return: full path of cmd if found or NULL
 */
char *findExecutablePath(ShellInformation *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((string_Length(cmd) > 2) && starts_With(cmd, "./"))
	{
		if (isBuiltinCommand(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicateCharacters(pathstr, curr_pos, i);
			if (!*path)
				concatenate_Strings(path, cmd);
			else
			{
				concatenate_Strings(path, "/");
				concatenate_Strings(path, cmd);
			}
			if (isBuiltinCommand(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
