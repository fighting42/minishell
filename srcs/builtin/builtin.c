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

int	check_builtin(t_execinfo *execinfo)
{
	char	*cmd;

	cmd = execinfo->cmd[0];
	if (!ft_strncmp("cd", cmd, ft_strlen(cmd)))
		return (ft_cd(execinfo));
	else if (!ft_strncmp("export", cmd, ft_strlen(cmd)))
		return (ft_export(execinfo));
	else if (!ft_strncmp("unset", cmd, ft_strlen(cmd)))
		return (ft_unset(execinfo));
	else if (!ft_strncmp("exit", cmd, ft_strlen(cmd)))
		return (ft_exit(execinfo));
	return (1);
}

int	check_builtin_fd(t_execinfo *execinfo, int fd)
{
	char	*cmd;

	cmd = execinfo->cmd[0];
	if (!ft_strncmp("echo", cmd, ft_strlen(cmd)))
		return (ft_echo(execinfo->cmd, fd));
	else if (!ft_strncmp("pwd", cmd, ft_strlen(cmd)))
		return (ft_pwd());
	else if (!ft_strncmp("env", cmd, ft_strlen(cmd)))
		return (ft_env(execinfo, fd));
	return (1);
}
