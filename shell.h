#ifndef _SHLIB_H_
#define _SHLIB_H_

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUFFERFLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096


/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2





extern char **environ;


typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

 
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfile_descriptor;
	int histcount;
} strinput_array_gen;

#define INITIALIZTION_DATA \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *Builtin = contains a builtin str and related func.
 *@type: the builtin comd flag.
 *@func: the func
 */
typedef struct builtin
{
	char *type;
	int (*func)(strinput_array_gen*);
} builtin_table;


/* refFile_shloop.c */
int main_shell_loop(strinput_array_gen*, char **);
int locate_buitin_func(strinput_array_gen*);
void locate_cmd_path(strinput_array_gen*);
void fork_exec_thread(strinput_array_gen*);

/* refFile_parser.c */
int CheckIf_FileExec_cmd(strinput_array_gen*, char *);
char *CharDuplication(char *, int, int);
char *locate_path_dir(strinput_array_gen*, char *, char *);

/* refFile_errors.c */
void _inputStrPrint(char *);
int _writechar(char);
int _putfile_descriptor(char c, int file_descriptor);
int _putsfile_descriptor(char *str, int file_descriptor);

/* refFile_string.c */
int _stringlength(char *);
int _strcomparision(char *, char *);
char *check_start(const char *, const char *);
char *_stringconcatenates(char *, char *);

/* refFile_string1.c */
char *_StringCopy(char *, char *);
char *_StringDup(const char *);
void _puts(char *);
int _putchar(char);

/* refFile_exits.c */
char *stringNcopy(char *, char *, int);
char *_stringNconcatenate(char *, char *, int);
char *_find_char_instr(char *, char);

/* refFile_tokenizer.c */
char **lexer(char *, char *);
char **lexer2(char *, char);

/* refFile_realloc.c */
char **memory_set(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void free_fd(char **);

/* refFile_memory.c */
int ptr_free(void **);

/* refFile_alphatoint.c */
int interarguement_counttive(strinput_array_gen*);
int check_if_delim(char, char *);
int _checkalphabet(int);
int _alphatoint(char *);

/* refFile_errors1.c */
int _errorAlphaToInterger(char *);
void PrintError(strinput_array_gen*, char *);
int printDec(int, int);
char *cvrt_no(long int, int, int);
void rmv_comments(char *);

/* refFile_builtin.c */
int _jmshexit(strinput_array_gen*);
int _jmshcd(strinput_array_gen*);
int _jmshhelp(strinput_array_gen*);

/* refFile_builtin1.c */
int _jmshhistory(strinput_array_gen*);
int _jmshalias(strinput_array_gen*);

/* refFile_getline.c */
ssize_t fetch_input(strinput_array_gen*);
int _get_line(strinput_array_gen*, char **, size_t *);
void signed_int_handler(int);

/* refFile_getinfo.c */
void erase_info(strinput_array_gen*);
void def_info(strinput_array_gen*, char **);
void mem_free_info(strinput_array_gen*, int);

/* refFile_environ.c */
char *_get_environment(strinput_array_gen*, const char *);
int _jmshenv(strinput_array_gen*);
int _jmshsetenv(strinput_array_gen*);
int _jmshunsetenv(strinput_array_gen*);
int environ_linked_list_popul(strinput_array_gen*);

/* refFile getenv.c */
char **get_environment(strinput_array_gen*);
int _unsetEnvironment(strinput_array_gen*, char *);
int _setEnvironment(strinput_array_gen*, char *, char *);

/* refFile_history.c */
char *get_history_file(strinput_array_gen*info);
int write_history(strinput_array_gen*info);
int FileHistory(strinput_array_gen*info);
int build_history_list(strinput_array_gen*info, char *buf, int linecount);
int renumber_history(strinput_array_gen*info);

/* refFile_lists.c */
list_t *AddNode(list_t **, const char *, int);
list_t *AddNodeEnd(list_t **, const char *, int);
size_t PrintiListString(const list_t *);
int DeleteNodeAtIndex(list_t **, unsigned int);
void list_free_memory(list_t **);

/* refFile_lists1.c */
size_t listLength(const list_t *);
char**ListToStrings(list_t *);
size_t PrintList(const list_t *);
list_t *node_begins_with(list_t *, char *, char);
ssize_t getNodeIndex(list_t *, list_t *);

/* refFile_vars.c */
int is_chain(strinput_array_gen*, char *, size_t *);
void check_chain(strinput_array_gen*, char *, size_t *, size_t, size_t);
int switch_alias(strinput_array_gen*);
int switch_vars(strinput_array_gen*);
int switch_string(char **, char *);

#endif
