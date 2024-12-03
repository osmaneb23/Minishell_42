#include <stdio.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	int	a;

	a = 0;
	while (s[a])
		a++;
	return (a);
}

char *return_var(char *var_and_val, int limit)
{
    char *var;
    int start;

    start = 0;
    var = (char *)malloc(sizeof(char) * (limit + 1));
    if (!var)
        return (NULL);
    while (start < limit)
    {
        var[start] = var_and_val[start];
        start++;
    }
    var[start] = '\0';
    return(var);
}

char *return_val(char *var_and_val, int start)
{
    char *val;
    int limit;
    int i;

    i = 0;
    limit = ft_strlen(var_and_val);
    val = (char *)malloc(sizeof(char) * (limit - start));
    if (!val)
        return(NULL);
    start++;
    while (start < limit)
    {
        val[i] = var_and_val[start];
        start++;
        i++;
    }
    val[i] = '\0';
    return(val);
}

int main()
{
    char *res1;
    char *res2;

    res1 = return_var("AAAA=aaaa", 4);
    printf("\n\n");
    printf("MAIN-var> %s", res1);
    res2 = return_val("AAAA=aaaa", 4);
    printf("\n\n");
    printf("MAIN-val> %s", res2);
    printf("\n\n");
}
