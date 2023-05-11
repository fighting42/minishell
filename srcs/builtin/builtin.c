/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 01:39:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/16 02:39:30 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_builtin(t_exec *exec)
{
	char	*cmd;

	cmd = exec->pipeline->cmd[0];
	if (cmd)
	{
		if (!ft_strncmp("cd", cmd, ft_strlen(cmd)) \
			&& !ft_strncmp("cd", cmd, 2))
			return (ft_cd(exec->pipeline));
		else if (!ft_strncmp("export", cmd, ft_strlen(cmd)) \
			&& !ft_strncmp("export", cmd, 5))
			return (ft_export(exec->pipeline));
		else if (!ft_strncmp("unset", cmd, ft_strlen(cmd)) \
			&& !ft_strncmp("unset", cmd, 5))
			return (ft_unset(exec->pipeline));
		else if (!ft_strncmp("exit", cmd, ft_strlen(cmd)) \
			&& !ft_strncmp("exit", cmd, 4))
			return (ft_exit(exec));
	}
	return (1);
}

int	check_builtin_fd(t_pipeline *pipeline, int fd)
{
	char	*cmd;

	cmd = pipeline->cmd[0];
	if (cmd)
	{
		if (!ft_strncmp("echo", cmd, ft_strlen(cmd)) \
			&& !ft_strncmp("echo", cmd, 4))
			return (ft_echo(pipeline->cmd, fd));
		else if (!ft_strncmp("pwd", cmd, ft_strlen(cmd)) \
			&& !ft_strncmp("pwd", cmd, 3))
			return (ft_pwd(fd));
		else if (!ft_strncmp("env", cmd, ft_strlen(cmd)) \
			&& !ft_strncmp("env", cmd, 3))
			return (ft_env(pipeline, fd));
	}
	return (1);
}
