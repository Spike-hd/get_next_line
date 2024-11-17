/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hduflos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:53:17 by hduflos           #+#    #+#             */
/*   Updated: 2024/11/17 13:38:48 by hduflos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*truncate_storage(char **storage, int i)
{
	char	*result;
	char	*new_storage;
	int		storage_len;

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

int	parse_storage(char *storage)
{
	int	i;

	i = 0;
	if (!storage)
		return (0);
	while (storage[i])
	{
		if (storage[i] == '\n')
			return (i);
		i++;
	}
	return (0);
}

char	*increase_storage(char *buffer, char *storage, int i)
{
	char	*bigger_storage;
	int		total_size;

	total_size = i + ft_strlen(storage);
	bigger_storage = (char *)malloc(total_size + 1);
	if (!bigger_storage)
		return (NULL);
	if (storage)
	{
		ft_strlcpy(bigger_storage, storage, total_size + 1);
		free(storage);
	}
	else
		bigger_storage[0] = '\0';
	ft_strlcat(bigger_storage, buffer, total_size + 1);
	return (bigger_storage);
}

int	parse_buffer(char *buffer, char **storage, int nb_read)
{
	if (!buffer || nb_read <= 0)
		return (0);
	*storage = increase_storage(buffer, *storage, nb_read);
	if (!*storage)
		return (0);
	return (parse_storage(*storage));
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	static char	*storage = NULL;
	int			nb_read;
	int			i;

	nb_read = -1;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	while (nb_read)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == -1)
		{
			free (storage);
			return (NULL);
		}
		i = parse_buffer(buffer, &storage, nb_read);
		if (i == 0 && nb_read == 0)
		{
			free(storage);
			storage = NULL;
			return (NULL);
		}
		if (i)
			return (truncate_storage(&storage, i));
	}
	free (storage);
	return (NULL);
}
