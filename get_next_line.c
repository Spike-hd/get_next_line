#include "get_next_line.h"

char *troncate_storage(char **storage, int i)
{
    char *result;
    char *new_storage;
    int storage_len;

    if (!storage || !*storage || i < 0)
        return (NULL);
    storage_len = ft_strlen(*storage);
    result = ft_substr(*storage, 0, i);
    if (!result)
        return (NULL);
    new_storage = ft_substr(*storage, i, storage_len - i);
    if (!new_storage)
    {
        free(result);
        return (NULL);
    }
    free(*storage);
    *storage = new_storage;
    return (result);
}

int parse_storage(char *storage)
{
    int i;

    i = 0;
    if(!storage)
        return (0);
    while (storage[i])
    {
        if (storage[i] == '\n')
            return (i);
        i++;
    }
    return (0);
}

char    *increase_storage(char *buffer, char *storage, int i)
{
    char    *bigger_storage;
    int total_size;

    total_size = i + ft_strlen(storage);
    bigger_storage = (char *)malloc(total_size + 1);
    if (!bigger_storage)
        return (NULL);

    if (storage)
    {
        ft_strlcpy(bigger_storage, storage, total_size + 1);
        free(storage); // Libérer l'ancienne mémoire de `storage`
    }
    else
        bigger_storage[0] = '\0';
    ft_strlcat(bigger_storage, buffer, total_size + 1);
    return (bigger_storage);
}

int    parse_buffer(char *buffer, char **storage, int nb_read)
{
    if (!buffer)
        return (0);
    storage = increase_storage(buffer, *storage, nb_read);
    return (parse_storage(storage));
}


char    *get_next_line(int fd)
{
    char    buffer[SIZE];
    static char    *storage = NULL;
    int nb_read;
    int i;

    nb_read = -1;
    while (nb_read)
    {
        nb_read = read(fd, buffer, SIZE);
        if (nb_read == -1)
            return (NULL);
        i = parse_buffer(buffer, &storage, nb_read);
        if (i)
            return (troncate_storage(&storage, i));
    }
    //TODO : Free storage
}