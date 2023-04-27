/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:06:54 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/27 16:09:22 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
				print_error("bash: export", error_cmd(execinfo->cmd[i]), NOT_VALID_ERR, 1);
			j++;
		}
		add_env(execinfo->env, execinfo->cmd[i]);
		i++;
	}
	return (0);
}

