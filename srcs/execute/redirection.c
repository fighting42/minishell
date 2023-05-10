/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:06:34 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/08 21:26:40 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unlink_heredoc(int cnt)
{
	char	*file;
	int		i;

	i = 1;
	while (i <= cnt)
	{
		file = ft_strjoin(".heredoc/.tmp", ft_itoa(i));
		unlink(file);
		free(file);
		i++;
	}
}

char	*do_heredoc(t_redirct *redirct, t_exec *exec)
{
	char		*line;
	int			fd;
	int			tmp_stdin;
	char		*file;

	file = ft_strjoin(".heredoc/.tmp", ft_itoa(exec->heredoc_cnt));
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	exec->heredoc_cnt--;
	tmp_stdin = dup(STDIN_FILENO);
	dup2(exec->stdin_ori, STDIN_FILENO);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(redirct->value, line, ft_strlen(redirct->value)) \
			&& !ft_strncmp(redirct->value, line, ft_strlen(line)))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	dup2(tmp_stdin, STDIN_FILENO);
	free(line);
	close(fd);
	return (file);
}

int	fd_open(t_redirct *redirct)
{
	if (redirct->type == STDIN || redirct->type == HEREDOC)
		return (open(redirct->value, O_RDONLY));
	else if (redirct->type == STDOUT)
		return (open(redirct->value, O_RDWR | O_CREAT | O_TRUNC, 0644));
	else if (redirct->type == APPEND)
		return (open(redirct->value, O_RDWR | O_CREAT | O_APPEND, 0644));
	return (0);
}

void	do_redirct(t_redirct *redirct)
{
	int	fd;

	fd = fd_open(redirct);
	if (redirct->type == STDIN || redirct->type == HEREDOC)
		dup2(fd, STDIN_FILENO);
	else if (redirct->type == STDOUT || redirct->type == APPEND)
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirct(t_exec *exec)
{
	t_redirct	*redirct;

	redirct = exec->pipeline->redirct;
	while (redirct)
	{
		do_redirct(redirct);
		redirct = redirct->next;
	}
}
