#include "shell.h"

/**
 * main - entry point
 *
 * Return: 0 on success, 1 on error.
 */
int main(int arguement_count, char **arguement_vector)
{
	strinput_array_gen info[] = { INITIALIZTION_DATA };
	int file_descriptor = 2;
	
//**this is assembly code used in interacting with hardware directly*/

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (file_descriptor)
		: "r" (file_descriptor));

	if (arguement_count == 2)
	{
		file_descriptor = open(arguement_vector[1], O_RDONLY);
		if (file_descriptor == -1)
		{
			if (error_number == EACCES)
				exit(126);
			if (error_number == ENOENT)
			{
				_inputStrPrint(arguement_vector[0]);
				_inputStrPrint(": 0: Can't open ");
				_inputStrPrint(arguement_vector[1]);
				_writechar('\n');
				_writechar(BUFFERFLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfile_descriptor = file_descriptor;
	}
	environ_linked_list_popul(info);
	FileHistory(info);
	main_shell_loop(info, arguement_vector);
	return (EXIT_SUCCESS);
}
