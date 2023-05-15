/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:57:51 by dapark            #+#    #+#             */
/*   Updated: 2023/05/15 17:06:33 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_case(char *str, t_parse *parse)
{
	int	i;
	int	ret_pipe;
	int	ret;

	i = -1;
	count_pipe(str, parse);
	ret = redirection_error(str, parse);
	if (ret == 2)
		return (2);
	if (pipe_error(str) == 1 || ret == 1)
		return (1);
	while (str[++i] != '\0')
	{
		while (check_sep(str[i], " ") == 1 && str[i] != '\0')
			i++;
		ret_pipe = consecutive_pipe_error(str, i);
		if (ret_pipe == -1)
			return (1);
		else
			i = ret_pipe;
	}
	if (pipe_the_end(str, parse) == 1)
		return (1);
	return (0);
}

int	redirection_case(t_parse *parse)
{
	if (parse->tmp[parse->i][parse->j] == '<')
	{
		if (redirection_stdin(parse) == 1)
			return (1);
	}
	else if (parse->tmp[parse->i][parse->j] == '>')
	{
		if (redirection_stdout(parse) == 1)
			return (1);
	}
	return (0);
}

int	parse_case(t_parse *parse, t_token *t_curr)
{
	int	ret;

	if (parse->tmp[parse->i][parse->j] == '|')
	{
		ret = check_pipe(parse, t_curr);
		if (ret != 2)
			return (ret);
	}
	else if (parse->tmp[parse->i][parse->j] == '<' || \
			parse->tmp[parse->i][parse->j] == '>')
	{
		if (redirection_case(parse) == 1)
			return (1);
	}
	else if (parse->tmp[parse->i][parse->j] == ' ')
		parse->j++;
	else
	{
		if (cmd_or_str(parse, t_curr) == 1)
			return (1);
		if (parse->tmp[parse->i + 1] != NULL)
			return (2);
	}
	return (3);
}

int	parse_loop(t_parse *parse, t_token *t_curr)
{
	int	ret;

	while (parse->tmp[++parse->i] != NULL)
	{
		parse->j = 0;
		while (parse->tmp[parse->i][parse->j] != '\0')
		{
			parse->quote = quote_status(parse->tmp[parse->i][parse->j], \
									parse->quote);
			ret = parse_case(parse, t_curr);
			if (ret == 0 || ret == 1)
				return (ret);
			else if (ret == 2)
			{
				if (parse->tmp[parse->i + 1][0] == ' ' \
					&& parse->tmp[parse->i + 2] == NULL)
					return (0);
				t_curr = create_token();
			}
			else
				continue ;
		}
	}
	return (0);
}

t_cmdline	*parsing(char *str, t_env *env)
{
	t_token		*t_curr;
	t_cmdline	*c_curr;
	t_parse		*parse;
	int			ret;

	if (error_quote(str) == 1)
		return (print_error(errmsg(TRUE, NULL, NULL, \
		"syntax error"), FALSE, 258));
	c_curr = malloc(sizeof(t_cmdline));
	t_curr = create_token();
	c_curr->token = t_curr;
	parse = malloc(sizeof(t_parse));
	init_parse(parse, str, env, c_curr);
	ret = error_case(str, parse);
	if (ret == 1 || ret == 2)
		return (end_program(parse, ret));
	ret = parse_loop(parse, t_curr);
	c_curr = parse->c_head;
	if (ret != 0)
		return (end_program(parse, 0));
	free_parse(parse);
	return (c_curr);
}
