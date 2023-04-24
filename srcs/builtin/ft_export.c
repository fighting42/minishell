/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:06:54 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/24 17:30:56 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_execinfo *execinfo)
{
	int		cnt;
	int		i;
	char	**new_env;

	cnt = 0;
	while (execinfo->env->value[cnt])
		cnt++;
	new_env = malloc(sizeof(char *) * (cnt + 1));
	i = 0;
	while (i < cnt)
	{
		new_env[i] = ft_strdup(execinfo->env->value[i]);
		free(execinfo->env->value[i]);
		i++;
	}
	new_env[i++] = execinfo->cmd[1];
	new_env[i] = NULL;
	free(execinfo->env->value);
	execinfo->env->value = new_env;
	return (0);
}

