/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kethouve <kethouve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:17:16 by kethouve          #+#    #+#             */
/*   Updated: 2023/10/31 15:32:23 by kethouve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*clear_res(char	*src)
{
	int		i;
	int		j;
	char	*new_line;

	i = 0;
	j = 0;
	if (!src)
		return (0);
	while (src[j] && src[j] != '\n')
		j++;
	if (src[j] == '\n')
		j++;
	while (src[i])
		i++;
	new_line = malloc(((i - j) + 1) * sizeof(char));
	if (!new_line)
		return (0);
	i = 0;
	while (src[j])
		new_line[i++] = src[j++];
	new_line[i] = '\0';
	free(src);
	src = NULL;
	return (new_line);
}

char	*get_txt(int fd, char *res)
{
	char	*tmp;
	int		readed;

	readed = 1;
	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	tmp[0] = '\0';
	if (!tmp)
		return (0);
	while (!ft_strchr(tmp, '\n') && readed != 0)
	{
		readed = read(fd, tmp, BUFFER_SIZE);
		if (readed <= 0 && (res == NULL || res[0] == '\0'))
		{
			free(tmp);
			free(res);
			return (0);
		}
		tmp[readed] = '\0';
		res = ft_strjoin(res, tmp);
	}
	free(tmp);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*res[4096];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (free(res[fd]), res[fd] = NULL, NULL);
	if (res[fd] != NULL)
		res[fd] = clear_res(res[fd]);
	res[fd] = get_txt(fd, res[fd]);
	if (res[fd] == NULL)
	{
		free(res[fd]);
		return (0);
	}
	line = ft_get_line(res[fd]);
	return (line);
}
