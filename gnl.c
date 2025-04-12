#include "philo.h"
#include <stdlib.h> 

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

char *ft_strdup(char *str)
{
    int i = 0;
    int length = 0;
    char *all;

    while (str[length])
        length++;
    all = malloc(sizeof(char) * length + 1);
    if (!all)
        return (NULL);
    while (str[i])
    {
        all[i] = str[i];
        i++;
    }
    all[i] = '\0';
    return (all);
}
char *gnl(int fd)
{
    static char buffer_str[BUFFER_SIZE];
    static char line[700000];
    static char count_pos;
    static char count_read;
    int i = 0;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (count_pos >= count_read)
        {
            count_read = read(fd, buffer_str, BUFFER_SIZE);
            count_pos = 0;
            if (count_read <= 0)
                break;
        }
        line[i++] = buffer_str[count_pos++];
        if (line[i - 1] == '\n')
            break;   
    }
    line[i] = '\0';
    if (i == 0) 
        return (NULL);
    return (ft_strdup(line));
}
#include <fcntl.h>
#include <stdio.h>
int main ()
{
    int fd = open("file", O_RDWR, 0);

    char *line = gnl(fd);
    printf("%s\n", line);
    free(line);
}
