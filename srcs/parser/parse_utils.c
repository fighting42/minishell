/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:55:09 by dapark            #+#    #+#             */
/*   Updated: 2023/05/08 20:53:22 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(void)
{
	t_token	*ret;

	ret = (t_token *)malloc(sizeof(t_token));
	ret->pipe_flag = 0;
	ret->next = NULL;
	return (ret);
}

void	append_token(t_token *head, t_token *curr, char *value, int type)
{
	t_token	*tmp;

	curr->value = value;
	printf("값 확인 :: %s\n", curr->value);
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

void	move_index_j(t_parse *parse)
{
	while (parse->tmp[parse->i][parse->j] != '\0')
	{
		parse->quote = quote_status(parse->tmp[parse->i][parse->j], parse->quote);
		parse->j++;
	}
}