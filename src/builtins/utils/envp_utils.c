/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:11:27 by febouana          #+#    #+#             */
/*   Updated: 2024/12/13 19:26:18 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//+ Detruit une liste t_env
void destroy_envp_list(t_env **envp) 
{
    t_env *current;

    if (envp == NULL || *envp == NULL)
        return;
    current = *envp;
    while (current != NULL) 
    {
        t_env *next_node = current->next;
        del_node_envp(&current);
        current = next_node;
    }
    *envp = NULL;
}

//?OKOK
//+ Cherche et retourne le dernier noeud d'une liste
t_env	*find_last_node(t_env *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

//?OKOK
//+ Permet de supprimer un noeud dans la liste env
void del_node_envp(t_env **envp)
{
    t_env *del_node;
    t_env *new_next;
    t_data *data;

    if (envp == NULL || *envp == NULL)
        return;
    data = get_data();
    del_node = *envp;
    new_next = del_node->next;
    if (new_next)
        new_next->prev = del_node->prev;
    if (del_node->prev)
        del_node->prev->next = new_next;
    else
        data->envp = new_next;
    free(del_node);
}

//?OKOK
// + Permet d'ajouter un noeud a la liste env
int append_node_envp(t_env **envp, char *line)
{
    t_env *new_node;
    t_env *last_node;

    if (!envp)
        return (ERROR);
    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return (cleanup(ERROR, ERR_MALLOC, ERROR, 2));
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
    return (SUCCESS);
}

//?OKOK
//+ Permet de creer un env si minishell est exec avec env -i
int init_env_if_le_correcteur_clc(t_data* data)
{
	char	path[PATH_MAX];
	char	*tmp;

    if (getcwd(path, PATH_MAX) == NULL)
        return (1);
        
    tmp = ft_strjoin("PWD=", path);
    if (!tmp || append_node_envp(&data->envp, tmp) == ERROR)
        return (cleanup(ERROR, ERR_MALLOC, ERROR, 2));    
    tmp = ft_strdup("SHLVL=1");
    if (!tmp || append_node_envp(&data->envp, tmp) == ERROR)
        return (cleanup(ERROR, ERR_MALLOC, ERROR, 2)); 
    tmp = ft_strdup("_=/usr/bin/env");
    if (!tmp || append_node_envp(&data->envp, tmp) == ERROR)
        return (cleanup(ERROR, ERR_MALLOC, ERROR, 2)); 
    tmp = ft_strdup("OLDPWD");
    if (!tmp || append_node_envp(&data->envp, tmp) == ERROR)
        return (cleanup(ERROR, ERR_MALLOC, ERROR, 2)); 
    return (SUCCESS);
}

