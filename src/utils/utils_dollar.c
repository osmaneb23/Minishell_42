/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:25:22 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/03 15:10:28 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	main_handle_var(char *tmp, char *new_value, t_data *data)
{
	int		i;
	int		j;
	bool	in_single_quotes;

	i = 0;
	j = 0;
	in_single_quotes = false;
	while (tmp[i])
	{
		if (tmp[i] == '\'')
		{
			in_single_quotes = !in_single_quotes;
			new_value[j++] = tmp[i++];
		}
		else if (in_single_quotes || tmp[i] != '$' || !tmp[i + 1])
			new_value[j++] = tmp[i++];
		else if (tmp[i + 1] == '?')
			j = handle_exit_status(data, new_value, j, &i);
		else if (ft_isalnum(tmp[i + 1]) || tmp[i + 1] == '_')
			j = handle_var_names(&i, tmp, new_value, j);
		else
			new_value[j++] = tmp[i++];
	}
	new_value[j] = '\0';
}

int	handle_exit_status(t_data *data, char *new_value, int j, int *i)
{
	char	*exit_str;

	exit_str = ft_itoa(data->exit_status);
	if (!exit_str)
	{
		free(new_value);
		cleanup(ERROR, ERR_MALLOC, ERROR, 2);
	}
	j = str_append(new_value, exit_str, j);
	free(exit_str);
	*i += 2;
	return (j);
}

int	handle_var_names(int *i, char *tmp, char *new_value, int j)
{
	int		var_start;
	char	*var_name;
	char	*env_value;

	var_start = ++(*i);
	while (ft_isalnum(tmp[*i]) || tmp[*i] == '_')
		(*i)++;
	var_name = ft_substr(tmp, var_start, *i - var_start);
	if (!var_name)
	{
		free(new_value);
		cleanup(ERROR, ERR_MALLOC, ERROR, 2);
	}
	env_value = search_env_var(var_name);
	if (env_value)
		j = str_append(new_value, env_value, j);
	free(var_name);
	return (j);
}

int	str_append(char *dest, const char *src, int pos)
{
	int	i;

	i = 0;
	while (src[i])
		dest[pos++] = src[i++];
	return (pos);
}

size_t	ft_numlen(int n)
{
	size_t			len;
	unsigned int	num;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		num = -n;
	}
	else
		num = n;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}
