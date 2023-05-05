/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:06:54 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/05 22:20:10 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*error_cmd(char *cmd)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin("\'", cmd); // ` 이거..
	tmp2 = ft_strjoin(tmp2, "\'");
	free(tmp1);
	return (tmp2);
}

int	ft_export(t_execinfo *execinfo)
{
	int	i;
	int	j;

	i = 1;
	while (execinfo->cmd[i])
	{
		j = 0;
		while (execinfo->cmd[i][j])
		{
			if (!(ft_isalnum(execinfo->cmd[i][j]) || (i != 0 && execinfo->cmd[i][j] == '=')))
				print_error(errmsg(1, "export", error_cmd(execinfo->cmd[i]), NOT_VALID_ERR), EXIT_Y, 1);
			j++;
		}
		add_env(execinfo->env, execinfo->cmd[i]);
		i++;
	}
	return (0);
}
