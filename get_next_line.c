
#define SIZE 5

int    parse_buffer(char *buffer, char **storage, int nb_read)
{
    static char *storage;

}

char    *get_next_line(int fd)
{
    char    *buffer[SIZE];
    char    *storage;
    int nb_read;

    nb_read = -1;
    while (nb_read)
    {
        nb_read = read(fd, buffer, SIZE);
        if (nb_read == -1)
            return (NULL);
        parse_buffer(buffer, &storage, nb_read);
    }
}