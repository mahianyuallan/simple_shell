#include "shell.h"

/**
 * sign_get - Handle the SIGINT signal.
 *
 * This function is a signal handler for the SIGINT signal. It writes a newline
 * character and the shell prompt to the standard output.
 *
 * @val: The signal value (unused in this context).
 */
void sign_get(int val)
{
	(void)val;
	write(STDOUT_FILENO, "\n#cisfun$ ", 9);
}
