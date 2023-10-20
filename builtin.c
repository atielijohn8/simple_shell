#include "shell.h"

/**
 * exit_Custom_Shell - exits  shell
 * @info: Structure containing potential arguments.
 *        used in shell
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0)info,argv[0] != "exit"
 */
int exit_Custom_Shell(ShellInformation *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			printError_Message(info->argv[1]);
			printCharacter('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * changeDirectory - changes the current directory of the
 *                    current process 
 * @info: Structure containing possible arguments. Used to maintain
 *          const function prototype.
 *  Return: (0) succcsess
 */
int changeDirectory(ShellInformation *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		print_String("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getEnvironmentVariable(info, "HOME=");
		if (!dir)
			chdir_ret = 
				chdir((dir = getEnvironmentVariable(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (string_compare(info->argv[1], "-") == 0)
	{
		if (!getEnvironmentVariable(info, "OLDPWD="))
		{
			print_String(s);
			put_Character('\n');
			return (1);
		}
		print_String(getEnvironmentVariable(info, "OLDPWD=")), put_Character('\n');
		chdir_ret = 
			chdir((dir = getEnvironmentVariable(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		printError_Message(info->argv[1]), printCharacter('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", getEnvironmentVariable(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * displayHelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int displayHelp(ShellInformation *info)
{
	char **arg_array;

	arg_array = info->argv;
	print_String("help call works Function not  implemented \n");
	if (0)
		print_String(*arg_array);
	return (0);
}
