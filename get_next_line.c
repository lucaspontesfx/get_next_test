/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucda-si <lucda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 17:16:29 by lucda-si          #+#    #+#             */
/*   Updated: 2024/12/11 17:33:51 by lucda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next(char	*file)
{
	char	*next_line;
	size_t	i;
	size_t	j;

	if (!file || !*file)
		return (free(file), NULL);
	i = 0;
	while (file[i] != '\0' && file[i] != '\n')
		i++;
	if (!file[i])
		return (free(file), NULL);
	i++;
	next_line = (char *)malloc(sizeof(char) * (ft_strlen(file) - i + 1));
	if (!next_line)
		return (NULL);
	j = 0;
	while (file[i])
	{
		next_line[j] = file[i];
		j++;
		i++;
	}
	next_line[j] = '\0';
	free(file);
	return (next_line);
}

char	*extract_line(char *file)
{
	char	*line;
	size_t	len;
	int		i;

	if (!file || !*file)
		return (NULL);
	len = 0;
	while (file[len] != '\0' && file[len] != '\n')
		len++;
	line = ft_calloc(sizeof(char), (len + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (file[i] != '\0' && file[i] != '\n')
	{
		line[i] = file[i];
		i++;
	}
	if (file[i] == '\n')
		line[i] = '\n';
	line[++i] = '\0';
	return (line);
}

static char	*read_file(int fd, char *file)
{
	char	*buffer;
	char	*tmp;
	ssize_t	b_read;

	if (!file)
		file = ft_strdup("");
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free(file), NULL);
	b_read = 1;
	while (b_read > 0 && !ft_strchr(file, '\n'))
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
			return (free(buffer), free(file), NULL);
		buffer[b_read] = '\0';
		tmp = ft_strjoin(file, buffer);
		if (!tmp)
			return (free(buffer), free(file), NULL);
		free(file);
		file = tmp;
	}
	free(buffer);
	return (file);
}

char	*get_next_line(int fd)
{
	static char	*file;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	file = read_file(fd, file);
	if (!file)
		return (NULL);
	line = extract_line(file);
	file = get_next(file);
	return (line);
}
/*
int	main(void)
{
	char	*line;
	int		fd;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (-1);
	line = "init";
	while ((line = get_next_line(fd)) != NULL)
	{	
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
Verification removed that was giving me issues with leak
if (file[len] == '\n')
	line = ft_calloc(sizeof(char), (len + 2));
if (file[len] == '\0')
	line = ft_calloc(sizeof(char), (len + 1));
*/
