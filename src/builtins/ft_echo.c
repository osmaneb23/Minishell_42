/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 18:25:24 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/21 04:27:09 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_n_flag(char **cmd_param, int *i)
{
	int		j;
	bool	newline;

	newline = true;
	while (cmd_param[*i] && ft_strncmp(cmd_param[*i], "-n", 2) == 0)
	{
		j = 1;
		while (cmd_param[*i][j] == 'n')
			j++;
		if (!cmd_param[*i][j])
		{
			newline = false;
			(*i)++;
		}
		else
			break ;
	}
	return (newline);
}

int	ft_echo(char **cmd_param)
{
	int		i;
	bool	newline;

	i = 1;
	if (!cmd_param[i])
	{
		printf("\n");
		return (SUCCESS);
	}
	newline = check_n_flag(cmd_param, &i);
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
