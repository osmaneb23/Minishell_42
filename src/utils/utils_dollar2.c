/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:44:42 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/03 15:16:49 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	estimate_new_length(const char *value, t_data *data)
{
	size_t	len;
	int		i;
	bool	in_single_quotes;

	len = 0;
	i = 0;
	in_single_quotes = false;
	while (value[i])
	{
		if (value[i] == '\'')
		{
			in_single_quotes = !in_single_quotes;
			i++;
			len++;
		}
		else if (!in_single_quotes && value[i] == '$' && value[i + 1])
			len += handle_dollar_sign(value, &i, data);
		else
		{
			len++;
			i++;
		}
	}
	return (len + 1);
}

size_t	handle_dollar_sign(const char *value, int *i, t_data *data)
{
	size_t	len;
	int		var_len;

	len = 0;
	(*i)++;
	if (value[*i] == '?')
	{
		len = get_exit_status_length(data->exit_status);
		(*i)++;
	}
	else if (ft_isalnum(value[*i]) || value[*i] == '_')
	{
		var_len = skip_variable_name(&value[*i]);
		len = get_env_var_length(&value[*i], var_len);
		(*i) += var_len;
	}
	else
		len++;
	return (len);
}

size_t	get_exit_status_length(int status)
{
	size_t	len;
	int		num;

	len = 0;
	if (status == 0)
		return (1);
	num = status;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}

size_t	skip_variable_name(const char *str)
{
	size_t	len;

	len = 0;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

size_t	get_env_var_length(const char *start, int len)
{
	char	*var_name;
	size_t	value_len;
	char	*env_value;

	var_name = ft_substr(start, 0, len);
	value_len = 0;
	if (!var_name)
		cleanup(ERROR, ERR_MALLOC, ERROR, 2);
	env_value = search_env_var(var_name);
	if (env_value)
	{
		value_len = ft_strlen(env_value);
		free(env_value);
	}
	free(var_name);
	return (value_len);
}
