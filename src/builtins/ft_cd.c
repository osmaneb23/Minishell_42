#include "../includes/minishell.h"

void *get_data()
{
    t_data data;
    return (&data);
}

int ft_cd(char *direction)
{
    t_data *data = get_data();
    char *res;

    if (direction == "")
    {
        res = ft_strjoin("/home/", data->username);
        chdir(res);
        ft_pwd();
        return (SUCCESS);
    }
    if (chdir(direction) != 0)
    {    
        perror("Error: ft_cd:\n");
        return (ERROR);
    }
    else
        ft_pwd();
    return (SUCCESS);
}