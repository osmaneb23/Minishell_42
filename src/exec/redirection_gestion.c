/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_gestion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:34:17 by febouana          #+#    #+#             */
/*   Updated: 2024/12/12 22:03:58 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*OKOK
//? Initialise un fichier pour une redirection donnée
//? parmi <, > et >> 
int init_file(t_cmd *cmd, char *filename, int type)
{
    if (!cmd || !filename)
        return (ERROR);
    if ((type == INPUT || type == HEREDOC) && cmd->infile > -2)
        close(cmd->infile);
    if ((type == TRUNC || type == APPEND) && cmd->outfile > -2)
        close(cmd->outfile);
    if (type == INPUT)
        cmd->infile = open(filename, O_RDONLY);
    if (type == TRUNC)
        cmd->outfile = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (type == APPEND)
        cmd->outfile = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (cmd->infile == -1 || cmd->outfile == -1)
    {
        perror("Error: File operation failed");
        return (ERROR);
    }
    return (SUCCESS);
}

//*OKOK
//? Initialise ou remplace la redirection d'entree ou de sortie
int fill_cmd_nodes_redirections(t_cmd *cmd, t_token *token)
{
    if (token->next->type == ARG && token->type == HEREDOC)
    {
        if (heredoc(cmd, token->next->value) != SUCCESS)
            return (ERROR);
        if (token->next->next) //MON PRECIEUX
            token = token->next->next;
        if ((!token->prev || token->prev->type == PIPE) && token->type == ARG && (check_command_in_path(token->value) == SUCCESS || is_builtin(token->value) == true))
            token->type = CMD;  
        printf("\n"); // a supp ? pour rendre lisible plusieurs heredoc
    }
    else if (access(token->next->value, F_OK) == 0)
    {
        if (init_file(cmd, token->next->value, token->type) != SUCCESS)
            return (ERROR);
        if (token->next->next) //MON PRECIEUX
            token = token->next->next;
        if ((!token->prev || token->prev->type == PIPE) && token->type == ARG && (check_command_in_path(token->value) == SUCCESS || is_builtin(token->value) == true))
            token->type = CMD;
    }
    return (SUCCESS);
}

int	close_all_redi(t_data *data)
{
    t_cmd   *cmd;

    cmd = data->cmd;
    while (cmd)
    {
        if (data->pip[1] >= 0) 
            close(data->pip[1]);
        if (data->pip[0] >= 0) 
            close(data->pip[0]);
        if (cmd->outfile >= 0) 
            close(cmd->outfile);
        if (cmd->infile >= 0) 
            close(cmd->infile);
        cmd = cmd->next;
    }
    return (SUCCESS);
}

void close_all_redi_of_each_nodes(t_data *data)
{
    t_cmd *cmd;

    if (!data)
        return ;
    if (data->pip[0] >= 0) 
        close(data->pip[0]);
    if (data->pip[1] >= 0) 
        close(data->pip[1] );
    cmd = data->cmd;
    while (cmd)
    {
        if (cmd->cmd_param)
            ft_free_multi_array(cmd->cmd_param);
        if (cmd->outfile >= 0) 
            close(cmd->outfile);
        if (cmd->infile >= 0) 
            close(cmd->infile);
        cmd->f_pid = 0;
        cmd = cmd->next;
    }
    cmd = NULL;
    // printf("WATI-FREE-SUCCESS\n\n");
    // free les nodes (+ prev next) une par une en + ou deja fait ?
}

