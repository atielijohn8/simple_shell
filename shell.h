#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

extern char **environ;

/**
 * get_Path - get full path of the current dir
 * @command:  comd to get the full path of
 * directory
 * Return: fullpath of cmd
 */
char *get_Path(char *command);

/**
 * run_Cmd - take input from user
 * run it
 * @av: string array represrnting cmd and its arguments
 */
void run_Cmd(char **av);

/**
 * stat - file status
 * @pathname: file path
 * @statbuf: struct pointer
 * where struct will be stored
 * Return: (0)success, (-1) failure
 */
int stat(const char *pathname, struct stat *statbuf);

#endif
