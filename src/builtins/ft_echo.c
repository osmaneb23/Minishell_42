/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:25:24 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/10 20:34:02 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//+ EXIT STATUS OKOK
int	ft_echo(char **cmd_param)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	if (!cmd_param[i])
	{
		printf("\n");
		return (SUCCESS);
	}
	while (cmd_param[i][0] == '-' && cmd_param[i][1] == 'n')
	{
		newline = false;
		i++;
	}
	while (cmd_param[i])
	{
		printf("%s", cmd_param[i]);
		if (cmd_param[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (SUCCESS);
}
