/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 21:55:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/14 17:47:19 by yejinkim         ###   ########seoul.kr  */
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
		print_error(errmsg(TRUE, NULL, NULL, \
			"No such file or directory"), TRUE, 127);
	path = ft_split(envp[i] + 5, ':');
	return (path);
}

char	*path_join(char **envp_path, char **cmd)
{
	int			i;
	char		*tmp;
	char		*path;

	i = 0;
	while (envp_path[i])
	{
		tmp = ft_strjoin(envp_path[i], "/");
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char **cmd, char **envp_path)
{
	struct stat	st;

	stat(cmd[0], &st);
	if (ft_strchr(cmd[0], '/'))
	{
		if (S_ISDIR(st.st_mode))
			print_error(errmsg(TRUE, cmd[0], NULL, \
				"is a directory"), TRUE, 126);
		else if (access(cmd[0], X_OK) == 0)
			return (cmd[0]);
		else
			print_error(errmsg(TRUE, cmd[0], NULL, \
				"No such file or directory"), TRUE, 127);
	}
	else
		return (path_join(envp_path, cmd));
	return (NULL);
}

void	exec_cmd(int fds[2], t_exec *exec, int flag)
{
	t_pipeline	*pl;

	pl = exec->pipeline;
	close(fds[0]);
	if (!flag)
		dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	redirct(exec);
	if (!check_builtin_fd(pl, STDOUT_FILENO))
		exit(0);
	pl->path = find_path(pl->cmd, pars_envp(pl->env->value));
	if (execve(pl->path, pl->cmd, pl->env->value) == -1)
		print_error(errmsg(TRUE, pl->cmd[0], NULL, \
			"command not found"), TRUE, 127);
}

void	exec_fork(t_exec *exec, int flag)
{
	int			fds[2];
	pid_t		pid;

	signal(SIGQUIT, SIG_DFL);
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
	signal(SIGQUIT, SIG_IGN);
}
