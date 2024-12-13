/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apoet <apoet@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:13:34 by febouana          #+#    #+#             */
/*   Updated: 2024/12/12 15:22:42 by apoet            ###   ########.fr       */
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
		if (!res)
			return (print_error("minishell: cd: "), print_error(path),
				print_error(" not set\n"), 1); // OKOK?
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

//? OKOK
int	change_cd(char *direction)
{
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];
	int exit_status;

	exit_status = 0;
	getcwd(oldpwd, PATH_MAX);
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
	remplace_if_already_exist("OLDPWD", oldpwd); //! CAS SI OLDPWD N'EXISTE PAS
	getcwd(pwd, PATH_MAX);
	remplace_if_already_exist("PWD", pwd); //! CAS SI PWD N'EXISTE PAS
	return (exit_status);
}

// exit status OKOK
int	ft_cd(char **cmd_param)
{
	int		nbr_param;

	nbr_param = ft_multi_array_len(cmd_param);
	if (nbr_param > 2)
		return (print_error("minishell: cd: too many arguments\n"), 1);
	if (nbr_param == 2)
		return (change_cd(cmd_param[1]));
	if (nbr_param == 1)
		return (change_cd(""));
	return (SUCCESS);
}

//? "=XXXXXXX" OKOK