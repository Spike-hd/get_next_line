int    parse_buffer(char *buffer, char **storage, int nb_read)
{
    int i;
    static char *repository;

    if (!buffer)
        return (0);
    storage = complete_storage(buffer, repository, nb_read);
    i = parse_storage(storage);  // pour trouver \n
    if (i != -1)
    {
        repository = update_repository(storage, i); // on modifie storage pour avoir toute la ligne jusque \n et on laisse le reste a repository
        return (1);
    }
    return (0);
}

char    *complete_storage(char *buffer, char *repository, int n)
{
    char    *new_storage;
    int total_size;
    int i;
    int j;

    total_size = n + ft_strlen(repository);
    new_storage = (char *)malloc(total_size + 1);
    if (!new_storage)
        return (NULL);
    i = 0;
    if (repository != NULL)
    {
        while (repository[i])
        {
            new_storage[i] = repository[i];
            i++;
        }
    }
    j = -1;
    while (i + (++j) < total_size)
        new_storage[i + j] = buffer[j];
    new_storage[i + j] = '\0';
    return (new_storage);
}


int main()
{
    char *str;
    complete_storage()
}