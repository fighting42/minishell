/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:57:51 by dapark            #+#    #+#             */
/*   Updated: 2023/05/07 02:34:00 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int	g_status = 0;
t_cmdline	*parsing(char *str, t_env *env)
{
	t_token		*t_curr;
	t_cmdline	*c_curr;
	t_parse		*parse;

	char		*cmd;
	int			quote = 0;
	int			cnt_dlr = 0;

	if (error_case(str) == 1)
		return (0);
	c_curr = malloc(sizeof(t_cmdline));
	t_curr = create_token();
	c_curr->token = t_curr;
	parse = malloc(sizeof(t_parse));
	init_parse(parse, str, env, c_curr);

	printf("quote %lu %p\n", sizeof(parse->quote), &parse->quote);
	printf("i %lu %p\n", sizeof(parse->i),&parse->i);
	printf("j %lu %p\n", sizeof(parse->j),&parse->j);
	printf("dallar_index %lu %p\n", sizeof(parse->dollar_index),&parse->dollar_index);
	printf("type %lu %p\n", sizeof(parse->type),&parse->type);
	printf("env_var %lu %p\n", sizeof(parse->env_var),&parse->env_var);
	printf("c_head %lu %p\n", sizeof(parse->c_head),&parse->c_head);
	printf("tmp %lu %p\n", sizeof(parse->tmp),&parse->tmp);

	for (parse->i = 0; parse->tmp[parse->i] != NULL; parse->i++)
		printf("split : %s\n", parse->tmp[parse->i]);
		
	parse->i = 0;
	while (parse->tmp[parse->i] != NULL)
	{
		parse->j = 0;
		while (parse->tmp[parse->i][parse->j] != '\0')
		{
			parse->quote = quote_status(parse->tmp[parse->i][parse->j], parse->quote);
			if (parse->tmp[parse->i][parse->j] == '|')
				check_pipe(parse, t_curr);
			else if (parse->tmp[parse->i][parse->j] == '<')
			{
				if (redirection_stdin(parse) == 1)
					return (0);
			}
			else if (parse->tmp[parse->i][parse->j] == '>')
			{
				if (redirection_stdout(parse) == 1)
					return (0);
			}
			else if (parse->tmp[parse->i][parse->j] == ' ')
				parse->j++;
			else
			{
				if (cmd_or_str(parse, t_curr) == 1)
					return (0);
				if (parse->tmp[parse->i + 1] != NULL)
					t_curr = create_token();
			}
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

	char *tmp = "echo \"$USER sdfe asdf\"";
	printf("%s\n", tmp);
	
	g_status = 0;
	str = parsing(tmp, &temp);
	prt = str->token;
	while (prt != NULL)
	{
		printf("value: %s / type: %d / pipe_flag: %d\n", prt->value, prt->type, prt->pipe_flag);
		prt = prt->next;
	}	
	return (0);
}
