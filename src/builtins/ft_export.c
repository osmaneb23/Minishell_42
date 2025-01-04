/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:05:59 by febouana          #+#    #+#             */
/*   Updated: 2025/01/04 18:01:18 by obouayed         ###   ########.fr       */
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
		return (print_error("minishell: export: `"), print_error(var),
			print_error("': not a valid identifier\n"), 1);
	to_print = ft_strdup(var);
	if (!to_print)
		return (EXIT_MALLOC);
	if (append_node_envp(&envp, to_print) != SUCCESS)
		return (EXIT_MALLOC);
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
	int		res;

	if (export_init_vars(&var_and_val, &var, &val, i) != SUCCESS)
		return (EXIT_MALLOC);
	if (export_not_valid(var_and_val, var) != SUCCESS)
		return (free(var), free(val), 1);
	res = remplace_if_already_exist(var, val);
	if (res == EXIT_MALLOC)
		return (free(val), free(var), EXIT_MALLOC);
	if (res == SUCCESS)
		return (free(val), free(var), SUCCESS);
	if (ft_strcmp(val, "") == 0)
	{
		to_print = join_var_and_val(var, "");
		if (append_node_envp(&envp, to_print) != SUCCESS)
			return (free(val), free(var), EXIT_MALLOC);
		return (free(val), free(var), SUCCESS);
	}
	to_print = join_var_and_val(var, val);
	if (append_node_envp(&envp, to_print) != SUCCESS)
		return (free(val), free(var), EXIT_MALLOC);
	return (free(val), free(var), SUCCESS);
}

//?OKOK
//+ Permet d'afficher les variables exportes
//+ ">export"
bool	export_just_display(t_data *data)
{
	int		count;
	char	**tab_envp;

	count = count_envp_nodes(data->envp);
	tab_envp = copy_envp_to_tab(data, data->envp);
	if (!tab_envp)
		return (false);
	sort_envp_and_print(tab_envp, count);
	ft_free_multi_array(tab_envp);
	return (true);
}

//?OKOK
// exit status OKOK
int	ft_export(char **cmd_param)
{
	int		exit_status;
	int		i;
	int		j;
	t_data	*data;

	exit_status = 0;
	i = 0;
	j = 1;
	data = get_data();
	if (ft_strcmp(cmd_param[0], "export") == 0
		&& ft_multi_array_len(cmd_param) == 1)
		if (!export_just_display(data))
			return (EXIT_MALLOC);
	while (cmd_param[j])
	{
		i = search_egal_symbol(cmd_param[j]);
		if (i >= 0)
			exit_status = export_new_var_and_val(data->envp, cmd_param[j], i);
		if (i == -1)
			exit_status = export_just_new_var(data->envp, cmd_param[j]);
		j++;
	}
	return (exit_status);
}
