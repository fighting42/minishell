/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:52:15 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/06 17:05:02 by yejinkim         ###   ########seoul.kr  */
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
	else
		path = cmd;
	set_env(pipeline->env, "OLDPWD", get_env(pipeline->env->value, "PWD"));
	chdir(path);
	ret = getcwd(NULL, 0);
	set_env(pipeline->env, "PWD", ret);
	free(ret);
	return (0);
}
