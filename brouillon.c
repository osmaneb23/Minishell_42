# include <fcntl.h>                  // open, close
# include <linux/limits.h>           // INT_MAX, INT_MIN, PATH_MAX etc
# include <stdio.h>                  // printf
# include <readline/history.h>       // add_history
# include <readline/readline.h>      // readline
# include <signal.h>                 // signal
# include <stdbool.h>                // bool
# include <stdlib.h>                 // malloc, free, exit
# include <sys/stat.h>               // stat
# include <sys/types.h>              // pid_t
# include <sys/wait.h>               // waitpid
# include <unistd.h>                 // execve, fork, pipe
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av, char **env) 
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("Erreur lors de fork");
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) 
    {
        char *programme = "/bin/ls";
        char *args[] = { "ls", NULL };

        if (execve(programme, args, env) == -1) 
        {
            perror("Erreur d'exécution avec execve");
            exit(EXIT_FAILURE);
        }
    } 
    else 
    {
        int status;
        pid_t result = waitpid(pid, &status, 0);

        if (result == -1) 
        {
            perror("Erreur lors de waitpid");
            exit(EXIT_FAILURE);
        } 
        printf("VALO>CS\n");
    }
    return 0;
}
