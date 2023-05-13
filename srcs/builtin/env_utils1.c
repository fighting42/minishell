/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 21:26:21 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/13 17:43:48 by yejinkim         ###   ########seoul.kr  */
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

char	*get_env(char **env, char *var)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(var, "=");
	len = ft_strlen(tmp);
	while (env[i])
	{
		if (!ft_strncmp(env[i], tmp, len))
			break ;
		i++;
	}
	free(tmp);
	if (!env[i])
		return (NULL);
	return (env[i] + len);
}

void	set_env(t_env *env, char *var, char *value)
{
	int		i;
	int		len;
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin(var, "=");
	len = ft_strlen(tmp);
	i = get_env_i(env->value, var);
	if (i < 0)
	{
		if (!ft_strncmp("OLDPWD=", tmp, len))
		{
			tmp2 = ft_strjoin(tmp, getcwd(NULL, 0));
			add_env(env, tmp2);
			free(tmp2);
		}
		free(tmp);
		return ;
	}
	free(env->value[i]);
	env->value[i] = ft_strjoin(tmp, value);
	free(tmp);
}

void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (env->value[i])
		free(env->value[i++]);
	free(env);
}
