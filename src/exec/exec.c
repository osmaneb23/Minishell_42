#include "../../includes/minishell.h"

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

int parent_process(int *pip, t_cmd *next_cmd) 
{
    close(pip[1]);
    if (next_cmd)
        next_cmd->infile = pip[0];
    else
        close(pip[0]);
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
        close_all_redi(data); //+ CLOSE LES REDI DE TOUS LES NOEUDS CMD
        free_all_cmd_nodes(&data->cmd); //+ VIDE ET DETRUIT TOUS LES NOEUDS DE CMD
        free_t_env_list(&data->envp); //+ DETRUIT ENV
        exit(0); //! EXIT STATUS + SIGNAUX ??
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
        close_all_redi(data); //+ CLOSE LES REDI DE TOUS LES NOEUDS CMD
        free_all_cmd_nodes(&data->cmd); //+ VIDE ET DETRUIT TOUS LES NOEUDS DE CMD
        free_t_env_list(&data->envp); //+ DETRUIT ENV
        exit(0); //! EXIT STATUS + SIGNAUX ??
    }
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
            close_all_redi_of_each_nodes(data); //! free mais segfault a cause de main routine
            return (ERROR); //! free mais segfault a cause de main routine
        }
    } 
    else
    {
        // close_all_redi_of_each_nodes(data); //! nn car main process
        ft_free_multi_array(env);
        return (parent_process(pip, cmd->next));
    }
}

int exec(t_data *data) 
{    
    t_cmd *tmp;
    int *pip;

    if (init_cmd(data) == ERROR)
        return (ERROR); //? OKOK
    tmp = data->cmd;
    pip = data->pip;
    if (is_builtin(tmp->cmd_param[0]) && cmd_list_len(data->cmd) == 1)
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
