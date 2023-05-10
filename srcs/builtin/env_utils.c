/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:26:21 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/11 05:30:44 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**init_env(char **envp)
{
	int		i;
	char	**tmp;

	i = 0;
	while (envp[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (envp[++i])
		tmp[i] = ft_strdup(envp[i]);
	tmp[i] = NULL;
	return (tmp);
}

char	*get_env(char **env, char *var)
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
		return (NULL);
	free(var);
	return (env[i] + len);
}

void	set_env(t_env *env, char *var, char *value)
{
	int	i;
	int	len;

	i = 0;
	var = ft_strjoin(var, "=");
	len = ft_strlen(var);
	while (env->value[i])
	{
		if (!ft_strncmp(env->value[i], var, len))
			break ;
		i++;
	}
	if (!env->value[i])
	{
		if (!ft_strncmp("OLDPWD=", var, len))
			add_env(env, ft_strjoin(var, getcwd(NULL, 0)));
		return ;
	}
	env->value[i] = ft_strjoin(var, value);
}

void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->value[i])
		free(env->value[i++]);
	free(env->value);
}

int	update_env(t_exec *exec)
{
	int		i;
	int		j;
	int		len;
	char	**cmd;

	if (exec->pipe_cnt > 0)
		return (0);
	
	i = 0;
	cmd = exec->pipeline->cmd;
	while (cmd[i])
	{
		j = 0;
		len = 0;
		while (cmd[i][len] && cmd[i][len] != '=')
			len++;
		while (exec->pipeline->env->value[j])
		{
			if (!ft_strncmp(exec->pipeline->env->value[j], cmd[i], len))
				add_env(exec->pipeline->env, cmd[i]);
			j++;
		}
		i++;
	}
	return (0);
}
