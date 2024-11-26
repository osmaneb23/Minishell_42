#include "../../includes/minishell.h"

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
