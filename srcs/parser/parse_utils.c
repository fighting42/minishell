/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:55:09 by dapark            #+#    #+#             */
/*   Updated: 2023/05/04 14:35:06 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(void)
{
	t_token	*ret;

	ret = malloc(sizeof(t_token) * 1);
	ret->pipe_flag = 0;
	return (ret);
}

void	append_token(t_token *head, t_token *curr, char *value, int type)
{
	t_token	*tmp;

	curr->value = value;
	if (type != -1)
	{
		if (type == 0)
			curr->type = STDIN;
		else if (type == 1)
			curr->type = STDOUT;
		else if (type == 2)
			curr->type = APPEND;
		else if (type == 3)
			curr->type = HEREDOC;
		else
			curr->type = COMMAND;
	}
	tmp = head;
	if (head == curr)
		head = curr;
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = curr;
		curr->next = NULL;
	}
}
