/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:05:19 by febouana          #+#    #+#             */
/*   Updated: 2024/12/04 17:16:48 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//! with no options
int ft_env(void)
{
    t_data *data = get_data();
    t_env *tmp;

    if (!data || !data->envp)
        return (ERROR);
    tmp = data->envp;
    while(tmp != NULL)
    {
        if (ft_strchr(tmp->line, '='))
            printf("%s\n", tmp->line);
        tmp = tmp->next;
    }
    return (SUCCESS);
}
