/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/02 22:55:54 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*search_env_var(char *var)
{
	int		len;
	char	*value;
	t_env	*tmp;
	t_data	*data;

	if (!var)
		return (NULL);
	data = get_data();
	if (!data || !data->envp)
		return (NULL);
	len = ft_strlen(var);
	tmp = data->envp;
	while (tmp != NULL)
	{
		if (ft_strncmp(var, tmp->line, len) == 0 && tmp->line[len] == '=')
		{
			value = malloc(ft_strlen(tmp->line + len + 1) + 1);
			if (!value)
				return (NULL);
			ft_strcpy(value, tmp->line + len + 1);
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
void replace_value_with_variable(t_data *data)
{
	char    *value;
	char    *tmp;
	char *tmp2;
	t_token *token;

	token = data->token;
	while (token)
	{
		if ((token->value[0] == '$') || (token->value[0] == '"' && token->value[1] == '$'))
		{
			if (token->value[0] == '"')
				remove_quotes(data);
			tmp2 = token->value;
			token->value = ft_substr(token->value, 1, ft_strlen(token->value) - 1);
			free(tmp2);
			value = search_env_var(token->value);
			printf("value: %s\n", value);
			if (value)
			{
				tmp = token->value;
				token->value = value;
				free(tmp);
			}
		}
		token = token->next;
	}
}

bool	main_routine(t_data *data)
{
	if (!check_openquote(data->line))
	{
		tokenization(data->line);
		replace_value_with_variable(data);
		remove_quotes(data);
		init_cmd(data);
		printf_tokens(data);
		if (!check_misplacements(data))
		{
			if (!check_valid_commands(data))
				cleanup(SUCCESS, NULL, NO_EXIT, 0);
		}
	}
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	initialize_data(&data, env);
	setup_signals();
	while (1)
	{
		data->line = readline("minishell$ ");
		if (data->line == NULL)
		{
			rl_clear_history();
			return (cleanup(SUCCESS, "exit\n", NO_EXIT, 2));
		}
		main_routine(data);
		add_history(data->line);
	}
	rl_clear_history();
	return (cleanup(SUCCESS, NULL, NO_EXIT, 0));
}
