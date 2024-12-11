/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:13:34 by febouana          #+#    #+#             */
/*   Updated: 2024/12/11 14:29:58 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//? OKOK
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
				cleanup(ERROR, ERR_MALLOC, ERROR, 2); //! oui?
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
	}
	if (ft_strcmp(symbole, "-") == 0)
	{
		path = "OLDPWD";
		res = search_env_var(path);
		if (!res)
		{
			print_error("minishell: cd: ");
			print_error(path);
			return (cleanup(1, " not set\n", NO_EXIT, 2));
		}
		printf("%s\n", res);
	}
	chdir(res);
	free(res);
	return (SUCCESS);
}

//? OKOK
int	change_cd(char *direction)
{
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];

	getcwd(oldpwd, PATH_MAX);
	if (ft_strcmp(direction, "") == 0 || ft_strcmp(direction, "~") == 0
		|| ft_strcmp(direction, "--") == 0 || ft_strcmp(direction, "-") == 0)
		change_cd_env_var(direction);
	else if (chdir(direction) == -1)
	{
		print_error("minishell: cd: ");
		print_error(direction);
		return (cleanup(1, ": No such file or directory\n", NO_EXIT, 2));
	}
	remplace_if_already_exist("OLDPWD", oldpwd);
	getcwd(pwd, PATH_MAX);
	remplace_if_already_exist("PWD", pwd);
	return (SUCCESS);
}

//! EXIT STATUS KO
int	ft_cd(char **cmd_param)
{
	t_data* data;
	int	nbr_param;

	data = get_data();
	nbr_param = ft_multi_array_len(cmd_param);
	if (nbr_param > 2)
		return (data->exit_status = 1, print_error("cd: too many arguments\n"));
		// return (cleanup(1, "cd: too many arguments\n", NO_EXIT, 2));
	if (nbr_param == 2)
		return (change_cd(cmd_param[1]));
	if (nbr_param == 1)
		return (change_cd(""));
	return (SUCCESS);
}

//? "=XXXXXXX" OKOK