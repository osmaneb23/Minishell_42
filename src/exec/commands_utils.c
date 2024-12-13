/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:20:17 by febouana          #+#    #+#             */
/*   Updated: 2024/12/12 18:21:39 by apoet            ###   ########.fr       */
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
		return (cleanup(ERROR, "Error: last node inaccessible\n", ERROR,
				2));
	last->next = cmd;
	cmd->prev = last;
	return (SUCCESS);
}

//*OKOK
//? Compte le nombre de commandes en comptant le nbr de pipe
//! et si "< infile | cmd1 > outfile" == va compter 2 commandes alors que pas forcement  
//! et si "< infile cmd1 | cmd2" ; cmd1 va etre interprete comme un ARG 
//* meilleur solution = CONTINUER a suivre l'algo calculant le nbr de sequences dans le prompte selon le nbr de pipe...
//* ... mais rajouter par la suite un systeme de skip_cmd si noaud vide

bool there_is_cmd()
{
    t_data* data;
    t_token *tmp;

    data = get_data();
    tmp = data->token;
    while (tmp)
    {
        if ((tmp->type >= 1 && tmp->type <= 4) && tmp->next && tmp->next->next && tmp->next->next->type == ARG)
            if (check_command_in_path(tmp->next->next->value) == SUCCESS || is_builtin(tmp->next->next->value) == true)
                return (true);
        if (tmp->type == CMD)
            return (true);
        tmp = tmp->next;
    } 
    return (false);
}



int count_nb_sequences(t_token *token)
{
    int i;
    t_token *tmp;

    i = 0;
    tmp = token;
    while (tmp)
    {
        if (strcmp(tmp->value, "|") == 0 && tmp->type == PIPE)
            i++;
        tmp = tmp->next;
    }
    if (i == 0) // SI pas de pipe...
    {
        // if (there_is_cmd() == true)
            return (1); // 1) il y a au moins une cmd donc une sequence //! cas heredoc de con
        // return (FAILURE); // 2) il n'y pas de cmd dans une sequence dooooonc nsm
    }
    return (i + 1); // SI presence d'au moins 1 pipe == presence de 2 sequences
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
