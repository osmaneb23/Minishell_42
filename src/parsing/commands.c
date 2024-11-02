/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:43:47 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/02 19:14:21 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_cmd(t_data *data)
{
	t_token	*token;
	t_cmd	*cmd;

	token = data->token;
	while (token)
	{
		if (token->type == CMD)
		{
			cmd = malloc(sizeof(t_cmd));
			if (!cmd)
				cleanup(ERROR, "Error: malloc failed\n", ERROR, 2);
			cmd->cmd_param = init_cmd_param(token);
			cmd->infile = -1;
			cmd->outfile = -1;
			cmd->next = NULL;
			cmd->prev = NULL;
			if (!data->cmd)
				data->cmd = cmd;
			else
				add_cmd_to_list(cmd, data->cmd);
		}
		token = token->next;
	}
}

char	**init_cmd_param(t_token *token)
{
	t_token			*tmp;
	char			**cmd_param;
	unsigned int	i;

	tmp = token;
	i = 0;
	while (tmp && tmp->type >= CMD && ++i)
		tmp = tmp->next;
	cmd_param = malloc(sizeof(char *) * (i + 1));
	if (!cmd_param)
		cleanup(ERROR, "Error: malloc failed\n", ERROR, 2);
	cmd_param[i] = NULL;
	i = 0;
	tmp = token;
	while (tmp && tmp->type >= CMD)
	{
		cmd_param[i] = ft_strdup(tmp->value);
		if (!cmd_param[i])
			cleanup(ERROR, "Error: malloc failed\n", ERROR, 2);
		i++;
		tmp = tmp->next;
	}
	return (cmd_param);
}

bool	add_cmd_to_list(t_cmd *cmd, t_cmd *data_cmd)
{
	t_cmd	*last;

	last = last_command(data_cmd);
	if (!last)
		return (cleanup(ERROR, "Error: impossible to get last command\n", ERROR,
				2));
	last->next = cmd;
	cmd->prev = last;
	return (SUCCESS);
}
