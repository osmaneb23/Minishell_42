#include "../includes/minishell.h"

// possibilite de trouver current path avec getenv() mais bon
int ft_pwd()
{
    
    char cwd[PATH_MAX]; // keske cwd...

    if (getcwd(cwd, PATH_MAX)) //! cherche direct dans l'env classique, ne pose pas pbl ?
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
