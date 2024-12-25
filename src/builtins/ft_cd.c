/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:13:34 by febouana          #+#    #+#             */
/*   Updated: 2024/12/25 16:57:46 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//+ Recherche dans env la variable donnee en argument
//+ et retourne la valeur associee
char	*search_env_var(char *var)
{
	int		len;
	char	*value;
	t_env	*tmp;
	t_data	*data;

	if (!var)
		return (NULL);
	data = get_data();
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

bool	change_cd_env_var(char *symbole)
{
	char	*res;
	char	*path;

	if (ft_strcmp(symbole, "") == 0 || ft_strcmp(symbole, "~") == 0
		|| ft_strcmp(symbole, "--") == 0)
	{
		path = "HOME";
		res = search_env_var(path);
		if (!res)
			return (print_error("minishell: cd: "), print_error(path),
				print_error(" not set\n"), 1);
	}
	if (ft_strcmp(symbole, "-") == 0)
	{
		path = "OLDPWD";
		res = search_env_var(path);
		if (!res)
			return (print_error("minishell: cd: "), print_error(path),
				print_error(" not set\n"), 1);
		printf("%s\n", res);
	}
	chdir(res);
	free(res);
	return (SUCCESS);
}

int	change_cd(char *direction)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strcmp(direction, "") == 0 || ft_strcmp(direction, "~") == 0
		|| ft_strcmp(direction, "--") == 0 || ft_strcmp(direction, "-") == 0)
		exit_status = change_cd_env_var(direction);
	else if (chdir(direction) == -1)
	{
		print_error("minishell: cd: ");
		print_error(direction);
		print_error(": No such file or directory\n");
		return (1);
	}
	return (exit_status);
}

int	ft_cd(char **cmd_param)
{
	int		nbr_param;
	int		exit_status;
	char	pwd[PATH_MAX];
	char	oldpwd[PATH_MAX];

	exit_status = 0;
	nbr_param = ft_multi_array_len(cmd_param);
	if (nbr_param > 2)
		return (print_error("minishell: cd: too many arguments\n"), 1);
	if (!getcwd(oldpwd, PATH_MAX))
		return (print_error("Error: getcwd\n"), 1);
	if (nbr_param == 2)
		exit_status = change_cd(cmd_param[1]);
	else
		exit_status = change_cd("");
	if (!getcwd(pwd, PATH_MAX))
		return (print_error("Error: getcwd\n"), 1);
	if (remplace_if_already_exist("OLDPWD", oldpwd) == EXIT_MALLOC)
		return (EXIT_MALLOC);
	if (remplace_if_already_exist("PWD", pwd) == EXIT_MALLOC)
		return (EXIT_MALLOC);
	return (exit_status);
}
