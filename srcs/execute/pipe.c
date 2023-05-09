/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:55:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/09 01:49:46 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**pars_envp(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
		i++;
	}
	if (!envp[i])
		print_error(NO_FILE_ERR, EXIT_Y, 127);
	path = ft_split(envp[i] + 5, ':');
	return (path);
}

char	*find_path(char **cmd, char **envp_path)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (envp_path[i])
	{
		if (cmd[0][0] == '/')
			path = cmd[0];
		else
		{
			tmp = ft_strjoin(envp_path[i], "/");
			path = ft_strjoin(tmp, cmd[0]);
			free(tmp);
		}
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	exec_cmd(int fds[2], t_exec *exec, int flag)
{
	t_pipeline	*pl;

	signal(SIGQUIT, SIG_DFL); // 맞나?
	pl = exec->pipeline;
	close(fds[0]);
	if (!flag)
		dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	redirct(exec);
	if (!check_builtin_fd(pl, STDOUT_FILENO))
		exit(0);
	pl->path = find_path(pl->cmd, pars_envp(pl->env->value));
	g_status = 0;
	if (execve(pl->path, pl->cmd, pl->env->value) == -1)
		print_error(errmsg(1, pl->cmd[0], NULL, CMD_ERR), EXIT_Y, 127);
}

void	exec_fork(t_exec *exec, int flag)
{
	int			fds[2];
	pid_t		pid;

	pipe(fds);
	pid = fork();
	if (pid == 0)
		exec_cmd(fds, exec, flag);
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
}
