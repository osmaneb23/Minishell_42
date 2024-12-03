/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:57:23 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/03 17:51:57 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_var_val(t_data *data)
{
	t_token	*token;
	size_t	len;
	char	*new_value;

	token = data->token;
	while (token)
	{
		len = estimate_new_length(token->value, data);
		new_value = malloc(sizeof(char) * len);
		if (!new_value)
			cleanup(ERROR, ERR_MALLOC, ERROR, 2);
		main_handle_var(token->value, new_value, data);
		free(token->value);
		token->value = new_value;
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
		printf_tokens(data);
		printf("\n");
		if (!check_misplacements(data))
		{
			if (!check_valid_commands(data))
			{
				if (!exec(data))
					cleanup(SUCCESS, NULL, NO_EXIT, 0);
			}
		}
		
	}
	return (SUCCESS);
}

#define WHITE "\033[0;37m"
#define BWHITE "\033[1;37m"
#define DEFAULT "\033[0m"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)ac;
	(void)av;
	initialize_data(&data);
	setup_signals();
	make_env(data, envp);
	printf(WHITE); // Active la couleur blanche pour le reste
	while (1)
	{
		// Prompt avec fond noir et texte en blanc
		// data->line = readline("\001" BWHITE "\002" "minishell> " WHITE);
		data->line = readline("minishell> ");
		if (data->line == NULL)
		{
			rl_clear_history();
			return (cleanup(SUCCESS, "exit\n", NO_EXIT, 1));
		}
		if (ft_strlen(data->line) == 0)
			continue ;
		main_routine(data, envp);
		add_history(data->line);
		free(data->line); // ??
	}
	rl_clear_history();
	printf(DEFAULT); // Réinitialise les couleurs
	return (cleanup(SUCCESS, NULL, NO_EXIT, 0));
}

