#include "../../includes/minishell.h"

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
    while (tmp != NULL)
    {
        if (ft_strncmp(var, tmp->line, len) == 0)
        {
            del_node_t_env(&tmp);
            return (SUCCESS);
        }
        tmp = tmp->next;
    }
    return (FAILURE);
}

//! with no options
int ft_unset(char **cmd_param)
{
    if (!cmd_param || tabtablen(cmd_param) == 1 || ft_strcmp(cmd_param[1], "") == 0) // SI pas d'argument ==> RIEN + RETURN (//bash posix)
        return (ERROR);
    else
    {
        if (search_and_del(cmd_param[1]) == SUCCESS)
            return (SUCCESS);
        else
            printf("Error: unset: %s not found\n", cmd_param[1]); //! bash posix ne renvoi rien lui
    }
    return (FAILURE);
}
