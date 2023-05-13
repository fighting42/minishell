/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:44:23 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/13 22:50:56 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_join(t_join *join)
{
	free(join->ret);
	free(join);
}

void	free_cmdline(t_cmdline *cmdline)
{
	t_token	*token_f;
	t_token	*token_n;

	token_f = cmdline->token;
	token_n = cmdline->token;
	while (token_n != NULL)
	{
		token_f = token_n;
		token_n = token_f->next;
		if (token_f->value != NULL)
			free(token_f->value);
		free(token_f);
	}
	free(cmdline);
}
