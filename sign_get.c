#include "shell.h"


void sign_get(int val)
{
	(void)val;
	write(STDOUT_FILENO, "\n#cisfun$ ", 9);
}