/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:20:17 by febouana          #+#    #+#             */
/*   Updated: 2024/12/06 15:06:51 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int cmd_list_len(t_cmd *cmd)
{
    t_cmd *tmp;
    int i;
    if (!cmd)
        return (FAILURE);
    tmp = cmd;
    i = 0;
    while (tmp != NULL)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

int	add_cmd_to_list(t_cmd *cmd, t_cmd *data_cmd)
{
	t_cmd	*last;

	last = return_last_cmd_node(data_cmd);
	if (!last)
		return (cleanup(ERROR, "Error: impossible to get last command\n", ERROR,
				2));
	last->next = cmd;
	cmd->prev = last;
	return (SUCCESS);
}

//*OKOK
//? Compte le nombre de commandes en vérifiant les pipes
int count_nbr_cmd(t_token *token)
{
    t_token *tmp;
    int i = 0;

    if (!token)
        return (FAILURE);
    tmp = token;
    while (tmp)
    {
        if (strcmp(tmp->value, "|") == 0 || tmp->type == PIPE)
            i++;
        tmp = tmp->next;
    }
    return (i + 1);
}

t_cmd	*return_last_cmd_node(t_cmd *command)
{
	if (!command)
		return (NULL);
	while (command->next)
		command = command->next;
	return (command);
}

//*OKOK
//? Libère une liste chaînée de commandes
void free_all_cmd_nodes(t_cmd **cmd_list)
{
    t_cmd *current;
    t_cmd *next;

    if (!cmd_list || !(*cmd_list))
        return;
    current = *cmd_list;
    while (current)
    {
        next = current->next;
        ft_free_multi_array(current->cmd_param);
        free(current); //+ FREE LE NOEUD INIT DANS INIT_CMD_NODES()
        current = next;
    }
    *cmd_list = NULL;
}
