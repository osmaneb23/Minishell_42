/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_gestion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:34:17 by febouana          #+#    #+#             */
/*   Updated: 2024/12/17 18:14:03 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*OKOK
//? Initialise un fichier pour une redirection donnée
//? parmi <, > et >>
int	init_file(t_cmd *cmd, char *filename, int type)
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

bool is_valid_cmd(char *cmd)
{
	if (check_command_in_path(cmd) == SUCCESS || is_builtin(cmd) == true || access(cmd, X_OK) == 0)
		return (true);
	return (false);
}

int	fill_cmd_nodes_redirections(t_cmd *cmd, t_token **real_token)
{
	bool is_pipe;
	
	is_pipe = false;
	while ((*real_token)->type >= 1 && (*real_token)->type <= 4)
	{
		if ((*real_token)->type == HEREDOC)
			if (heredoc(cmd, (*real_token)->next->value) != SUCCESS)
				return (ERROR);
		if ((*real_token)->type == INPUT || (*real_token)->type == TRUNC || (*real_token)->type >= APPEND)
			if (init_file(cmd, (*real_token)->next->value, (*real_token)->type) != SUCCESS)
				return (ERROR);
		if ((*real_token)->prev && (*real_token)->prev->type == PIPE)
			is_pipe = true;
		if ((*real_token)->next->next) // MON PRECIEUX
		{
			(*real_token) = (*real_token)->next->next;
			if ((!cmd->prev || is_pipe == true) && (*real_token)->type == ARG && is_valid_cmd((*real_token)->value) == true)
				(*real_token)->type = CMD; 
		}
		else
			return (SUCCESS);
	}
	return (SUCCESS);
}

int	close_all_redi(t_data *data)
{
	t_cmd	*cmd;

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

void	close_all_redi_of_each_nodes(t_data *data)
{
	t_cmd	*cmd;

	if (!data)
		return ;
	if (data->pip[0] >= 0)
		close(data->pip[0]);
	if (data->pip[1] >= 0)
		close(data->pip[1]);
	cmd = data->cmd;
	while (cmd)
	{
		if (cmd->cmd_param)
			ft_free_multi_array(cmd->cmd_param);
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		if (cmd->infile >= 0)
			close(cmd->infile);
		cmd = cmd->next;
	}
	cmd = NULL;
}

void close_null_sq()
{
    t_data * data;
    t_cmd *tmp;
    
    data = get_data();
    tmp = data->cmd;
    while (tmp)
    {
        if (!tmp->cmd_param)
        {  
            if (tmp->infile > -2)
            {
                close(tmp->infile);
                tmp->infile = -2;
            }
            if (tmp->outfile > -2)
            {
                close(tmp->outfile);
                tmp->outfile = -2;
            }
            tmp->skip_cmd = true;
        }
        tmp = tmp->next;
    }
}
