/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:55:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/17 22:28:56 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fd_open(t_redirct *rd)
{
	if (rd->type == STDIN)
		return (open(rd->value, O_RDONLY));
	else if (rd->type == STDOUT)
		return (open(rd->value, O_RDWR | O_CREAT | O_TRUNC, 0644));
	else if (rd->type == APPEND)
		return (open(rd->value, O_RDWR | O_CREAT | O_APPEND, 0644));
	else
	{
		// heredoc
		return (0);
	}
}

void	do_heredoc(t_redirct *rd, int fd)
{
	char *line;
	printf("rd: %s, fd: %d\n", rd->value, fd);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(rd->value, line, ft_strlen(rd->value)) \
			&& !ft_strncmp(rd->value, line, ft_strlen(line)))
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
	free(line);
}

void	do_redirct(t_redirct *rd)
{
	int	fd;

	fd = fd_open(rd);
	if (rd->type == STDIN)
		dup2(fd, STDIN_FILENO);
	else if (rd->type == STDOUT || rd->type == APPEND)
		dup2(fd, STDOUT_FILENO);
	else if (rd->type == HEREDOC) // heredoc 안됨ㅋ..
		do_heredoc(rd, STDIN_FILENO);
	close(fd);
}

void	redirection(t_redirct *redirct)
{
	while (redirct)
	{
		do_redirct(redirct);
		redirct = redirct->next;
	}
}

void	pipe_exec(t_execinfo *execinfo, int flag)
{
	int			fds[2];
	pid_t		pid;
	int			status;

	pipe(fds);
	pid = fork(); // fork 실패 error처리
	if (pid == 0)
	{
		close(fds[0]);
		if (!flag) // 마지막 cmd
			dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		redirection(execinfo->redirct);
		if (check_builtin(execinfo->cmd[0], execinfo))
			return ;
		execinfo->path = find_path(execinfo->cmd, pars_envp(execinfo->envp));
		if (execve(execinfo->path, execinfo->cmd, execinfo->envp) == -1)
			printf("command not found\n");
	}
	else
	{
		waitpid(pid, &status, 0);
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
}
