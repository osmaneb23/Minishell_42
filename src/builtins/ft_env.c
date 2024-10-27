#include "../includes/minishell.h"

t_env	*find_last_node(t_env *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

void append_envp(t_env **envp, char *line)
{
    t_env *new_node;
    t_env *last_node;

    if (!envp)
        return;
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return;
    new_node->next = NULL;
    new_node->line = line;
    if (*envp == NULL)
    {
        new_node->prev = NULL;
        *envp = new_node;
    }
    else
    {
        last_node = find_last_node(*envp);
        last_node->next = new_node;
        new_node->prev = last_node;
    }
}

void make_env(t_data *data, char **env)
{
    int i = 0;
    
    data->envp = NULL;
    while (env[i])
    {
        append_envp(&data->envp, env[i]);
        i++;
    }
}

//! pas d'ordre de prevu avec export
//! prevoir le cas si env -i
int ft_env()
{
    t_data *data = get_data();
    t_env *tmp;

    if (!data || !data->envp)
        return (ERROR);
    tmp = data->envp;
    while(tmp != NULL)
    {
        printf("%s\n", tmp->line);
        tmp = tmp->next;
    }
    return (SUCCESS);
}



//? ==========================
//? se renseigner sur le cas env -i