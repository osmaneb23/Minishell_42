/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:05:59 by febouana          #+#    #+#             */
/*   Updated: 2024/12/10 23:17:46 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//?OKOK
//+ Affiche les variables exportes avec
//+ la bonne syntaxe
void	print_export_line(char *line)
{
	int	i;

	i = 0;
	printf("export ");
	while (line[i] != '=')
	{
		printf("%c", line[i]);
		i++;
	}
	printf("=");
	i++;
	printf("\"");
	while (line[i])
	{
		printf("%c", line[i]);
		i++;
	}
	printf("\"");
	printf("\n");
}

//?OKOK
//+ Permet d'exporter une nouvelle variable seule
//+ ">export VAR"
int	export_just_new_var(t_env *envp, char *var)
{
	char	*to_print;
	t_env	*tmp;
	int		len;

	tmp = envp;
	len = ft_strlen(var);
	while (tmp != NULL)
	{
		if (ft_strncmp(var, tmp->line, len) == 0)
			return (SUCCESS);
		tmp = tmp->next;
	}
	if (verif_var_char(var) == ERROR)
	{
		printf("Error: export: %s: not a valid identifier\n", var);
		return (SUCCESS);
	}
	to_print = ft_strdup(var);
	if (!to_print)
		return (cleanup(ERROR, ERR_MALLOC, ERROR, 2));
	append_node_envp(&envp, to_print);
	return (SUCCESS);
}

//?OKOK
//+ Permet d'exporter une nouvelle variable et sa valeur
//+ ">export VAR=VAL"
int	export_new_var_and_val(t_env *envp, char *var_and_val, int i)
{
	char	*to_print;
	char	*var;
	char	*val;

	var = return_var(var_and_val, i);
	val = return_val(var_and_val, i);
	if (!strcmp(var, "") || verif_var_char(var))
	{
		print_error("minishell: export: `");
		print_error(var_and_val);
		return (free(var), free(val), print_error("': not a valid identifier\n"), 1); //OKOK
	}
	if (!remplace_if_already_exist(var, val))
		return (free(val), free(var), SUCCESS);
	if (ft_strcmp(val, "") == 0)
	{
		to_print = join_var_and_val(var, "");
		return (free(val), free(var), append_node_envp(&envp, to_print),
			SUCCESS);
	}
	to_print = join_var_and_val(var, val);
	append_node_envp(&envp, to_print);
	return (free(val), free(var), SUCCESS);
}

//?OKOK
//+ Permet d'afficher les variables exportes
//+ ">export"
void	export_just_display(t_data *data)
{
	int		count;
	char	**tab_envp;

	count = count_envp_nodes(data->envp);
	tab_envp = copy_envp_to_tab(data, data->envp);
	sort_envp_and_print(tab_envp, count);
	ft_free_multi_array(tab_envp);
}

//?OKOK
void	ft_export(char **cmd_param)
{
	int		i;
	int		j;
	t_data	*data;

	i = 0;
	j = 1;
	data = get_data();
	if (ft_strcmp(cmd_param[0], "export") == 0
		&& ft_multi_array_len(cmd_param) == 1)
		return (export_just_display(data));
	while (cmd_param[j])
	{
		i = search_egal_symbol(cmd_param[j]);
		if (i >= 0)
			data->exit_status = export_new_var_and_val(data->envp, cmd_param[j], i);
		if (i == -1)
			data->exit_status = export_just_new_var(data->envp, cmd_param[j]);
		j++;
	}
}

//* cas msg d'erreur "VAR=val"
//* cas "VAR1=ehbfnwekfj=weofhjwefjkn=wefouih"
//* cas "VAR1=val1 VAR2=val2"
//* cas avec "VAR1="