/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:25:24 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/04 17:40:35 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **cmd_params)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (!cmd_params[i])
	{
		printf("\n");
		return (SUCCESS);
	}
	while (cmd_params[i][0] == '-' && cmd_params[i][1] == 'n')
	{
		newline = false;
		i++;
	}
	while (cmd_params[i])
	{
		printf("%s", cmd_params[i]);
		if (cmd_params[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
