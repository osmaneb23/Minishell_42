
#include "../../includes/minishell.h"

//! with no options
int ft_env(void)
{
    t_data *data = get_data();
    t_env *tmp;

    if (!data || !data->envp)
        return (ERROR);
    tmp = data->envp;
    while(tmp != NULL)
    {
        if (ft_strchr(tmp->line, '=')) //! NUANCE RAJOUTEE DEPUIS NEW MAKE_ENV() : BIEN ? PAS BIEN ?
            printf("%s\n", tmp->line);
        tmp = tmp->next;
    }
    return (SUCCESS);
}
