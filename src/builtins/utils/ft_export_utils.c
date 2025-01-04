/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:07:10 by febouana          #+#    #+#             */
/*   Updated: 2025/01/04 18:01:10 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	search_egal_symbol(char *cmd_param)
{
	int	i;

	i = 0;
	while (cmd_param[i])
	{
		if (cmd_param[i] == '=')
			return (i);
		i++;
	}
	return (FAILURE);
}

char	*return_var(char *var_and_val, int limit)
{
	char	*var;
	int		start;

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
	return (var);
}

char	*return_val(char *var_and_val, int start)
{
	char	*val;
	int		limit;
	int		i;

	i = 0;
	limit = ft_strlen(var_and_val);
	val = (char *)malloc(sizeof(char) * (limit - start));
	if (!val)
		return (NULL);
	start++;
	while (start < limit)
	{
		val[i] = var_and_val[start];
		start++;
		i++;
	}
	val[i] = '\0';
	return (val);
}

bool	export_not_valid(char *var_and_val, char *var)
{
	if (!ft_strcmp(var, "") || verif_var_char(var))
	{
		return (print_error("minishell: export: `"), print_error(var_and_val),
			print_error("': not a valid identifier\n"), 1);
	}
	return (SUCCESS);
}

bool	export_init_vars(char **var_and_val, char **var, char **val, int i)
{
	*var = return_var((*var_and_val), i);
	*val = return_val((*var_and_val), i);
	if (!var || !val)
		return (EXIT_MALLOC);
	return (SUCCESS);
}
