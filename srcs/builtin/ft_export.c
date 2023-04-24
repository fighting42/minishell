/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 17:06:54 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/24 23:07:19 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_execinfo *execinfo)
{
	int	cnt;
	int	i;

	cnt = 1;
	while (execinfo->cmd[cnt])
	{
		i = 0;
		while (execinfo->cmd[cnt][i])
		{
			if (!(ft_isalnum(execinfo->cmd[cnt][i]) || (i != 0 && execinfo->cmd[cnt][i] == '=')))
				print_error("bash: export", execinfo->cmd[cnt], NOT_VALID_ERR, 1); // cmd 따옴표 묶어서 출력
			i++;
		}
		cnt++;
	}
	add_env(execinfo, cnt - 1);
	return (0);
}

