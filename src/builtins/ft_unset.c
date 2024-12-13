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
    len = ft_strlen(var);
    tmp = data->envp;
    while (tmp != NULL)
    {
        t_env *next = tmp->next; // Stocker le prochain élément
        if (ft_strncmp(var, tmp->line, len) == 0)
        {
            del_node_envp(&(data->envp)); // Passer l'adresse de la tête globale
            return (SUCCESS);
        }
        tmp = next; // Utiliser le pointeur stocké
    }
    return (ERROR);
}

// exit status OKOK
int	ft_unset(char **cmd_param)
{
	if (cmd_param[1] && ft_strcmp(cmd_param[1], "") != 0)
	{    
        if (strcmp(cmd_param[1], "_") == 0) // NON WALLAH MERCI BASH POSIX
            return (SUCCESS);
		if (search_and_del(cmd_param[1]) == SUCCESS){
			return (SUCCESS);}
		else
			printf("minishell: unset: %s not found\n", cmd_param[1]); // conforama utilisateur
	}
	return (SUCCESS);
}
