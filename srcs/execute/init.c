/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:06:56 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/21 18:09:47 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**pars_envp(char **envp)
{
	char	**path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!envp[i])
		printf("path error\n");
	path = ft_split(envp[i] + 5, ':');
	return (path);
}

char	*find_path(char **cmd, char **envp_path)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (envp_path[i])
	{
		if (cmd[0][0] == '/')
			path = cmd[0];
		else
		{
			tmp = ft_strjoin(envp_path[i], "/");
			path = ft_strjoin(tmp, cmd[0]);
			free(tmp);
		}
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	split_redirct(t_execinfo *execinfo, t_token *token)
{
	t_redirct	*redirct;
	t_redirct	*tmp;

	redirct = malloc(sizeof(t_redirct));
	redirct->value = token->value;
	redirct->type = token->type;
	redirct->next = NULL;
	if (!execinfo->redirct)
		execinfo->redirct = redirct;
	else
	{
		tmp = execinfo->redirct;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redirct;
	}
}

void	split_cmd(t_token *token, t_execinfo *execinfo, int cnt)
{
	int	i;

	execinfo->cmd = malloc(sizeof(char *) * (cnt + 1));
	execinfo->redirct = NULL;
	i = 0;
	while (i < cnt)
	{
		if (token->type == COMMAND)
			execinfo->cmd[i++] = token->value;
		else
		{
			split_redirct(execinfo, token);
			cnt--;
		}
		token = token->next;
	}
	execinfo->cmd[i] = NULL;
}

t_execinfo	*append_info(t_execinfo *head, t_execinfo *curr)
{
	t_execinfo	*tmp;

	if (!head)
		head = curr;
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = curr;
	}
	return (head);
}

t_execinfo	*split_execinfo(t_cmdline *cmdline, int i, char **envp)
{
	static int	prev;
	t_token		*token;
	t_execinfo	*execinfo;
	int			j;
	int			cnt;

	j = 0;
	cnt = i - prev;
	token = cmdline->token;
	while ((j++ < i - cnt) && prev)
		token = token->next;
	prev = i;
	execinfo = malloc(sizeof(t_execinfo));
	execinfo->envp = envp;
	execinfo->hd_cnt = '0';
	execinfo->next = NULL;
	split_cmd(token, execinfo, cnt);
	return (execinfo);
}

t_execinfo	*init_execinfo(t_cmdline *cmdline, char **envp)
{
	int			i;
	int			pipe_cnt;
	t_token		*token;
	t_execinfo	*execinfo;

	i = 1;
	pipe_cnt = 0;
	execinfo = NULL;
	while (cmdline)
	{
		token = cmdline->token;
		while (token)
		{
			if (!token->next)
			{
				execinfo = append_info(execinfo, \
					split_execinfo(cmdline, i, envp));
				break ;
			}
			else if (token->next->pipe_flag)
			{
				execinfo = append_info(execinfo, \
					split_execinfo(cmdline, i, envp));
				pipe_cnt++;
			}
			token = token->next;
			i++;
		}
		cmdline = cmdline->next;
	}
	execinfo->pipe_cnt = pipe_cnt;
	return (execinfo);
}
