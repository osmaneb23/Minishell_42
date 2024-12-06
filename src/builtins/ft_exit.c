/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:27:50 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/06 16:18:57 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char **cmd_param)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_param[i])
	{
		j = 0;
		while (cmd_param[i][j])
		{
			if (!ft_isdigit(cmd_param[i][j]))
				return (cleanup(255, "exit: numeric argument required\n", 255,
						2));
			j++;
		}
		i++;
	}
	if (i > 2)
		return (cleanup(1, "exit: too many arguments\n", NO_EXIT, 2));
	if (i == 1)
		return (cleanup(0, "exit", 0, 1));
	return (cleanup(ft_atoi(cmd_param[1]), "exit", ft_atoi(cmd_param[1]), 1));
}
