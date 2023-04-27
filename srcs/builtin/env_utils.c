/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:26:21 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/27 15:50:07 by yejinkim         ###   ########seoul.kr  */
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

int	get_env_i(char **env, char *var)
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
		return (-1);
	free(var);
	return (i);
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
	free(var);
	// free(env->value[i]);
	env->value[i] = ft_strjoin(var, value);
}

char	**init_add_env(char **env)
{
	int		i;
	char	**tmp;

	i = 0;
	while (env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (env[++i])
		tmp[i] = ft_strdup(env[i]);
	tmp[i++] = NULL;
	tmp[i] = NULL;
	return (tmp);
}

void	add_env(t_env *env, char *value)
{
	int		i;
	char	**new_env;
	
	if (!ft_strchr(value, '='))
		return ;
	new_env = init_add_env(env->value);
	i = 0;
	while (new_env[i])
		free(env->value[i++]);
	new_env[i] = ft_strdup(value);
	free(env->value);
	env->value = new_env;
}

void	del_env(t_env *env, char *var)
{
	int i;

	i = get_env_i(env->value, var);
	while (env->value[i + 1])
	{
		env->value[i] = env->value[i + 1];
		i++;
	}
	env->value[i] = NULL;
	free(env->value[i]);
}