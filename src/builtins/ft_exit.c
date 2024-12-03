/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:27:50 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/03 18:00:24 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Max size etc etc

int	ft_exit(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
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
	return (cleanup(ft_atoi(args[1]), "exit", ft_atoi(args[1]), 1));
}
