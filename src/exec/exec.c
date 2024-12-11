#include "../../includes/minishell.h"

int	redirect_input_output(t_cmd *cmd, int *pip)
{
	if (cmd->infile >= 0) // si redirection d'entree de precisee ?
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
			// si redirection de sortie de precisee ? + //! secu
		close(cmd->outfile);
	}
	else if (cmd->next != NULL) // si cmd n'est pas la derniere cmd
		dup2(pip[1], STDOUT_FILENO);
	return (SUCCESS);
}

int	parent_process(int *pip, t_cmd *next_cmd)
{
	close(pip[1]);
	if (next_cmd)
		next_cmd->infile = pip[0];
	else
		close(pip[0]);
    return (SUCCESS);
}

int	destroy_child_process(int exit_status)
{
	t_data	*data;

	data = get_data();
	close_all_redi(data); //+ CLOSE LES REDI DE TOUS LES NOEUDS CMD
	if (data->cmd)
		free_all_cmd_nodes(&data->cmd); //+ VIDE ET DETRUIT TOUS LES NOEUDS DE CMD
	if (data->envp)
		destroy_envp_list(&data->envp); //+ DETRUIT ENV
	if (data)
	{
		free_data(&data);
		data->exit_status = exit_status;
	}
    rl_clear_history();
	printf("\n\nEXIT-STATUS==%d\n\n", exit_status);
	exit (exit_status);
}

int	child_process(t_cmd *cmd, int *pip, char **env)
{

	t_data* data = get_data();
	char	*path;

	if (cmd->infile >= 0)
		close(pip[0]);
	if (cmd->outfile < 0 && cmd->next != NULL)
		cmd->outfile = pip[1];
	if (is_builtin(cmd->cmd_param[0]))
	{
		redirect_input_output(cmd, pip);
		exec_builtin(cmd->cmd_param);
	}
	else
	{
		redirect_input_output(cmd, pip);
		if (access(cmd->cmd_param[0], X_OK) == 0)
			execve(cmd->cmd_param[0], cmd->cmd_param, env); //! signaux avec ./minishell
		else 
		{	
			path = return_command_in_path(cmd->cmd_param[0]);
			execve(path, cmd->cmd_param, env);
			free(path);
		}
	}
	printf("SSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSs\n\n");
    ft_free_multi_array(env);
    destroy_child_process(data->exit_status);
	return (SUCCESS); // VOID ?
}

int	exec_cmd(t_data *data, t_cmd *cmd, int *pip)
{
	char	**env;

	env = copy_envp_to_tab(data, data->envp);
	if (!env)
		return (cleanup(ERROR, ERR_MALLOC, ERROR, 2));
	cmd->f_pid = fork();
 
	if (cmd->f_pid == 0)
	{
		if (cmd && cmd->cmd_param[0])
			return (child_process(cmd, pip, env));
		// else
		// {
		// 	destroy_child_process(ERROR, STDERR_FILENO); //! free mais segfault a cause de main routine
		// 	return (ERROR); //! free mais segfault a cause de main routine
		// }
	}
	else
	{
		if (env)
			ft_free_multi_array(env);
		return (parent_process(pip, cmd->next));
	}
    return (SUCCESS);
}

int	exec(t_data *data)
{
	t_cmd	*tmp;
	int		*pip;

	if (init_cmd(data) == ERROR)
		return (ERROR); //? OKOK
	tmp = data->cmd;
	pip = data->pip;
	if (is_builtin(tmp->cmd_param[0]) && cmd_list_len(data->cmd) == 1)
		return (launch_builtin(tmp), data->exit_status);
    printf("\n\nPIPEX\n\n");
	while (tmp)
	{
		if (pipe(pip) == -1)
			return (cleanup(ERROR, ERR_PIPE, ERROR, 2));
		exec_cmd(data, tmp, pip);
		tmp = tmp->next;
	}
    close_all_redi(data);
    wait_all(data);
    if (data->exit_status != SUCCESS)
        return (ERROR);
    return (SUCCESS);
}

// WIFEXITED ==> verifie le status
// WEXITSTATUS ==> retourne l'exit_status



//? =======================================================
// FEHIM: 
//* corriger appel chemin absolu et executable
//* revoir comportement builtin // repertoire courant (ASKIP)

//! secu si envp entierement unset

//! revoir exit status de chaque builtins 
//! revoir return ERR malloc...etc dans exec 

//! corriger cmd_init (// "< infile | wc" ==> cas d'encule)

//? =======================================================
// OSMANE:
//! corriger ft_exit (//strtol)
//! cas signaux si execute dans minishell (// ctrl-C)