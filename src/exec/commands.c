/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:43:47 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/12 22:39:52 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*OKOK
//? Compte les paramètres de commande
int count_cmd_param(t_token *og_token)
{
    t_token *token = og_token;
    unsigned int i = 0;

    while (token && token->type != PIPE)
    {
        if (token->type >= 1 && token->type <= 4)
        {
            if (token->next && token->next->type == ARG)
                i--;
        }
        else
            i++;
        token = token->next;
    }
    return (i);
}

//*OKOK
//? Initialise les paramètres de commande
char **init_cmd_param(t_token *og_token)
{
    char **cmd_param;
    int i;
    t_token *token;

    token = og_token;
    i = count_cmd_param(token);
    if (i == 0 || i == FAILURE)
        return (NULL);
    cmd_param = malloc(sizeof(char *) * (i + 1));
    if (!cmd_param)
        return (print_error(ERR_MALLOC), NULL); //! cleanup
    cmd_param[i] = NULL;
    i = 0;
    while (token && token->type != PIPE)
    {
        if (token->type >= 1 && token->type <= 4)
        {
            if (token->next && token->next->type == ARG)
                token = token->next->next;
			else
                return (NULL);
        }
        else
        {
            cmd_param[i] = ft_strdup(token->value);
            if (!cmd_param[i])
                return (print_error(ERR_MALLOC), NULL); //! cleanup
            i++;
            token = token->next;
        }
    }
    return (cmd_param);
}

//*OKOK
//? Remplit les nœuds de commandes avec des données
int fill_cmd_nodes(t_data *data)
{
    t_cmd *cmd;
    t_token *token;

    token = data->token;
    cmd = data->cmd;
    while (token && cmd)
    {
        if ((token->type >= 1 && token->type <= 4) && token->next && token->next->type == ARG)
            if (fill_cmd_nodes_redirections(cmd, token) == ERROR)
                return(ERROR);
        if (token && token->type == PIPE)
        {
            if (!cmd->cmd_param) //! ne change pas de noeud si pas de cmd trouve
            {    
                cmd->skip_cmd = true;
                // cmd->cmd_param = malloc(sizeof(char *) * 3);
                // cmd->cmd_param[0] = ft_strdup("");
                // cmd->cmd_param[1] = ft_strdup("");
                // cmd->cmd_param[2] = ft_strdup("");
            }
            cmd = cmd->next;
        }
        if (token && token->type == CMD)
        {
			cmd->cmd_param = init_cmd_param(token);
			if (!cmd->cmd_param)
				return (ERROR); //besoin de free les precedents noeud si deja init
        }
    	token = token->next;
    }
    return (SUCCESS);
}

//*OKOK
//? Initialise les nœuds de commandes 
int init_cmd_nodes(t_data *data)
{
    t_cmd *cmd;
    t_token *token;
    int nb_sq;

    token = data->token;
    nb_sq = count_nb_sequences(token);
    if (nb_sq == FAILURE)
        return (ERROR);
    while (nb_sq > 0)
    {
        cmd = malloc(sizeof(t_cmd));
        if (!cmd)
            return (cleanup(ERROR, ERR_MALLOC, ERROR, 2));
        cmd->infile= -2;
        cmd->outfile = -2;
        cmd->cmd_param = NULL;
        cmd->next = NULL;
        cmd->prev = NULL;
        cmd->skip_cmd = false;
        if (!data->cmd)
            data->cmd = cmd;
        else
            add_cmd_to_list(cmd, data->cmd);
        nb_sq--;
    }
    return (SUCCESS);
}

int init_cmd(t_data *data)
{
    if (init_cmd_nodes(data) == ERROR)
        return (ERROR); 
    if (fill_cmd_nodes(data) == ERROR)
        return (ERROR); 

//? test sip_cmd
    // t_cmd * tmp = data->cmd;
    // printf("1=%s\n", tmp->cmd_param[0]);
    // printf("1=%s\n", tmp->cmd_param[1]);
    // printf("1=%s\n", tmp->cmd_param[2]);
    // tmp = tmp->next;
    // printf("2=%s\n", tmp->cmd_param[0]);
    // printf("2=%s\n", tmp->cmd_param[1]);
    // printf("2=%s\n", tmp->cmd_param[2]);
    // tmp = tmp->next;
    // printf("3=%s\n", tmp->cmd_param[0]);
    // printf("3=%s\n", tmp->cmd_param[1]);
    // printf("3=%s\n", tmp->cmd_param[2]);

        
    return (SUCCESS);
}






// t_cmd * tmp = data->cmd;
// printf("\n\n1=%s\n", tmp->cmd_param[0]);
// printf("1=%s\n", tmp->cmd_param[1]);
// printf("1=%s\n\n", tmp->cmd_param[2]);
// tmp = tmp->next;
// printf("2=%s\n", tmp->cmd_param[0]);
// printf("2=%s\n", tmp->cmd_param[1]);
// printf("2=%s\n\n", tmp->cmd_param[2]);
// tmp = tmp->next;
// printf("3=%s\n", tmp->cmd_param[0]);
// printf("3=%s\n", tmp->cmd_param[1]);
// printf("3=%s\n", tmp->cmd_param[2]);

    // free_all_cmd_nodes(&data->cmd);



















//! difference entre compter les cmd et les sequences... 
//! ...donc plus trop utile
// int cmd_counter_ce_gros_bg_la()
// {
//     int i;
//     t_data* data;
//     t_token *tmp;

//     data = get_data();
//     tmp = data->token;
//     i = 0;
//     while (tmp)
//     {
//         if ((tmp->type >= 1 && tmp->type <= 4) && (!tmp->prev || tmp->prev->type == PIPE) && tmp->next && tmp->next->next && tmp->next->next->type == ARG)
//             if (check_command_in_path(tmp->next->next->value) == SUCCESS || is_builtin(tmp->next->next->value) == true)
//                 i++;
//         if (tmp->type == CMD)
//             i++;
//         tmp = tmp->next;
//     } 
//     return (i);
// }

//! difference entre compter les cmd et les sequences... doinc plus trop utile
// int cmd_counter_ce_gros_bg_la()
// {
//     int i;
//     t_data* data;
//     t_token *tmp;

//     data = get_data();
//     tmp = data->token;
//     i = 0;
//     while (tmp)
//     {
//         if ((tmp->type >= 1 && tmp->type <= 4) && (!tmp->prev || tmp->prev->type == PIPE) && tmp->next && tmp->next->next && tmp->next->next->type == ARG)
//             if (check_command_in_path(tmp->next->next->value) == SUCCESS || is_builtin(tmp->next->next->value) == true)
//                 i++;
//         if (tmp->type == CMD)
//             i++;
//         tmp = tmp->next;
//     } 
//     return (i);
// }

