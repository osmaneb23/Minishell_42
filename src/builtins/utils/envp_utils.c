/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:11:27 by febouana          #+#    #+#             */
/*   Updated: 2024/12/06 14:57:14 by febouana         ###   ########.fr       */
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
        del_node_t_env(&current);
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
//+ Permet de supprimer une noeud dans la liste env
void	del_node_t_env(t_env **envp)
{
	t_env	*del_node;
	t_env	*new_next;

	if (envp == NULL || *envp == NULL)
		return ;
	del_node = *envp;
	new_next = del_node->next;
	if (new_next)
		new_next->prev = del_node->prev;

	if (del_node->prev)
		del_node->prev->next = new_next;

	*envp = new_next;
	del_node->next = NULL;
	del_node->prev = NULL;
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
        return (ERROR);
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
    
    tmp = ft_strdup("OLDPWD");
    if (!tmp || append_node_envp(&data->envp, tmp) == ERROR || getcwd(path, PATH_MAX) == NULL)
        return (ERROR); 
    tmp = ft_strjoin("PWD=", path);
    if (!tmp || append_node_envp(&data->envp, tmp) == ERROR)
        return (ERROR); 
    return (SUCCESS);
}

