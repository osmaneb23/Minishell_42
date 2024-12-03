#include "../../includes/minishell.h"

//? utils_exec.c

char *get_path_next(char **path) 
{
    char *dir;
    char *next;

    if (!path || !*path)
        return NULL;
    dir = *path;
    next = ft_strchr(*path, ':');
    if (next) 
    {
        *next = '\0';
        *path = next + 1;
    } 
    else
        *path = NULL;
    return dir;
}

char *check_solo_path(char *dir, char *command) 
{
    char *full_path;
    char *tmp;

    if (!dir || !command)
        return NULL;
    tmp = ft_strjoin(dir, "/");
    if (!tmp)
        return NULL;
    full_path = ft_strjoin(tmp, command);
    free(tmp);
    if (!full_path)
        return NULL;
    if (access(full_path, X_OK) == 0)
        return full_path; 
    else 
    {
        free(full_path);
        return NULL;
    }
}

char *return_command_in_path(char *command) 
{
    char *path;
    char *path_copy;
    char *original_ptr;
    char *dir;
    char *full_path;

    if (!command)
        return NULL;
    path = getenv("PATH");
    if (!path)
        return NULL;
    path_copy = ft_strdup(path);
    if (!path_copy)
        return NULL;
    original_ptr = path_copy;
    dir = get_path_next(&path_copy);
    while (dir) 
    {
        full_path = check_solo_path(dir, command);
        if (full_path) 
        {
            free(original_ptr);
            return full_path;
        }
        dir = get_path_next(&path_copy);
    }
    free(original_ptr);
    return NULL;
}

int	close_all_redi(t_data *data)
{
    t_cmd   *cmd;

    cmd = data->cmd;
    while (cmd)
    {
        if (data->pip[1] >= 0) 
            close(data->pip[1]);
        if (data->pip[0] >= 0) 
            close(data->pip[0]);
        if (cmd->outfile >= 0) 
            close(cmd->outfile);
        if (cmd->infile >= 0) 
            close(cmd->infile);
        cmd = cmd->next;
    }
    return (SUCCESS);
}

// ======================================================================
// ======================================================================
// ======================================================================

int exec_builtin(char **cmd)
{
    if (ft_strcmp(cmd[0], "cd") == 0)
        return (ft_cd(cmd));
    if (ft_strcmp(cmd[0], "pwd") == 0)
        return (ft_pwd());
    if (ft_strcmp(cmd[0], "export") == 0)
        return (ft_export(cmd));
    if (ft_strcmp(cmd[0], "unset") == 0)
        return (ft_unset(cmd));
    if (ft_strcmp(cmd[0], "env") == 0)
        return (ft_env());
    if (ft_strcmp(cmd[0], "exit") == 0)
        return (ft_exit(cmd));
    // if (ft_strcmp(cmd[0], "echo") == 0)
    //     return (ft_echo());
    return (ERROR);
}

bool	launch_builtin(t_cmd *cmd)
{
	int	save_stdout;

	save_stdout = -1;
	if (cmd->outfile >= 0)
	{
		save_stdout = dup(STDOUT_FILENO);
		dup2(cmd->outfile, STDOUT_FILENO);
        close(cmd->outfile);
	}
	exec_builtin(cmd->cmd_param);
    if (cmd->outfile >= 0)
    {
        dup2(save_stdout, STDOUT_FILENO);
        close(save_stdout);
    }
	return (SUCCESS);
}

// ======================================================================
// ======================================================================
// ======================================================================

int redirect_input_output(t_cmd *cmd, int *pip) 
{
    if (cmd->infile >= 0) //si redirection d'entree de precisee ?
    {
        dup2(cmd->infile, STDIN_FILENO);
        close(cmd->infile);
    }
    if (cmd->outfile >= 0) 
    {
        dup2(cmd->outfile, STDOUT_FILENO); //si redirection de sortie de precisee ? + //! secu
        close(cmd->outfile);
    }
    else if (cmd->next != NULL) //si cmd n'est pas la derniere cmd 
        dup2(pip[1], STDOUT_FILENO);
    return (SUCCESS);
}

int child_process(t_data *data, t_cmd *cmd, int *pip, char **env) 
{
    char* path;

    if (cmd->infile >= 0)
        close(pip[0]);
    if (cmd->outfile < 0 && cmd->next != NULL)
        cmd->outfile = pip[1];
    if (is_builtin(cmd->cmd_param[0])) 
    {    
        redirect_input_output(cmd, pip);
        exec_builtin(cmd->cmd_param);
        ft_free_multi_array(env);
        close_all_redi(data);
        rl_clear_history();
        exit(0); //! signal
    }
    else 
    {
        redirect_input_output(cmd, pip);
        path = return_command_in_path(cmd->cmd_param[0]);
        execve(path, cmd->cmd_param, env);
        ft_free_multi_array(env);
        free(path);
        close_all_redi(data);
        rl_clear_history();
        exit(0); //! signal
    }
    return (SUCCESS);
}

int parent_process(int *pip, t_cmd *next_cmd) 
{
    close(pip[1]);
    if (next_cmd)
        next_cmd->infile = pip[0];
    else
        close(pip[0]);
    return (SUCCESS);
}

int exec_cmd(t_data *data, t_cmd *cmd, int *pip) 
{
    char **env;
    
    env = copy_envp_to_tab(data, data->envp);
    if (!env)
        return (ERROR); //? OKOK
    cmd->f_pid = fork();
    if (cmd->f_pid == -1)
        return (ERROR);
    if (cmd->f_pid == 0) 
    {
        if (cmd && cmd->cmd_param[0])
            return (child_process(data, cmd, pip, env));
        else
        {
            ft_free_contents_nodes(data); //! free mais segfault a cause de main routine
            return (ERROR); //! free mais segfault a cause de main routine
        }
    } 
    else
    {
        // ft_free_contents_nodes(data); //! nn car main process
        ft_free_multi_array(env);
        return (parent_process(pip, cmd->next));
    }
}

int	wait_all(t_data *data)
{
    t_cmd   *cmd;
	int		status;
	int		pid;
    
    cmd = data->cmd;
    while (cmd)
    {
        pid = waitpid(0, &status, 0);
        if (pid == -1)
            return (ERROR); //!
        if (pid == data->cmd->f_pid) // verifie s'il s'agit du id de fork
        {
			if (WIFEXITED(status))
				data->exit_status = WEXITSTATUS(status);
        }
        cmd = cmd->next;
    }
    return (SUCCESS);
}

int exec(t_data *data) 
{    
    t_cmd *tmp;
    int *pip;

    if (init_cmd(data) == ERROR)
        return (ERROR); //? OKOK
    tmp = data->cmd;
    pip = data->pip;
    if (is_builtin(tmp->cmd_param[0]) && t_cmd_len(data->cmd) == 1)
        return (launch_builtin(tmp));
    while (tmp)
    {
        if (pipe(pip) == -1)
            return (ERROR); ///? OKOK 
        exec_cmd(data, tmp, pip); //! segfault si renvoi ERROR (// fork // pipe)
        tmp = tmp->next;
    }
    close_all_redi(data);
    wait_all(data);
    return (SUCCESS);
}

// WIFEXITED ==> verifie le status
// WEXITSTATUS ==> retourne l'exit_status 




































// int exec_cmd(t_data *data, t_cmd *cmd, int *pip) 
// {
//     if (cmd && cmd->cmd_param[0])
//         return (ERROR);
//     cmd->f_pid = fork();
//     if (cmd->f_pid == -1)
//         return (ERROR);
//     if (cmd->f_pid == 0) 
//     {
//         if (cmd && cmd->cmd_param[0])
//             child_process(data, cmd, pip);    
//         else
//         {
//             ft_free_contents_nodes(data); //! meh
//             return (ERROR); //! meh
//         }
//     } 
//     else
//         parent_process(pip, cmd->next);
//     return (SUCCESS);
// }
