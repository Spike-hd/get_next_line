
#define SIZE 5

int    parse_buffer(char *buffer, char **storage, int nb_read)
{
    int i;
    static char *repository;
    storage = complete_storage(buffer, repository, nb_read);
    i = parse_storage(storage);  // pour trouver \n
    if (i != -1)
    {
        repository = update_repository(storage, i); // on modifie storage pour avoir toute la ligne jusque \n et on laisse le reste a repository
        return 1;
    }
    return 0
}

char    *get_next_line(int fd)
{
    char    buffer[SIZE];
    char    *storage;
    int nb_read;

    nb_read = -1;
    while (nb_read)
    {
        nb_read = read(fd, buffer, SIZE);
        if (nb_read == -1)
            return (NULL);
        if (parse_buffer(buffer, &storage, nb_read))
            return (storage);
    }
    //TODO : Free storage
}