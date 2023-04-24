/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:52:15 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/24 20:39:21 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_value(char **env, char *var)
{
	int	i;
	int	len;

	i = 0;
	var = ft_strjoin(var, "=");
	len = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, len))
			break ;
		i++;
	}
	if (!env[i])
		return (NULL); // error
	free(var);
	return (env[i] + len);
}

void	set_value(char **env, char *var, char *value)
{
	int	i;
	int	len;

	i = 0;
	var = ft_strjoin(var, "=");
	len = ft_strlen(var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], var, len))
			break ;
		i++;
	}
	// OLDPWD 없을때도 있나 ?
	if (!env[i])
		return ; // error
	free(var);
	// free(env[i]);
	env[i] = ft_strjoin(var, value);
}

int	ft_cd(t_execinfo *execinfo)
{
	int		i;
	char	*cmd;
	char	*path;
	char	**env;
	char	*ret;

	i = 0;
	cmd = execinfo->cmd[1];
	env = execinfo->env->value;
	if ((cmd && cmd[i] == '~' && ft_strlen(cmd) == 1) || !cmd)
		path = get_value(env, "HOME");
	else
		path = cmd;
	set_value(env, "OLDPWD", get_value(env, "PWD"));
	chdir(path);
	ret = getcwd(NULL, 0);
	set_value(env, "PWD", ret);
	// printf("pwd: %s\npwd: %s (minishell)\n", ret, get_value(execinfo->env->value, "PWD"));
	free(ret);
	return (0);
}
