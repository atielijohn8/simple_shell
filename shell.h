#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo arguements to pass into a function,
 *		hence uniform prototype for function pointer struct
 *@arg: str generated from getline containing arguements
 *@argv: an array of strings generated from
 *       from the arguments
 *@path: a string representing the current path
 *@argc: argument count
 *@line_count: line count processed
 *@err_num: error code for exit() calls
 *@linecount_flag: flag indicating count input
 *@fname: filename
 *@env: local copy to env to linked list
 *@environ: modified cp of env from linked list
 *@history: node hidtory
 *@alias: node the aliases
 *@custom_env_changed: this is a flag indicating that 
 *             environment was changed
 *@status: return  status of last executed command
 *@cmd_buf: address of pointer to command buffer
 *@cmd_buf_type: fd reading input lines
 *@readfd: input lines
 *@histcount: count of hist numbers
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; 
	int cmd_buf_type;
	int readfd;
	int histcount;
} ShellInformation;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - stores builtin string and related function
 *@type:  builtin command flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(ShellInformation *);
} builtin_table;


/*  refFile_shloop.c */
int  customShellMain(ShellInformation *, char **);
int findBuiltinCommand(ShellInformation *);
void  findExecutableCommand(ShellInformation *);
void executeCommand(ShellInformation *);

/*  refFile_parser.c */
int isBuiltinCommand(ShellInformation *, char *);
char *duplicateCharacters(char *, int, int);
char *findExecutablePath(ShellInformation *, char *, char *);

/* loopCustomShell.c */
int loopCustomShell(char **);

/*  refFile_errors.c */
void printError_Message(char *);
int printCharacter(char);
int  putCharacter_To_File(char c, int fd);
int  putStringTo_File(char *str, int fd);

/*  refFile_string.c */
int string_Length(char *);
int string_compare(char *, char *);
char *starts_With(const char *, const char *);
char *concatenate_Strings(char *, char *);

/*  refFile_string1.c */
char *copy_String(char *, char *);
char *duplicate_String(const char *);
void print_String(char *);
int put_Character(char);

/*  refFile_exits.c */
char *copy_N_Characters(char *, char *, int);
char *concatenate_N_Characters(char *, char *, int);
char *findFirst_Occurrence(char *, char);

/*  refFile_tokenizer.c */
char **tokenizeString(char *, char *);
char **tokenizeString_Opt2(char *, char);

/*  refFile_realloc.c */
char *make_memset(char *, char, unsigned int);
void freeMemory(char **);
void *resize_Memory(void *, unsigned int, unsigned int);

/*  refFile_memory.c */
int freeBlock(void **);

/*  refFile_atoi.c */
int process_Interactive_Mode(ShellInformation *);
int is_Delimiter(char, char *);
int _isalpha(int);
int _atoi(char *);

/*  refFile_errors1.c */
int _erratoi(char *);
void print_error(ShellInformation *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/*  refFile_builtin.c */
int exit_Custom_Shell(ShellInformation *);
int changeDirectory(ShellInformation *);
int displayHelp(ShellInformation *);

/*  refFile_builtin1.c */
int access_History(ShellInformation *);
int aliasCommand(ShellInformation *);

/* refFile_getline.c */
ssize_t get_input(ShellInformation *);
int _getline(ShellInformation *, char **, size_t *);
void handleSignalInterrupt(int);

/*  refFile_getinfo.c */
void clear_info(ShellInformation *);
void set_info(ShellInformation *, char **);
void freeShellInfo(ShellInformation *, int);

/*  refFile_environ.c */
char *getEnvironmentVariable(ShellInformation *, const char *);
int manageEnvironment(ShellInformation *);
int setEnvironmentVariable(ShellInformation *);
int unsetEnvironmentVariable(ShellInformation *);
int populate_EnvironmentList(ShellInformation *);

/*  refFile_getenv.c */
char **get_environ(ShellInformation *);
int _unsetenv(ShellInformation *, char *);
int _setenv(ShellInformation *, char *, char *);

/*  refFile_history.c */
char *getHistoryFile(ShellInformation *info);
int write_history(ShellInformation *info);
int read_history(ShellInformation *info);
int build_history_list(ShellInformation *info, char *buf, int linecount);
int renumberHistory(ShellInformation *info);

/*  refFile_lists.c */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int deleteNodeAtIndex(list_t **, unsigned int);
void freeLinkedList(list_t **);

/*  refFile_lists1.c */
size_t listLength(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *findNodeStartsWith(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

/*  refFile_vars.c */
int isCommandChaining(ShellInformation *, char *, size_t *);
void check_chain(ShellInformation *, char *, size_t *, size_t, size_t);
int replaceAlias(ShellInformation *);
int replace_vars(ShellInformation *);
int replace_string(char **, char *);

#endif
