/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droura-s <droura-s@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:44:43 by droura-s          #+#    #+#             */
/*   Updated: 2024/10/10 13:01:31 by droura-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*free_memory(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

static char	*fill_line(char **static_buffer)
{
	char	*line;
	char	*tmp;
	int		buffer_len;
	int		i;

	buffer_len = ft_strlen(*static_buffer);
	i = find_jump(*static_buffer);
	if (i == -1)
		i = buffer_len;
	line = ft_substr(*static_buffer, 0, i + 1);
	if (!line)
		return (NULL);
	if (i + 1 >= buffer_len)
	{
		free_memory(static_buffer);
		return (line);
	}
	tmp = ft_substr(*static_buffer, i + 1, buffer_len - i - 1);
	if (!tmp)
		return (free_memory(&line));
	free_memory(static_buffer);
	*static_buffer = tmp;
	return (line);
}

static char	*read_file(int fd, char *static_buffer, char *buffer)
{
	ssize_t		bytes;
	char		*tmp;

	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free_memory(&static_buffer));
		else if (bytes == 0)
			return (static_buffer);
		buffer[bytes] = '\0';
		if (!static_buffer)
			static_buffer = ft_calloc_bzero(1, 1);
		if (!static_buffer)
			return (static_buffer);
		tmp = static_buffer;
		static_buffer = ft_strjoin(tmp, buffer);
		free_memory(&tmp);
		if (!static_buffer || !*static_buffer)
			return (free_memory(&static_buffer));
		if (find_jump(buffer) >= 0)
			return (static_buffer);
	}
	return (static_buffer);
}

char	*get_next_line(int fd)
{
	static char	*static_buffer_list[MAX_FD];
	char		*buffer;
	char		*line;

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
	{
		if (fd >= 0 && fd < MAX_FD)
			free_memory(&static_buffer_list[fd]);
		return (NULL);
	}
	buffer = ft_calloc_bzero(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	static_buffer_list[fd] = read_file(fd, static_buffer_list[fd], buffer);
	free_memory(&buffer);
	if (!static_buffer_list[fd] || !*static_buffer_list[fd])
		return (NULL);
	line = fill_line(&static_buffer_list[fd]);
	if (!line)
		return (NULL);
	return (line);
}
