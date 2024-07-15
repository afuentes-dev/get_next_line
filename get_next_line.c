/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afuentes < afuentes@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 09:48:34 by afuentes          #+#    #+#             */
/*   Updated: 2024/03/18 22:18:57 by afuentes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

	if (!res)
		res = ft_calloc(1, 1);
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte = 1;
	while (byte > 0)
	{
		byte = read(fd, buff, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buff);
			free(res);
			res = 0;
			return (0);
		}
		buff[byte] = 0;
		res = ft_free(res, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buff);
		buff = 0;
		return (0);
	}
	buff = get_read_file(fd, buff);
	if (!buff)
	{
		free(buff);
		buff = 0;
		return (0);
	}
	line = ft_line(buff);
	buff = ft_next(buff);
	return (line);
}

/*
#include <stdio.h>
int main(void){
	char *res;
	int fd;

	fd = open ("file2.txt", O_RDONLY);
	while ((res = get_next_line(fd))){
		printf("%s", res);
		free(res);
	}
	close(fd);
	return (0);
}
*/
