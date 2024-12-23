/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:37:45 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/23 22:38:08 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_escaped_chars(const char *value, int *i, size_t *len)
{
	if (value[*i] == '\\' && value[*i + 1])
	{
		*len += 2;
		*i += 2;
	}
	else
	{
		(*len)++;
		(*i)++;
	}
}
