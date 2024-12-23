/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 23:54:51 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/23 20:30:24 by obouayed         ###   ########.fr       */
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

void	process_dollar(char *tmp, char *new_value, t_parser *state)
{
	if ((tmp[state->i] == '\'' && !(state->in_double_quotes))
		|| (tmp[state->i] == '"' && !(state->in_single_quotes)))
	{
		change_bool_quotes(tmp, state->i, &state->in_single_quotes,
			&state->in_double_quotes);
		new_value[state->j++] = tmp[state->i++];
	}
	else if (tmp[state->i] == '$' && !(state->in_single_quotes) && tmp[state->i
			+ 1])
		handle_dollar(tmp, new_value, &state->i, &state->j);
	else
		new_value[state->j++] = tmp[state->i++];
}

void	main_handle_var(char *tmp, char *new_value)
{
	t_parser	state;

	state.i = 0;
	state.j = 0;
	state.in_single_quotes = false;
	state.in_double_quotes = false;
	while (tmp[state.i])
	{
		if ((tmp[state.i] == '\\' && tmp[state.i + 1] == '$')
			|| (tmp[state.i] == '\\' && tmp[state.i + 1] == '$'))
		{
			new_value[state.j++] = tmp[state.i++];
			new_value[state.j++] = tmp[state.i++];
			continue ;
		}
		process_dollar(tmp, new_value, &state);
	}
	new_value[state.j] = '\0';
}
