#include "../../includes/minishell.h"

int cmd_list_envp(t_env *envp)
{
    t_env *tmp;
    int i;

    if (!envp)
        return (FAILURE);
    tmp = envp;
    i = 0;
    while (tmp != NULL)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

//+ Permet de chercher puis supprimer la VAR donnee en argument
int search_and_del(char *var)
{
    int len;
    t_env *tmp;
    t_data *data;

    data = get_data();
	if (data->envp == NULL || !var)
		return (ERROR);
    len = ft_strlen(var);
    tmp = data->envp;
    if (cmd_list_envp(data->envp) == 1) //! A TESTER 
        append_node_envp(&data->envp, ""); //! reverifier dans append et supp "" si on ajoute un nv node
    while (tmp != NULL)
    {
        if (ft_strncmp(var, tmp->line, len) == 0)
        {
            del_node_envp(&tmp);
            return (SUCCESS);
        }
        tmp = tmp->next;
    }
    return (FAILURE);
}

//! with no options
int ft_unset(char **cmd_param)
{
    if (!cmd_param || ft_multi_array_len(cmd_param) == 1 || ft_strcmp(cmd_param[1], "") == 0) // SI pas d'argument ==> RIEN + RETURN (//bash posix)
        return (ERROR);
    else
    {
        if (search_and_del(cmd_param[1]) == SUCCESS)
            return (SUCCESS);
        else
            printf("Error: unset: %s not found\n", cmd_param[1]); //! bash posix ne renvoi rien lui
    }
    return (SUCCESS);
}
