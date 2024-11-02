/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:27:50 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/02 19:14:42 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		return (cleanup(2, "exit: too many arguments\n", 1, 2));
	if (i == 1)
		exit(0);
	if (!ft_isdigit(args[1][0]))
		return (cleanup(2, "exit: numeric argument required\n", 255, 2));
	exit(ft_atoi(args[1]));
	return (SUCCESS);
}
