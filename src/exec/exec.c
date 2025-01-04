/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouayed <obouayed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:19:49 by obouayed          #+#    #+#             */
/*   Updated: 2025/01/04 18:00:54 by obouayed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(int *pip, t_cmd *cmd)
{
	close(pip[1]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->infile == -2)
		cmd->infile = pip[0];
	if (cmd->next && cmd->next->infile == -2)
		cmd->next->infile = pip[0];
	else if (cmd->next && cmd->next->infile >= 0)
		close(pip[0]);
	else
		close(pip[0]);
}

int	destroy_child_process(int exit_status, char **to_be_free)
{
	t_data	*data;

	data = get_data();
	close_all_redi(data);
	if (to_be_free)
		ft_free_multi_array(to_be_free);
	if (data)
	{
		if (data->envp)
			destroy_envp_list(&data->envp);
		free_data(&data);
		if (data->line)
			free(data->line);
	}
	rl_clear_history();
	exit(exit_status);
}

void	child_process(t_cmd *cmd, int *pip, char **env)
{
	t_data	*data;
	char	*path;

	data = get_data();
	redirect_input_output(cmd, pip);
	if (is_builtin(cmd->cmd_param[0]))
		handle_builtin(cmd);
	else
	{
		if (access(cmd->cmd_param[0], X_OK) == 0)
			execve(cmd->cmd_param[0], cmd->cmd_param, env);
		else
		{
			path = return_command_in_path(cmd->cmd_param[0]);
			if (!path)
				destroy_child_process(EXIT_MALLOC, env);
			execve(path, cmd->cmd_param, env);
			free(path);
		}
	}
	destroy_child_process(data->exit_status, env);
}

int	exec_cmd(t_data *data, t_cmd *cmd, int *pip)
{
	data->tmp_env = copy_envp_to_tab(data, data->envp);
	if (!data->tmp_env)
		return (close_all_redi(data), cleanup(ERROR, ERR_MALLOC, ERROR, 2));
	data->current_pid = fork();
	if (data->current_pid == -1)
		return (close_all_redi(data), ft_free_multi_array(data->tmp_env),
			cleanup(ERROR, ERR_FORK, ERROR, 2));
	signal_child_process();
	if (data->current_pid == 0)
	{
		if (cmd->cmd_param && cmd->cmd_param[0])
			child_process(cmd, pip, data->tmp_env);
		else
			destroy_child_process(SUCCESS, data->tmp_env);
	}
	else
	{
		if (data->tmp_env)
			ft_free_multi_array(data->tmp_env);
		parent_process(pip, cmd);
	}
	return (SUCCESS);
}

int	exec(t_data *data, t_cmd *cmd, int *pip)
{
	if (!cmd->skip_cmd && cmd->cmd_param && cmd->cmd_param[0]
		&& is_builtin(cmd->cmd_param[0]) && cmd_list_len(data->cmd) == 1)
	{
		handle_builtin(cmd);
		if (data->exit_status == EXIT_MALLOC)
			return (cleanup(EXIT_MALLOC, ERR_MALLOC, EXIT_MALLOC, 2));
		if (data->exit_status != SUCCESS)
			return (cleanup(NO_CHANGE, NULL, NO_EXIT, 2));
		return (SUCCESS);
	}
	while (cmd)
	{
		if (pipe(pip) == -1)
			return (cleanup(ERROR, ERR_PIPE, ERROR, 2));
		exec_cmd(data, cmd, pip);
		cmd = cmd->next;
	}
	close_all_redi(data);
	wait_all(data);
	setup_signals();
	if (data->exit_status != SUCCESS)
		return (cleanup(NO_CHANGE, NULL, NO_EXIT, 2));
	return (SUCCESS);
}

// WIFEXITED ==> verifie le status
// WEXITSTATUS ==> retourne l'exit_status

//! "cat | cat | ls" avec ENTER+ENTER+ENTER
//! "pwd > file | ls"

//! re checker exit status quand SIGPIPE
