#include "../../includes/minishell.h"

//! with no options
int ft_pwd(void)
{
    char cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX)) //! cherche direct dans l'env 
    {
        printf("%s\n", cwd);
        return (SUCCESS);
    }
    else
    {
        perror("Error: getcwd\n");
        return (ERROR);
    }
}
