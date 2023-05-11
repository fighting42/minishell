/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 03:36:05 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/11 21:06:44 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*malloc_backup(void)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char));
	if (!tmp)
		return (0);
	tmp[0] = '\0';
	return (tmp);
}

static char	*read_line(int fd, char *buf, char *backup)
{
	int		byte;
	char	*tmp;

	while (1)
	{
		byte = read(fd, buf, BUFFER_SIZE);
		if (byte == -1)
			return (0);
		else if (byte == 0)
			break ;
		buf[byte] = '\0';
		if (!backup)
			backup = malloc_backup();
		tmp = backup;
		backup = ft_strjoin(tmp, buf);
		if (!backup)
			return (0);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (backup);
}

static char	*backup_line(char *line)
{
	int		i;
	char	*backup;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (0);
	backup = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!backup)
		return (0);
	if (!backup[0])
	{
		free(backup);
		backup = NULL;
		return (0);
	}
	line[i + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*backup;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (0);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	line = read_line(fd, buf, backup);
	free(buf);
	buf = NULL;
	if (!line)
		return (0);
	backup = backup_line(line);
	return (line);
}
