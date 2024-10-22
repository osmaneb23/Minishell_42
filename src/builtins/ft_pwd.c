#include "../includes/minishell.h"

// possibilite de trouver current path avec getenv() mais bon
int ft_pwd()
{
    
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX))
    {
        printf("%s\n", cwd);
        return (SUCCESS);
    }
    else
    {
        perror("Failure: getcwd\n");
        return (FAILURE);
    }
}
