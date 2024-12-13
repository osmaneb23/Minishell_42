/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:05:19 by febouana          #+#    #+#             */
/*   Updated: 2024/12/11 22:41:09 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// exit status OKOK
//+ with no options and arguments (exit status can only be 0)
int ft_env(void)
{
    t_data *data = get_data();
    t_env *tmp;

    tmp = data->envp;
    if (!tmp)
        return (SUCCESS);
    while(tmp)
    {
        if (ft_strchr(tmp->line, '='))
            printf("%s\n", tmp->line);
        if (tmp->next == NULL)
            break ;
        tmp = tmp->next;
    }
    return (SUCCESS);
}
