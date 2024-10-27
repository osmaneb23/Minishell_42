#include "../includes/minishell.h"

// changer PWD dans l'env
//! BESOIN DE CHANGE PWD ET OLDPWD (et donc export) POUR CHEMEIN ABSOLUT ET RELATIF  
int change_cd(char *direction)
{
    int audd;

    char *res;
    t_data *data = get_data(); 
    if (ft_strcmp(direction, "") == 0 || ft_strcmp(direction, "~") == 0 || ft_strcmp(direction, "--") == 0)
    {
        res = search_env_var("HOME");
        if (!res)
            return (FAILURE);
        chdir(res);
        free(res);
        return (SUCCESS);
    }
    else 
        audd = chdir(direction);
    if (audd == -1)
    {    
        // char *new_direction = ft_strjoin(getenv("PWD"), direction); //! BESOIN DE CHANGE PWD ET OLDPWD (et donc export) POUR CHEMEIN ABSOLUT ET RELATIF  
        // printf("=======%s\n", new_direction);
        // audd = chdir(new_direction);
        // free(new_direction);
        if (audd != -1)
            return (SUCCESS);
        printf("Error: cd: %s: No such file or directory\n", direction);
        return (ERROR);
    }
    return (SUCCESS);
}

// with only a relative or absolute path 
int ft_cd(char **line)
{
    int exit_status;
    int nb_args;
    nb_args = 2; /*count_args(token);*/

    if (nb_args > 2)
    {    
        printf("Error: cd: Too many arguments\n");
        return (ERROR);
    }
    if (nb_args == 2)
        change_cd(line[1]);
}

//? ==========================
//? gestion du PWD et OLDPWD dans envp pour gerer les chemains relatifs et absolu avec cd 