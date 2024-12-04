/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:07:10 by febouana          #+#    #+#             */
/*   Updated: 2024/12/04 17:07:28 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ft_free_var_and_val(char **var, char **val)
{
    free(var);
    free(val);
}

int search_egal_symbol(char *cmd_param)
{
    int i;

    i = 0;
    while (cmd_param[i])
    {
        if (cmd_param[i] == '=')
            return (i);
        i++;
    }
    return (-1);
}

char *return_var(char *var_and_val, int limit)
{
    char *var;
    int start;

    start = 0;
    var = (char *)malloc(sizeof(char) * (limit + 1));
    if (!var)
        return (NULL);
    while (start < limit)
    {
        var[start] = var_and_val[start];
        start++;
    }
    var[start] = '\0';
    return(var);
}

char *return_val(char *var_and_val, int start)
{
    char *val;
    int limit;
    int i;

    i = 0;
    limit = ft_strlen(var_and_val);
    val = (char *)malloc(sizeof(char) * (limit - start));
    if (!val)
        return(NULL);
    start++;
    while (start < limit)
    {
        val[i] = var_and_val[start];
        start++;
        i++;
    }
    val[i] = '\0';
    return(val);
}
