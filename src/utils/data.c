/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:55:40 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/27 04:21:07 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	initialize_data(t_data **data, char **env)
{	
	(void)env;
	*data = get_data();
	(*data)->token = NULL;
	(*data)->line = NULL;
	(*data)->username = getenv("USER");
	(*data)->exit_status = 0;
}
