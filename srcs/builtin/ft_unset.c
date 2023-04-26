/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:25:38 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/24 23:33:01 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_execinfo *execinfo)
{
	int	cnt;
	int	i;

	cnt = 1;
	while (execinfo->cmd[cnt])
	{
		i = 0;
		while (execinfo->cmd[cnt][i])
		{
			if (!(ft_isalnum(execinfo->cmd[cnt][i])))
				print_error("bash: unset", execinfo->cmd[cnt], NOT_VALID_ERR, 1); // cmd 따옴표 묶어서 출력
			i++;
		}
		cnt++;
	}
	del_env(execinfo, cnt - 1);
	return (0);
}