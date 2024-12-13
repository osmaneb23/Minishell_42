/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:27:41 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/11 17:24:33 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Clean the data of minishell:
- free the data
- set the exit status in the data
- print a message if needed
- exit if needed
- return the exit status
*/
// int    cleanup(int exit_status, char *message, int exit_call, int fd)
// {
//     t_data    *data;

//     data = get_data();
//     if (data)
//     {
//         free_data(&data);
//         if (exit_status != NO_CHANGE)
//             data->exit_status = exit_status;
//     }
//     if (message)
//         ft_putstr_fd(message, fd);
//     if (exit_call != NO_EXIT)
//     {
//         if (data->envp)
//             destroy_envp_list(&data->envp); //+ DETRUIT ENV
//         free(data->line);
//         rl_clear_history();
//         exit(exit_call);
//     }
//     return (data->exit_status);
// }

int	cleanup(int exit_status, char *message, int exit_call, int fd)
{
	t_data	*data;

	data = get_data();
	if (data)
	{
		free_data(&data);
		if (exit_status != NO_CHANGE)
			data->exit_status = exit_status;
	}
	if (message)
		ft_putstr_fd(message, fd);
	if (exit_call != NO_EXIT)
	{
		if (data)
		{
			if (data->envp)
				destroy_envp_list(&data->envp);
			if (data->line)
				free(data->line);
		}
		rl_clear_history();
		exit(exit_call);
	}
	return (exit_status);
}

// Free the data of minishell
void	free_data(t_data **data)
{
	if (!data || !(*data))
		return ;
	if ((*data)->token)
		free_tokens(data);
	if ((*data)->cmd)
		free_commands(data);
}

// Free the tokens in the list
void	free_tokens(t_data **data)
{
	t_token	*current;
	t_token	*next;

	if (!data || !(*data) || !(*data)->token)
		return ;
	current = (*data)->token;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = NULL;
		current = next;
	}
	if ((*data)->token)
		(*data)->token = NULL;
}

void	free_commands(t_data **data)
{
	t_cmd	*current;
	t_cmd	*next;
	int		i;

	if (!data || !*data || !(*data)->cmd)
		return ;
	current = (*data)->cmd;
	while (current)
	{
		next = current->next;
		if (current->cmd_param)
		{
			i = 0;
			if (current->cmd_param[i])
				free(current->cmd_param[i]);
			while (current->cmd_param[i] && ++i)
				free(current->cmd_param[i]);
			free(current->cmd_param);
			current->cmd_param = NULL;
		}
		free(current);
		current = NULL;
		current = next;
	}
	(*data)->cmd = NULL;
}
