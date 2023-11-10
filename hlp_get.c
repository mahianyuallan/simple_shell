#include "shell.h"


int hlp_get(dt_shell *sh_data)
{
    switch (sh_data->args[1] ? _strcmp(sh_data->args[1], "") : 0) {
    case 0:
        aux_help_general();
        break;
    case 1:
        aux_help_setenv();
        break;
    case 2:
        aux_help_env();
        break;
    case 3:
        aux_help_unsetenv();
        break;
    case 4:
        aux_help();
        break;
    case 5:
        aux_help_exit();
        break;
    case 6:
        aux_help_cd();
        break;
    case 7:
        aux_help_alias();
        break;
    default:
        write(STDERR_FILENO, sh_data->args[0], _strlen(sh_data->args[0]));
    }

    sh_data->status = 0;
    return (1);
}
