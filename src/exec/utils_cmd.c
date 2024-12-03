/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:31:14 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/02 18:45:15 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Get the last command in the list
t_cmd	*last_command(t_cmd *command)
{
	if (!command)
		return (NULL);
	while (command->next)
		command = command->next;
	return (command);
}
