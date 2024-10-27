/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:55:40 by obouayed          #+#    #+#             */
/*   Updated: 2024/10/27 02:59:33 by obouayed         ###   ########.fr       */
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
