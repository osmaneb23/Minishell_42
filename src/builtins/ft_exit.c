/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:27:50 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/21 16:33:58 by apoet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
        printf("ARG==%s\n\n", args[i]);
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
		return (cleanup(0, "exit\n", 0, 1));
	return (cleanup(ft_atoi(args[1]), "exit", ft_atoi(args[1]), 1));
}
