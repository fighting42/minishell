/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:16:11 by dapark            #+#    #+#             */
/*   Updated: 2023/05/06 21:57:11 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection_stdin(t_parse *parse)
{
	if (parse->tmp[parse->i][parse->j + 1] == '<')
		parse->type = HEREDOC;
	else
		parse->type = STDIN;
	while (check_sep(parse->tmp[parse->i + 1][0], " |<>") == 1)
	{
		if ((is_not_ok_sep(parse->tmp[parse->i + 1], "|><")) == 1)
			return (1);
	}
	move_index_j(parse);
	return (0);
}

int	redirection_stdout(t_parse *parse)
{
	if (parse->tmp[parse->i][parse->j + 1] == '>')
		parse->type = APPEND;
	else
		parse->type = STDOUT;
	while (check_sep(parse->tmp[parse->i + 1][0], " |<>") == 1)
	{
		if ((is_not_ok_sep(parse->tmp[parse->i + 1], "|><")) == 1)
			return (1);
	}
	move_index_j(parse);
	return (0);
}

void	check_pipe(t_parse *parse, t_token *t_curr)
{
	t_curr->pipe_flag = 1;
	move_index_j(parse);
}