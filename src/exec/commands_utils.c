/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:20:17 by febouana          #+#    #+#             */
/*   Updated: 2024/12/23 20:29:57 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_access_redirections(t_data *data)
{
	t_token	*token;

	token = data->token;
	while (token)
	{
		if (token->type == INPUT)
		{
			if (token->next && token->next->type == ARG)
			{
				if (access(token->next->value, F_OK) != 0)
					return (print_error("minishell: "),
						print_error(token->next->value), cleanup(1,
							": No such file or directory\n", NO_EXIT, 2),
						ERROR);
			}
		}
		token = token->next;
	}
	return (SUCCESS);
}

//*OKOK
//? Compte les paramètres de commande
int	count_cmd_param(t_token *token)
{
	int	i;

	i = 0;
	while (token && token->type != PIPE)
	{
		if (token->type >= 1 && token->type <= 4)
		{
			if (token->next && token->next->type == ARG)
				i--;
		}
		else
			i++;
		token = token->next;
	}
	return (i);
}

int	count_nb_sequences(t_token *token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (strcmp(tmp->value, "|") == 0 && tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	if (i == 0)
		return (1);
	return (i + 1);
}

//*OKOK
//? Libère une liste chaînée de commandes
// void	free_all_cmd_nodes(t_cmd **cmd_list)
// {
// 	t_cmd	*current;
// 	t_cmd	*next;

// 	if (!cmd_list || !(*cmd_list))
// 		return ;
// 	current = *cmd_list;
// 	while (current)
// 	{
// 		next = current->next;
// 		ft_free_multi_array(current->cmd_param);
// 		free(current);
// 		current = next;
// 	}
// 	*cmd_list = NULL;
// }
