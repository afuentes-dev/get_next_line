/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afuentes < afuentes@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:11:58 by afuentes          #+#    #+#             */
/*   Updated: 2024/07/16 12:11:49 by afuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char *buff, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buff, buf);
	free(buff);
	return (temp);
}

char	*ft_next(char *buff)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buff[i] && buff[i] != '\n')
		i++;
	if (!buff[i])
	{
		free(buff);
		return (0);
	}
	line = ft_calloc((ft_strlen(buff) - i + 1), sizeof(char));
	if (!line)
		return (0);
	i++;
	j = 0;
	while (buff[i])
		line[j++] = buff[i++];
	free(buff);
	return (line);
}

char	*ft_line(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	if (!buff[i])
		return (0);
	while (buff[i] && buff[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (0);
	i = 0;
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] && buff[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*get_read_file(int fd, char *res)
{
	char	*buff;
	int		byte;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	byte = 1;
	while (byte > 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buff);
			return (0);
		}
		buff[byte] = '\0';
		res = ft_free(res, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buff[OPEN_MAX];
	char		*line;

	if (fd < 0)
		return (0);
	if (BUFFER_SIZE <= 0 || read(fd, buff, BUFFER_SIZE) < 0)
	{
		free(buff[fd]);
		buff[fd] = 0;
		return (0);
	}
	if (!buff[fd])
	{
		buff[fd] = ft_calloc(1, 1);
		if (!buff[fd])
			return (0);
	}
	buff[fd] = get_read_file(fd, buff[fd]);
	if (!buff[fd])
	{
		free(buff[fd]);
		buff[fd] = 0;
		return (0);
	}
	line = ft_line(buff[fd]);
	buff[fd] = ft_next(buff[fd]);
	return (line);
}

/*
#include <stdio.h>
int	main(void)
{
	int		fd;
	int		fd1;
	int		fd2;
	char	*line;
	int		lines;
	lines = 1;
	fd = open ("file1.txt", O_RDONLY);
	fd1 = open ("file1.txt", O_RDONLY);
	fd2 = open ("file2.txt", O_RDONLY);

	while ((line = get_next_line(fd)))
		printf("%d->%s\n", lines++, line);
	while ((line = get_next_line(fd1)))
		printf("%d->%s\n", lines++, line);
	while ((line = get_next_line(fd2)))
		printf("%d->%s\n", lines++, line);
	close(fd);
	return (0);
}
*/
