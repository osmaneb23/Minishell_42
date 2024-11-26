#include "../../includes/minishell.h"

//? OKOK
//+ Recherche dans env la variable donnee en argument
//+ et retourne la valeur associee
char *search_env_var(char *var)
{
    int len;
    char *value;
    t_env *tmp;
    t_data *data;

    if (!var)
        return (NULL);
    data = get_data();
    if (!data || !data->envp)
        return (NULL);
    len = ft_strlen(var);
    tmp = data->envp;
    while (tmp != NULL)
    {
        if (ft_strncmp(var, tmp->line, len) == 0 && tmp->line[len] == '=')
        {
            value = malloc(ft_strlen(tmp->line + len + 1) + 1);
            if (!value)
                return (NULL);
            ft_strcpy(value, tmp->line + len + 1);
            return (value);
        }
        tmp = tmp->next;
    }
    return (NULL);
}

int change_cd_env_var(char *symbole)
{
    char *res;
    char *path;

    if (ft_strcmp(symbole, "") == 0 || ft_strcmp(symbole, "~") == 0 || ft_strcmp(symbole, "--") == 0)
    {   
        path = "HOME";
        res = search_env_var(path); 
    }
    if (ft_strcmp(symbole, "-") == 0)
    {
        path = "OLDPWD";
        res = search_env_var(path);
    }
    if (!res)
    {
        printf("Error: cd: %s not set\n", path);
        return (ERROR);
    }
    chdir(res);
    free(res);
    return (SUCCESS);
}

//? OKOK
int change_cd(char *direction)
{
    char oldpwd[PATH_MAX];
    char pwd[PATH_MAX];

    getcwd(oldpwd, PATH_MAX);

    if (ft_strcmp(direction, "") == 0 || ft_strcmp(direction, "~") == 0 ||\
        ft_strcmp(direction, "--") == 0 || ft_strcmp(direction, "-") == 0)
        change_cd_env_var(direction);  
    
    else if (chdir(direction) == -1) 
    {    
        printf("Error: cd: %s: No such file or directory\n", direction);
        return (FAILURE);
    }
    remplace_if_already_exist("OLDPWD", oldpwd);
    getcwd(pwd, PATH_MAX);
    remplace_if_already_exist("PWD", pwd);   
    return (SUCCESS);
}

int ft_cd(char **cmd_param)
{
    int exit;
    int nbr_param;
    
    nbr_param = tabtablen(cmd_param);
    if (nbr_param > 2)
    {    
        printf("Error: cd: Too many arguments\n");
        return (ERROR);
    }
    if (nbr_param == 2)
        exit = change_cd(cmd_param[1]);
    if (nbr_param == 1) 
        exit = change_cd("");    
    return (exit);    
}
