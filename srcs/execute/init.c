/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:06:56 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/05 22:19:18 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	append_pipeline(t_exec *exec, t_pipeline *pipeline)
{
	t_pipeline	*tmp;

	if (!exec->pipeline)
		exec->pipeline = pipeline;
	else
	{
		tmp = exec->pipeline;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = pipeline;
	}
}

void	append_redirct(t_pipeline *pipeline, t_token *token)
{
	t_redirct	*redirct;
	t_redirct	*tmp;

	redirct = malloc(sizeof(t_redirct));
	redirct->value = token->value;
	redirct->type = token->type;
	redirct->next = NULL;
	if (!pipeline->redirct)
		pipeline->redirct = redirct;
	else
	{
		tmp = pipeline->redirct;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redirct;
	}
}

void	split_cmdline(t_token *token, t_pipeline *pipeline, int cnt)
{
	int		i;

	pipeline->cmd = malloc(sizeof(char *) * (cnt + 1));
	pipeline->path = NULL;
	pipeline->redirct = NULL;
	pipeline->next = NULL;
	i = 0;
	while (i < cnt)
	{
		if (token->type != COMMAND)
		{
			append_redirct(pipeline, token);
			cnt--;
		}
		else
			pipeline->cmd[i++] = token->value;
		token = token->next;
	}
	pipeline->cmd[i] = NULL;
}

t_pipeline	*create_pipeline(t_cmdline *cmdline, int i, int prev, t_env *env)
{
	t_token		*token;
	t_pipeline	*pipeline;
	int			j;
	int			cnt;

	pipeline = malloc(sizeof(t_pipeline));
	pipeline->env = env;
	token = cmdline->token;
	cnt = i - prev;
	j = 0;
	while ((j++ < i - cnt) && prev && token->next)
		token = token->next;
	prev = i;
	split_cmdline(token, pipeline, cnt);
	return (pipeline);
}

void	check_cmdline(t_cmdline *cmdline, t_env *env, t_exec *exec)
{
	int		i;
	int		prev;
	t_token	*token;

	i = 1;
	prev = 0;
	token = cmdline->token;
	while (token)
	{
		if (token->type == HEREDOC)
			exec->heredoc_cnt++;
		if ((!token->next || (token->next && token->next->pipe_flag)) \
			&& token->value)
		{
			append_pipeline(exec, create_pipeline(cmdline, i, prev, env));
			prev = i;
			if (!token->next)
				break ;
			else
				exec->pipe_cnt++;
		}
		token = token->next;
		i++;
	}
}
