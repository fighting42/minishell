/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:25:38 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/03 14:31:28 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_execinfo *execinfo)
{
	int	i;
	int	j;

	i = 1;
	while (execinfo->cmd[i])
	{
		j = 0;
		while (execinfo->cmd[i][j])
		{
			if (!(ft_isalnum(execinfo->cmd[i][j])))
				print_error("bash: unset", error_cmd(execinfo->cmd[i]), NOT_VALID_ERR, EXIT_Y, 1);
			j++;
		}
		del_env(execinfo->env, execinfo->cmd[i]);
		i++;
	}
	return (0);
}