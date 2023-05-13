/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:52:15 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/13 17:14:57 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*set_path(char *cmd, char **env)
{
	char	*path;

	if ((cmd && cmd[0] == '~' && ft_strlen(cmd) == 1) || !cmd)
		path = get_env(env, "HOME");
	else if (cmd[0] == '-' && ft_strlen(cmd) == 1)
	{
		path = get_env(env, "OLDPWD");
		if (!path)
		{
			print_error(errmsg(TRUE, "cd", NULL, "OLDPWD not set"), FALSE, 1);
			return (NULL);
		}
	}
	else
		path = cmd;
	return (path);
}

int	ft_cd(t_pipeline *pipeline)
{
	char	*path;
	char	*ret;

	path = set_path(pipeline->cmd[1], pipeline->env->value);
	if (!path)
		return (0);
	set_env(pipeline->env, "OLDPWD", get_env(pipeline->env->value, "PWD"));
	if (chdir(path) < 0)
	{
		print_error(errmsg(TRUE, "cd", pipeline->cmd[1], \
			"No such file or directory"), FALSE, 1);
		return (0);
	}
	ret = getcwd(NULL, 0);
	if (!ret)
		print_error(errmsg(TRUE, "cd", NULL, \
			"No such file or directory"), TRUE, 1);
	set_env(pipeline->env, "PWD", ret);
	free(ret);
	return (0);
}
