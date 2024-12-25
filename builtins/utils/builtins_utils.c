/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:11:15 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/17 22:13:12 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

//?OKOK
//+ Permet de free un char**
void	ft_free_multi_array(char **tabtab)
{
	int	i;

	i = 0;
	if (!tabtab)
		return ;
	while (tabtab[i])
	{
		free(tabtab[i]);
		i++;
	}
	free(tabtab);
	tabtab = NULL;
}

//?OKOK
//+ Permet de compter les lignes d'un char**
int	ft_multi_array_len(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != NULL)
		i++;
	return (i);
}

//?OKOK
//+ Permet de joindre une VAR, un '=' ainsi qu'une VAL
//+ Retourne le resultat
//+ 2 == = et 0
char	*join_var_and_val(char *var, char *val)
{
	char	*to_print;
	size_t	len_var;
	size_t	len_val;

	len_var = ft_strlen(var);
	len_val = ft_strlen(val);
	to_print = malloc(len_var + 1 + len_val + 1);
	if (!to_print)
		return (NULL);
	ft_strcpy(to_print, var);
	to_print[len_var] = '=';
	ft_strcpy(to_print + len_var + 1, val);
	return (to_print);
}

//?OKOK
//+ Permet de compter le nombre de noeud dans la liste env
int	count_envp_nodes(t_env *envp)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = envp;
	while (tmp)
	{
		i++;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (i);
}
