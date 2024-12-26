/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: febouana <febouana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:27:50 by obouayed          #+#    #+#             */
/*   Updated: 2024/12/26 21:16:18 by febouana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_overflowing(char *str)
{
	unsigned int	i;
	unsigned int	j;
	bool			negative;

	i = 0;
	negative = false;
	while (str[i])
		i++;
	j = i;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			negative = true;
		i--;
	}
	if (i > 19)
		return (true);
	if (i == 19)
	{
		if (negative && str[j - 1] > '8')
			return (true);
		if (!negative && str[j - 1] > '7')
			return (true);
	}
	return (false);
}

long	ft_atol_exit(char *str)
{
	unsigned int	i;
	int				sign;
	long			result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}



int	fake_exit(char **cmd_param)
{
	int		i;
	t_data	*data;
	long	exit_value;

	i = 0;
	data = get_data();
	if (!cmd_param[1])
		return (data->exit_status);
	if (is_overflowing(cmd_param[1]))
		return (print_error("minishell: exit: "), print_error(cmd_param[1]),
			print_error(" numeric argument required\n"), 2);
	if (cmd_param[1][i] == '-' || cmd_param[1][i] == '+')
		i++;
	while (cmd_param[1][i])
		if (!ft_isdigit(cmd_param[1][i++]))
			return (print_error("minishell: exit: "), print_error(cmd_param[1]),
				print_error(" numeric argument required\n"), 2);
	if (cmd_param[2])
		return (print_error("minishell: exit: too many arguments\n"), 1);
	exit_value = ft_atol_exit(cmd_param[1]);
	if (exit_value < 0 || exit_value > 255)
		exit_value %= 256;
	return (exit_value);
}

int	classic_exit(char **cmd_param)
{
	int		i;
	t_data	*data;
	long	exit_value;

	i = 0;
	data = get_data();
	if (!cmd_param[1])
		return (cleanup(NO_CHANGE, "exit\n", data->exit_status, 1));
	if (is_overflowing(cmd_param[1]))
		return (print_error("minishell: exit: "), print_error(cmd_param[1]),
			cleanup(2, " numeric argument required\n", 2, 2));
	if (cmd_param[1][i] == '-' || cmd_param[1][i] == '+')
		i++;
	while (cmd_param[1][i])
		if (!ft_isdigit(cmd_param[1][i++]))
			return (print_error("minishell: exit: "), print_error(cmd_param[1]),
				cleanup(2, " numeric argument required\n", 2, 2));
	if (cmd_param[2])
		return (cleanup(1, "minishell: exit: too many arguments\n", NO_EXIT,
				2));
	exit_value = ft_atol_exit(cmd_param[1]);
	if (exit_value < 0 || exit_value > 255)
		exit_value %= 256;
	return (cleanup(exit_value, "exit\n", exit_value, 1));
}

int	ft_exit(char **cmd_param, bool is_single_cmd)
{
	t_data	*data;

	data = get_data();
	if (is_single_cmd == false)
		return (fake_exit(cmd_param));
	return (classic_exit(cmd_param));
	return (42);
}
