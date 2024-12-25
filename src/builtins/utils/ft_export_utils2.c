/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:08:32 by febouana          #+#    #+#             */
/*   Updated: 2024/12/25 16:39:58 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//?OKOK
//+ Permet de verifier les caractères valides d'une VAR d'envp
bool	verif_var_char(char *var)
{
	int		i;
	int		j;
	char	invalid_char[26];

	i = 0;
	j = 0;
	ft_strcpy(invalid_char, "!@#$%^&*()+=,.:/?<>{}[]|-");
	if (isdigit(var[0]))
		return (ERROR);
	while (var[j])
	{
		while (invalid_char[i])
		{
			if (var[j] == invalid_char[i])
				return (ERROR);
			i++;
		}
		i = 0;
		j++;
	}
	return (SUCCESS);
}

//?OKOK
//+ Permet de remplacer la valeur existante de VAR par VAL
//! laisser return (ERROR)
int	remplace_if_already_exist(char *var, char *val)
{
	char	*to_print;
	t_data	*data;
	t_env	*tmp;
	int		len;

	to_print = NULL;
	data = get_data();
	tmp = data->envp;
	len = ft_strlen(var);
	while (tmp)
	{
		if (ft_strncmp(var, tmp->line, len) == 0)
		{
			to_print = join_var_and_val(var, val);
			if (!to_print)
				return (EXIT_MALLOC);
			free(tmp->line);
			tmp->line = NULL;
			return (tmp->line = to_print, SUCCESS);
		}
		tmp = tmp->next;
	}
	return (ERROR);
}

//+ Permet de trier un char**
void	envp_tab_bubble_sort(char **envp, int count)
{
	char	*temp;
	int		i;

	i = 0;
	while (i < count - 1)
	{
		if (ft_strcmp(envp[i], envp[i + 1]) > 0)
		{
			temp = envp[i];
			envp[i] = envp[i + 1];
			envp[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

//?OKOK
//+ Permet de trier un tabtab contenant env et de l'afficher
void	sort_envp_and_print(char **envp, int count)
{
	int	i;

	i = 0;
	envp_tab_bubble_sort(envp, count);
	while (envp[i])
	{
		if (strncmp(envp[i], "_=", 2) != 0)
		{
			if (ft_strchr(envp[i], '='))
				print_export_line(envp[i]);
			else
				printf("export %s\n", envp[i]);
		}
		i++;
	}
}

//?OKOK
//+ Permet de convertir la liste env en tabtab et de la retourner
char	**copy_envp_to_tab(t_data *data, t_env *envp)
{
	int		i;
	t_env	*tmp;
	char	**env_tab;
	int		count;

	i = 0;
	tmp = envp;
	count = count_envp_nodes(data->envp);
	if (!count)
		return (NULL);
	env_tab = malloc((count + 1) * sizeof(char *));
	if (!env_tab)
		return (NULL);
	while (i < count)
	{
		env_tab[i] = ft_strdup(tmp->line);
		if (!env_tab[i])
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	env_tab[count] = NULL;
	return (env_tab);
}
