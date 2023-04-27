/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:52:15 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/27 15:37:47 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_execinfo *execinfo)
{
	int		i;
	char	*cmd;
	char	*path;
	char	*ret;

	i = 0;
	cmd = execinfo->cmd[1];
	if ((cmd && cmd[i] == '~' && ft_strlen(cmd) == 1) || !cmd)
		path = get_env(execinfo->env->value, "HOME");
	else
		path = cmd;
	set_env(execinfo->env, "OLDPWD", get_env(execinfo->env->value, "PWD"));
	chdir(path);
	ret = getcwd(NULL, 0);
	set_env(execinfo->env, "PWD", ret);
	free(ret);
	return (0);
}
