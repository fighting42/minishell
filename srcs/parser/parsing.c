/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:57:51 by dapark            #+#    #+#             */
/*   Updated: 2023/05/09 16:32:10 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int	g_status = 0;

int	parse_case(t_parse *parse, t_token *t_curr)
{
	if (parse->tmp[parse->i][parse->j] == '|')
	{
		if (check_pipe(parse, t_curr) == 1)
			return (0);
		return (3);
	}
	else if (parse->tmp[parse->i][parse->j] == '<')
	{
		if (redirection_stdin(parse) == 1)
			return (1);
		return (3);
	}
	else if (parse->tmp[parse->i][parse->j] == '>')
	{
		if (redirection_stdout(parse) == 1)
			return (1);
		return (3);
	}
	else if (parse->tmp[parse->i][parse->j] == ' ')
	{
		parse->j++;
		return (3);
	}
	else
	{
		if (cmd_or_str(parse, t_curr) == 1)
			return (1);
		if (parse->tmp[parse->i + 1] != NULL)
			return (2);
		return (3);
	}
}

t_cmdline	*parsing(char *str, t_env *env)
{
	t_token		*t_curr;
	t_cmdline	*c_curr;
	t_parse		*parse;
	int			ret;

	if (error_quote(str) == 1)
		return (0);
	c_curr = malloc(sizeof(t_cmdline));
	t_curr = create_token();
	c_curr->token = t_curr;
	parse = malloc(sizeof(t_parse));
	init_parse(parse, str, env, c_curr);
	if (error_case(str, parse) == 1)
		return (0);
	while (parse->tmp[parse->i] != NULL)
	{
		parse->j = 0;
		while (parse->tmp[parse->i][parse->j] != '\0')
		{
			parse->quote = quote_status(parse->tmp[parse->i][parse->j], parse->quote);
			ret = parse_case(parse, t_curr);
			if (ret == 0)
				return (parse->c_head);
			else if (ret == 1)
				return (0);
			else if (ret == 2)
				t_curr = create_token();
			else
				continue ;
		}
		parse->i++;
	}
	return (parse->c_head);
}

int main(int argc, char **argv, char **envp)
{
	t_cmdline *str;
	t_token *prt;
	t_env temp;

	temp.value = envp;
	(void)argc;
	(void)argv;

	char *tmp = "cat |";
	printf("%s\n", tmp);
	
	g_status = 0;
	str = parsing(tmp, &temp);
	if (str == NULL)
	{
		printf("error\n");
		return (0);
	}
	prt = str->token;
	while (prt != NULL)
	{
		printf("value: %s / type: %d / pipe_flag: %d\n", prt->value, prt->type, prt->pipe_flag);
		prt = prt->next;
	}	
	return (0);
}
