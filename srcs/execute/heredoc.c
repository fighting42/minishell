/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 21:12:39 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/15 16:51:17 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unlink_heredoc(void)
{
	char	*file;
	int		i;
	char	*num;

	i = 1;
	while (i <= 16)
	{
		num = ft_itoa(i);
		file = ft_strjoin(".heredoc/.tmp", num);
		if (!access(file, F_OK))
			unlink(file);
		free(file);
		free(num);
		i++;
	}
}

void	do_heredoc(t_redirct *redirct, t_exec *exec, char *file)
{
	char		*line;
	int			fd;
	char		*tmp;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(exec->stdin_ori, STDIN_FILENO);
	dup2(exec->stdout_ori, STDOUT_FILENO);
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(redirct->value, line, ft_strlen(redirct->value)) \
			&& !ft_strncmp(redirct->value, line, ft_strlen(line)))
			break ;
		if (ft_strncmp(line, "", 1))
		{
			tmp = env_str_heredoc(line, exec->pipeline->env);
			if (tmp)
				write(fd, tmp, ft_strlen(tmp));
			free(tmp);
		}
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
}

char	*fork_heredoc(t_redirct *redirct, t_exec *exec)
{
	pid_t		pid;
	int			status;
	char		*file;
	char		*num;

	num = ft_itoa(exec->heredoc_cnt);
	file = ft_strjoin_free_back(".heredoc/.tmp", num);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sigint_handler_heredoc);
		do_heredoc(redirct, exec, file);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		exec->heredoc_cnt--;
		g_status = WEXITSTATUS(status);
		if (!g_status)
			return (file);
		return (NULL);
	}
}

int	check_heredoc(t_exec *exec)
{
	t_redirct	*tmp;

	tmp = exec->pipeline->redirct;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->type == HEREDOC)
			{
				tmp->value = fork_heredoc(tmp, exec);
				if (!tmp->value)
				{
					rl_replace_line("", 0);
					return (1);
				}
			}
			tmp = tmp->next;
		}
	}
	return (0);
}
