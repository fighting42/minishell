/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:16:11 by dapark            #+#    #+#             */
/*   Updated: 2023/05/11 20:55:20 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection_stdin(t_parse *parse)
{
	if (parse->tmp[parse->i][parse->j + 1] == '<')
	{
		parse->type = HEREDOC;
		parse->j++;
	}
	else
		parse->type = STDIN;
	parse->j++;
	while (parse->tmp[parse->i][parse->j] != '\0')
	{
		while (parse->tmp[parse->i][parse->j] == ' ' && \
		parse->tmp[parse->i][parse->j] != '\0')
			parse->j++;
		if ((check_sep(parse->tmp[parse->i][parse->j], ">|<")) == 1)
			return (1);
	}
	return (0);
}

int	redirection_stdout(t_parse *parse)
{
	if (parse->tmp[parse->i][parse->j + 1] == '>')
	{
		parse->type = APPEND;
		parse->j++;
	}
	else
		parse->type = STDOUT;
	parse->j++;
	while (parse->tmp[parse->i][parse->j] != '\0')
	{
		while (parse->tmp[parse->i][parse->j] == ' ' && \
		parse->tmp[parse->i][parse->j] != '\0')
			parse->j++;
		if ((check_sep(parse->tmp[parse->i][parse->j], ">|<")) == 1)
			return (1);
	}
	return (0);
}

int	check_pipe(t_parse *parse, t_token *t_curr)
{
	t_curr->pipe_flag = 1;
	parse->cnt_pipe++;
	parse->j++;
	while (parse->tmp[parse->i][parse->j] == ' ' && \
		parse->tmp[parse->i][parse->j] != '\0')
		parse->j++;
	if (parse->tmp[parse->i][parse->j] == '<')
	{
		if (redirection_stdin(parse) == 1)
			return (1);
	}
	if (parse->tmp[parse->i][parse->j] == '>')
	{
		if (redirection_stdout(parse) == 1)
			return (1);
	}
	move_index_j(parse);
	return (2);
}

void	count_pipe(char *str, t_parse *parse)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if (str[i] == '|' && quote == 0)
			parse->num_pipe++;
		i++;
	}
}
