/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:27:41 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/24 21:52:41 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_data(t_data **data)
{
	t_token *tmp;
	t_token *next;

	if (data && *data)
	{
		if ((*data)->token)
		{
			tmp = (*data)->token;
			while (tmp)
			{
				next = tmp->next;
				free(tmp->value);
				free(tmp);
				tmp = next;
			}
		}
		free((*data)->username);
		free(*data);
	}
}

bool cleanup(t_data **data, bool error, char* message)
{
	if (data && *data)
		free_data(data);
	if (error)
	{
		ft_putstr_fd(message, 2);
		free_data(data);
		return (ERROR);
	}
	free_data(data);
	return (SUCCESS); // exit?
}