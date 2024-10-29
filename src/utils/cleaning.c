/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:27:41 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/29 20:38:27 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		current = next;
	}
	if ((*data)->token)
		(*data)->token = NULL;
}

void	free_data(t_data **data)
{
	if (!data || !(*data))
		return ;
	free_tokens(data);
}

int	cleanup(int exit_status, char *message, int exit_call, int fd)
{
	t_data	*data;

	data = get_data();
	free_data(&data);
	data->exit_status = exit_status;
	if (message)
		ft_putstr_fd(message, fd);
	if (exit_call != NO_EXIT)
		exit(exit_call);
	return (exit_status);
}
