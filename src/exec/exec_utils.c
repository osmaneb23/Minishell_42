#include "../../includes/minishell.h"

void	wait_all(t_data *data)
{
	int		status;
	int		pid;
    int len;
    
    len = t_cmd_len(data->cmd);

    while (len > 0)
    {
        pid = waitpid(0, &status, 0);
        if (pid == -1){
            printf("AAAAAAAAAAAAAAAAAAAAAAAA\n");
            return ;}
        len--;
    }
}

int t_cmd_len(t_cmd *cmd)
{
    t_cmd *tmp;
    int i;
    if (!cmd)
        return (FAILURE);
    tmp = cmd;
    i = 0;
    while (tmp != NULL)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

//? Compte le nbr de cmd en checkant la presence de pipe
// int count_nbr_cmd(t_token *token)
// {
//     t_token *tmp;
//     int i;

//     i = 0;
//     if (!token || !token->next)
//         return (FAILURE); //! car -1 mais devrait etre logiquement ERROR : donc ?
//     tmp = token;
//     while(tmp != NULL)
//     {
//         if (strcmp(tmp->value, "|") == 0 || tmp->type == 5)
//             i++;
//         tmp = tmp->next;
//     }
//     return (i + 1); // donc renvoi 1 si aucun pipe trouve 
// }