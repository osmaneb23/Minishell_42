#include "../../includes/minishell.h"

int count_nbr_cmd(t_token *token)
{
    t_token *tmp;
    int i;

    i = 0;
    if (!token || !token->next)
        return (FAILURE); //! car -1 mais devrait etre logiquement ERROR : donc ?
    tmp = token;
    while(tmp != NULL)
    {
        if (strcmp(tmp->value, "|") == 0 || tmp->type == 5)
            i++;
        tmp = tmp->next;
    }
    return (i + 1); // donc renvoi 1 si aucun pipe trouve 
}

// int exec(t_data *data)
// {
//     printf("EXEC :\n");
//     // create_list_cmd(data->token); 
//     t_token *token = data->token;
//     printf("%s\n", token->value);
//     token = token->next;
//     printf("%s\n", token->value);
//     token = token->next;
//     printf("%s\n", token->value);
//     token = token->next;
//     printf("%s\n", token->value);
//     token = token->next;
//     printf("%s\n", token->value);

//     // token = token->next;
//     // printf("%s\n", token->value);
//     // token = token->next;
//     // printf("%s\n", token->value);
    
//     // if une seule cmd 
//         // 

//     // if plusieurs cmd "|"
//         // 

//     return (SUCCESS);
// }

int exec_builtin(char **cmd)
{
    // if (ft_strcmp(cmd[0], "echo") == 0)
    //     return (ft_echo());
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
    // if (ft_strcmp(cmd[0], "exit") == 0)
    //     return (ft_exit());
    return (FAILURE);
}

int launch_builtin(/*t_data *data,*/ char **cmd)
{

    exec_builtin(cmd);

    return (SUCCESS);
}

//? le dernier element de *cmd_param == NULL
int exec(t_data *data)
{
    printf("EXEC :\n");

    t_cmd *cmd;
    // int pip;
    
    cmd = data->cmd;
    // pip = data->pip;



    //! CAS OU LE PREMIER ARG != DE CMD A PRENDRE EN COMPTE // cmd->skip_cmd
    if (cmd && is_builtin(cmd->cmd_param[0])) // CMD BUILTIN SEUL
        return (launch_builtin(/*data,*/ cmd->cmd_param)); 
    // if (pipe(pip) == -1)
    //     return (ERROR); //free
    // exec_cmd();
    // cmd = cmd->next;
    // while (cmd != NULL)
    // {
    //     printf("alriiight\n");
    //     cmd = cmd->next;
    // }
    //wait_all();
    return (SUCCESS);
}

    // int i;

    // i = 0;
    // while (cmd->cmd_param[i] != NULL)
    // {
    //     printf("%s\n", cmd->cmd_param[i]);
    //     i++;
    // }
    // i = 0;
    // cmd = cmd->next;
    // while (cmd->cmd_param[i] != NULL)
    // {
    //     printf("%s\n", cmd->cmd_param[i]);
    //     i++;
    // }