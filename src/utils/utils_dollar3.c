/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:54:51 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/19 23:56:08 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_bool_quotes(char *tmp, int i, bool *in_single_quotes,
		bool *in_double_quotes)
{
	if (tmp[i] == '\'')
		*in_single_quotes = !(*in_single_quotes);
	else
		*in_double_quotes = !(*in_double_quotes);
}

void	handle_dollar(char *tmp, char *new_value, int *i, int *j)
{
	t_data	*data;

	data = get_data();
	if (tmp[*i + 1] == '?')
		*j = handle_exit_status(data, new_value, *j, i);
	else if (ft_isalnum(tmp[*i + 1]) || tmp[*i + 1] == '_')
		*j = handle_var_names(i, tmp, new_value, *j);
	else
		new_value[(*j)++] = tmp[(*i)++];
}

void	main_handle_var(char *tmp, char *new_value)
{
	int		i;
	int		j;
	bool	in_single_quotes;
	bool	in_double_quotes;

	i = 0;
	j = 0;
	in_single_quotes = false;
	in_double_quotes = false;
	while (tmp[i])
	{
		if ((tmp[i] == '\'' && !in_double_quotes) || (tmp[i] == '"'
				&& !in_single_quotes))
		{
			change_bool_quotes(tmp, i, &in_single_quotes, &in_double_quotes);
			new_value[j++] = tmp[i++];
		}
		else if (tmp[i] == '$' && !in_single_quotes && tmp[i + 1])
			handle_dollar(tmp, new_value, &i, &j);
		else
			new_value[j++] = tmp[i++];
	}
	new_value[j] = '\0';
}
