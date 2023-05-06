/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 17:57:51 by dapark            #+#    #+#             */
/*   Updated: 2023/05/06 23:04:41 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
int	g_status = 0;
t_cmdline	*parsing(char *str, t_env *env)
{
	t_token		*t_curr;
	t_parse		*parse;

	char		*cmd;
	int			quote = 0;
	int			cnt_dlr = 0;

	if (error_case(str) == 1)
		return (0);
	parse = malloc(sizeof(parse));
	init_parse(parse, str, env);
	t_curr = parse->t_head;
	parse->c_head->token = parse->t_head;

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
				{
					t_curr = create_token();
					printf("NULL check : %d\n", parse->i + 1);
				}
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

	char *tmp = "echo \"$USER sdfeasdf\"";
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
