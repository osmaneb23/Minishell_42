/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2025/01/04 19:11:20 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//?OKOK
void	init_env(t_data *data, char **env)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	data->envp = NULL;
	if (!(*env))
	{
		init_env_i(data);
		return ;
	}
	while (env[i])
	{
		line = ft_strdup(env[i]);
		append_node_envp(&data->envp, line);
		i++;
	}
}

void	replace_var_val(t_data *data)
{
	t_token	*token;
	size_t	len;
	char	*new_value;

	token = data->token;
	while (token)
	{
		if (!token->prev || token->prev->type != HEREDOC)
		{
			len = estimate_new_length(token->value);
			new_value = malloc(sizeof(char) * (len + 2));
			if (!new_value)
				cleanup(ERROR, ERR_MALLOC, ERROR, 2);
			main_handle_var(token->value, new_value);
			free(token->value);
			token->value = new_value;
		}
		token = token->next;
	}
}

bool	main_routine(t_data *data, char **envp)
{
	(void)envp;
	if (!check_openquote(data->line))
	{
		tokenization(data->line);
		if (ft_strlen(data->token->value) == 0)
			return (cleanup(SUCCESS, NULL, NO_EXIT, 0));
		replace_var_val(data);
		remove_quotes(data);
		remove_backslash(data);
		printf_tokens(data);
		if (!check_misplacements(data))
		{
			if (!check_valid_commands(data))
			{
				if (!init_cmd(data))
				{
					if (!exec(data, data->cmd, data->pip))
						cleanup(SUCCESS, NULL, NO_EXIT, 0);
				}
			}
		}
	}
	return (SUCCESS);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)ac;
	(void)av;
	initialize_data(&data);
	setup_signals();
	init_env(data, envp);
	printf(WHITE);
	while (1)
	{
		data->line = readline("minishell> ");
		if (data->line == NULL)
			return (cleanup(NO_CHANGE, "exit\n", data->exit_status, 1));
		if (ft_strlen(data->line) == 0)
			continue ;
		main_routine(data, envp);
		add_history(data->line);
		free(data->line);
		data->line = NULL;
	}
	rl_clear_history();
	printf(DEFAULT);
	return (cleanup(SUCCESS, NULL, SUCCESS, 0));
}
