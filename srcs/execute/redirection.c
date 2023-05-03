/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:06:34 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/03 14:32:05 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unlink_heredoc(t_execinfo *execinfo)
{
	char	*file;

	while (0 < ft_atoi(&execinfo->hd_cnt))
	{
		file = ft_strjoin(".heredoc/.tmp", &execinfo->hd_cnt);
		unlink(file);
		free(file);
		execinfo->hd_cnt--;
	}
}

char	*do_heredoc(t_redirct *rd, t_execinfo *execinfo)
{
	char		*line;
	int			fd;
	char		*file;
	static char	i;

	if (!i)
		i = '1';
	else
		i++;
	file = ft_strjoin(".heredoc/.tmp", &i);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	execinfo->hd_cnt = i;
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(rd->value, line, ft_strlen(rd->value)) \
			&& !ft_strncmp(rd->value, line, ft_strlen(line)))
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

int	fd_open(t_redirct *rd, t_execinfo *execinfo)
{
	char	*file;
	int		fd;

	if (rd->type == STDIN)
		return (open(rd->value, O_RDONLY));
	else if (rd->type == STDOUT)
		return (open(rd->value, O_RDWR | O_CREAT | O_TRUNC, 0644));
	else if (rd->type == APPEND)
		return (open(rd->value, O_RDWR | O_CREAT | O_APPEND, 0644));
	else if (rd->type == HEREDOC)
	{
		file = do_heredoc(rd, execinfo);
		fd = open(file, O_RDONLY); // heredoc 환경변수 처리 추가 !
		free(file);
		return (fd);
	}
	return (0);
}

void	do_redirct(t_redirct *rd, t_execinfo *execinfo, int flag)
{
	int	fd;

	fd = fd_open(rd, execinfo);
	if (rd->type == STDIN)
		dup2(fd, STDIN_FILENO);
	else if (rd->type == HEREDOC && flag)
		dup2(fd, STDIN_FILENO);
	else if (rd->type == STDOUT || rd->type == APPEND)
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirection(t_execinfo *execinfo)
{
	t_redirct	*rd;
	int			cnt;
	int			flag;

	cnt = 0;
	rd = execinfo->redirct;
	while (rd)
	{
		if (rd->type == HEREDOC)
			cnt++;
		rd = rd->next;
	}
	if (cnt > 16)
		print_error(NULL, NULL, HEREDOC_ERR, EXIT_Y, 2);
	rd = execinfo->redirct;
	while (rd)
	{
		if (cnt - 1 == ft_atoi(&execinfo->hd_cnt))
			flag = 1;
		else
			flag = 0;
		do_redirct(rd, execinfo, flag);
		rd = rd->next;
	}
	unlink_heredoc(execinfo);
}
