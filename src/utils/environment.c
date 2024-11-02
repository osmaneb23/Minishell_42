/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 23:43:02 by obouayed          #+#    #+#             */
/*   Updated: 2024/11/02 23:44:41 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_environment(t_data *data, char **env)
{
	unsigned int	i;

	i = 0;
	data->envp = NULL;
	if (!(*env))
		create_environment(data);
	else
	{
		while (env[i])
		{
			append_node_envp(&data->envp, env[i]);
			i++;
		}
	}
}

bool	create_environment(t_data *data)
{
	char	path[PATH_MAX];
	char	*tmp;

	tmp = ft_strdup("OLDPWD");
	if (!tmp || append_node_envp(&data->envp, tmp) == ERROR || getcwd(path,
			PATH_MAX) == NULL)
		return (ERROR);
	tmp = ft_strjoin("PWD=", path);
	if (!tmp || append_node_envp(&data->envp, tmp) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

bool	append_node_envp(t_env **envp, char *line)
{
	t_env	*new_node;
	t_env	*last_node;

	if (!envp)
		return (ERROR);
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (ERROR);
	new_node->next = NULL;
	new_node->line = line;
	if (*envp == NULL)
	{
		new_node->prev = NULL;
		*envp = new_node;
	}
	else
	{
		last_node = find_last_node(*envp);
		last_node->next = new_node;
		new_node->prev = last_node;
	}
	return (SUCCESS);
}

t_env	*find_last_node(t_env *node)
{
	if (node == NULL)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

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
