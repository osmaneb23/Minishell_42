#include "../includes/minishell.h"

//! besoin d'actualiser un data.env avec old_cwd et new_cwd ??
int ft_cd(char *direction)
{
    char *res;
    t_data *data = get_data(); 

    if (chdir(direction) == -1)
    {    
        printf("Error: ft_cd: %s: No such file or directory\n", direction);
        return (ERROR);
    }
    if (strcmp(direction, "") == 0)
    {
        res = ft_strjoin("/home/", data->username);
        if (!res)
            return (FAILURE);
        chdir(res);
        res = data->cwd;
        free(res);
        ft_pwd();
        return (SUCCESS);
    }
    else
    {
        ft_pwd();
        res = data->cwd;
    }
    return (SUCCESS);
}