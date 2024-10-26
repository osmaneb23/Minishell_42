/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 02:27:41 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/26 18:17:13 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_data(t_data **data)
{
	t_token	*tmp;
	t_token	*next;

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
	}
}

bool	cleanup(bool error, char *message, int ext)
{
	t_data *data;

	data = get_data();
	if (data)
		free_data(&data);
	if (message)
		ft_putstr_fd(message, 2);
	if (ext != NO_EXIT)
		exit(ext);
	return (error);
}