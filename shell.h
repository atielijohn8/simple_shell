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
 * @variableHandler: command that handles variable inputs
 * @*get_Path: get full path of the current dir
 * @ run_Cmd: take user input and runs
 * @stat: checks file status
 */

void variableHandler(char **av);
char *get_Path(char *command);
void run_Cmd(char **av);
int stat(const char *pathname, struct stat *statbuf);

#endif
