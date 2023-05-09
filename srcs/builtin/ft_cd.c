/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:52:15 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/10 05:39:08 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_pipeline *pipeline)
{
	int		i;
	char	*cmd;
	char	*path;
	char	*ret;

	i = 0;
	cmd = pipeline->cmd[1];
	if ((cmd && cmd[i] == '~' && ft_strlen(cmd) == 1) || !cmd)
		path = get_env(pipeline->env->value, "HOME");
	else if (cmd[i] == '-' && ft_strlen(cmd) == 1)
	{
		path = get_env(pipeline->env->value, "OLDPWD");
		if (!path)
		{
			print_error(errmsg(TRUE, "cd", NULL, "OLDPWD not set"), FALSE, 1);
			return (0);
		}
	}
	else
		path = cmd;
	set_env(pipeline->env, "OLDPWD", get_env(pipeline->env->value, "PWD"));
	if (chdir(path) < 0)
	{
		print_error(errmsg(TRUE, "cd", pipeline->cmd[1], "No such file or directory"), FALSE, 1);
		return (0);
	}
	ret = getcwd(NULL, 0);
	set_env(pipeline->env, "PWD", ret);
	free(ret);
	return (0);
}
