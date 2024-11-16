#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

#define SIZE 5

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char *troncate_storage(char **storage, int i);
int parse_storage(char *storage);
char    *increase_storage(char *buffer, char *storage, int i);
int    parse_buffer(char *buffer, char **storage, int nb_read);
char    *get_next_line(int fd);

#endif