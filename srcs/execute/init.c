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

t_execinfo	*append_exec(t_execinfo *head_exec, t_execinfo *new_exec)
{
	t_execinfo	*tmp;

	if (!head_exec)
		head_exec = new_exec;
	else
	{
		tmp = head_exec;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_exec;
	}
	return (head_exec);
}

void	append_redirct(t_execinfo *exec, t_token *token)
{
	t_redirct	*redirct;
	t_redirct	*tmp;

	redirct = malloc(sizeof(t_redirct));
	redirct->value = token->value;
	redirct->type = token->type;
	redirct->next = NULL;
	if (!exec->redirct)
		exec->redirct = redirct;
	else
	{
		tmp = exec->redirct;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redirct;
	}
}

void	check_cmd(t_token *token, t_execinfo *exec, int cnt)
{
	int	i;

	exec->cmd = malloc(sizeof(char *) * (cnt + 1));
	exec->redirct = NULL;
	i = 0;
	while (i < cnt)
	{
		if (token->type == COMMAND)
			exec->cmd[i++] = token->value;
		else
		{
			append_redirct(exec, token);
			cnt--;
		}
		token = token->next;
	}
	exec->cmd[i] = NULL;
}

t_execinfo	*create_exec(t_cmdline *cmdline, int i, int prev, t_env *env)
{
	t_token		*token;
	t_execinfo	*exec;
	int			j;
	int			cnt;

	exec = malloc(sizeof(t_execinfo));
	exec->env = env;
	exec->hd_cnt = '0';
	exec->next = NULL;
	cnt = i - prev;
	token = cmdline->token;
	j = 0;
	while ((j++ < i - cnt) && prev && token->next)
		token = token->next;
	prev = i;
	check_cmd(token, exec, cnt);
	return (exec);
}

t_execinfo	*init_execinfo(t_cmdline *cmdline, t_env *env)
{
	int			i;
	int			prev;
	int			pipe_cnt;
	t_token		*token;
	t_execinfo	*exec;

	i = 1;
	prev = 0;
	pipe_cnt = 0;
	exec = NULL;
	token = cmdline->token;
	while (token)
	{
		if (!token->next || (token->next && token->next->pipe_flag))
		{
			exec = append_exec(exec, create_exec(cmdline, i, prev, env));
			prev = i;
			if (!token->next)
				break ;
			else
				pipe_cnt++;
		}
		token = token->next;
		i++;
	}
	exec->pipe_cnt = pipe_cnt;
	return (exec);
}
