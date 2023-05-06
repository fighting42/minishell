/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:06:34 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/06 17:32:04 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unlink_heredoc(t_exec *exec)
{
	char	*file;

	while (0 < exec->heredoc_cnt)
	{
		file = ft_strjoin(".heredoc/.tmp", ft_itoa(exec->heredoc_cnt));
		unlink(file);
		free(file);
		exec->heredoc_cnt--;
	}
}

char	*do_heredoc(t_redirct *redirct, t_exec *exec)
{
	char		*line;
	int			fd;
	char		*file;

	file = ft_strjoin(".heredoc/.tmp", ft_itoa(exec->heredoc_cnt));
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	exec->heredoc_cnt++;
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
	free(line);
	// free(file);
	close(fd);
	return (file);
}

int	fd_open(t_redirct *redirct, t_exec *exec)
{
	char	*file;
	int		fd;

	if (redirct->type == STDIN)
		return (open(redirct->value, O_RDONLY));
	else if (redirct->type == STDOUT)
		return (open(redirct->value, O_RDWR | O_CREAT | O_TRUNC, 0644));
	else if (redirct->type == APPEND)
		return (open(redirct->value, O_RDWR | O_CREAT | O_APPEND, 0644));
	else if (redirct->type == HEREDOC)
	{
		file = do_heredoc(redirct, exec);
		fd = open(file, O_RDONLY); // heredoc 환경변수 처리 추가 !
		free(file);
		return (fd);
	}
	return (0);
}

void	do_redirct(t_redirct *redirct, t_exec *exec, int flag)
{
	int	fd;

	fd = fd_open(redirct, exec);
	if (redirct->type == STDIN)
		dup2(fd, STDIN_FILENO);
	else if (redirct->type == HEREDOC && flag)
		dup2(fd, STDIN_FILENO);
	else if (redirct->type == STDOUT || redirct->type == APPEND)
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirct(t_exec *exec)
{
	t_redirct	*redirct;
	int			cnt;
	int			flag;

	cnt = 0;
	if (exec->heredoc_cnt > 16)
		print_error(HEREDOC_ERR, EXIT_Y, 2);
	redirct = exec->pipeline->redirct;
	while (redirct)
	{
		if (cnt - 1 == exec->heredoc_cnt)
			flag = 1;
		else
			flag = 0;
		do_redirct(redirct, exec, flag);
		redirct = redirct->next;
	}
	unlink_heredoc(exec);
}
