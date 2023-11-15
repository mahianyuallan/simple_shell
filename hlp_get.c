#include "shell.h"

/**
 * hlp_get - Display help information based on the provided arguments.
 *
 * This function displays help information based on the provided arguments.
 * It checks the value of sh_data->args[1] to determine which help information
 * to display and sets the status in the dt_shell structure accordingly.
 *
 * @sh_data: Pointer to the dt_shell structure.
 *
 * Return: Always returns 1.
 */
int hlp_get(dt_shell *sh_data)
{
    switch (sh_data->args[1] ? _strcmp(sh_data->args[1], "") : 0)
    {
        case 0:
            gen_help_ax();
            break;
        case 1:
            envirset_help_ax();
            break;
        case 2:
            envir_help_ax();
            break;
        case 3:
            envirunset_help_ax();
            break;
        case 4:
            help_ax();
            break;
        case 5:
            exit_help_ax();
            break;
        case 6:
            cmd_help_ax();
            break;
        case 7:
            alias_help_ax();
            break;
        default:
            write(STDERR_FILENO, sh_data->args[0], _strlen(sh_data->args[0]));
    }

    sh_data->status = 0;
    return (1);
}
