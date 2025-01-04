/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_gestion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:34:17 by febouana          #+#    #+#             */
/*   Updated: 2025/01/04 18:00:10 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//*OKOK
//? Initialise un fichier pour une redirection donnée
//? parmi <, > et >>
int	init_file(t_cmd *cmd, char *filename, int type)
{
	t_data	*data;

	data = get_data();
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
		print_error("Error: File operation failed\n");
		data->exit_status = 1;
		return (ERROR);
	}
	return (SUCCESS);
}

int	fill_cmd_nodes_redirections(t_cmd *cmd, t_token **real_token)
{
	while ((*real_token)->type >= 1 && (*real_token)->type <= 4)
	{
		if ((*real_token)->type == HEREDOC)
			if (heredoc(cmd, (*real_token)->next->value) != SUCCESS)
				return (ERROR);
		if ((*real_token)->type == INPUT || (*real_token)->type == TRUNC
			|| (*real_token)->type >= APPEND)
			if (init_file(cmd, (*real_token)->next->value,
					(*real_token)->type) != SUCCESS)
				return (ERROR);
		if ((*real_token)->next->next)
		{
			(*real_token) = (*real_token)->next->next;
			if ((!cmd->prev || ((*real_token)->prev
						&& (*real_token)->prev->type == PIPE))
				&& (*real_token)->type == ARG
				&& is_valid_cmd((*real_token)->value) == true)
				(*real_token)->type = CMD;
		}
		else
			return (SUCCESS);
	}
	return (SUCCESS);
}

void	redirect_input_output(t_cmd *cmd, int *pip)
{
	close(pip[0]);
	if (cmd->prev && cmd->prev->outfile >= 0)
		close(cmd->prev->outfile);
	if (cmd->infile >= 0)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
	else if (cmd->next != NULL)
		dup2(pip[1], STDOUT_FILENO);
	close(pip[1]);
}

int	close_all_redi(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (cmd)
	{
		if (data->pip[1] > 2)
			close(data->pip[1]);
		if (data->pip[0] > 2)
			close(data->pip[0]);
		if (cmd->outfile >= 0)
			close(cmd->outfile);
		if (cmd->infile >= 0)
			close(cmd->infile);
		cmd = cmd->next;
	}
	return (SUCCESS);
}

void	close_null_sq(void)
{
	t_data	*data;
	t_cmd	*tmp;

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
