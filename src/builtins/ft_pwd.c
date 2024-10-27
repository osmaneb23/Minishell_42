#include "../includes/minishell.h"

// possibilite de trouver current path avec getenv() mais bon
//! exec pwd peu importe quelle/combien d'argument le suit
int ft_pwd()
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX)) //! cherche direct dans l'env 
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
