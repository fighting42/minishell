/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:55:09 by dapark            #+#    #+#             */
/*   Updated: 2023/04/28 17:16:56 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token()
{
	t_token	*ret;

	ret = malloc(sizeof(t_token) * 1);
	ret->pipe_flag = 0;
	return (ret);
}

void	append_token(t_token *head, t_token *curr, char *value, int *r_flag) // value값 바로 넣을 수 없나?
{
	t_token	*tmp;

	curr->value = value;
	if (r_flag != -1)
	{
		if (r_flag == 0)
			curr->type = STDIN;
		else if (r_flag == 1)
			curr->type = STDOUT;
		else if (r_flag == 2)
			curr->type = APPEND;
		else if (r_flag == 3)
			curr->type = HEREDOC;
		else
			curr->type = COMMAND;
		r_flag = -1 ;
	}
	tmp = head;
	while (tmp)
		tmp = tmp->next;
	tmp = curr;
	curr->next = NULL;
}
