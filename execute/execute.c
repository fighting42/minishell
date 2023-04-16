/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:29:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/16 23:06:18 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	split_redirct(t_cmdinfo *cmdinfo, t_token *token)
{
	t_redirct	*redirct;
	t_redirct	*tmp;
	
	redirct = malloc(sizeof(t_redirct));
	redirct->value = token->value;
	redirct->type = token->type;
	redirct->next = NULL;
	if (!cmdinfo->redirct)
		cmdinfo->redirct = redirct;
	else
	{
		tmp = cmdinfo->redirct;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redirct;
	}
}

void	split_cmd(t_token *token, t_cmdinfo	*cmdinfo, int cnt)
{
	int 		i;

	cmdinfo->cmd = malloc(sizeof(char *) * (cnt + 1));
	cmdinfo->redirct = NULL;
	i = 0;
	while (i < cnt)
	{
		if (token->type == COMMAND)
		{
			cmdinfo->cmd[i] = token->value;
			i++;
		}
		else
		{
			split_redirct(cmdinfo, token);
			cnt--;
		}
		token = token->next;
	}
	cmdinfo->cmd[i] = NULL;
}

void	exec_cmd(t_cmdline *cmdline, int i, char **envp)
{
	static int	prev;
	t_token		*token;
	t_cmdinfo	*cmdinfo;
	int			j;
	int			cnt;

	j = 0;
	cnt = i - prev;
	token = cmdline->token;
	while ((j++ < i - cnt) && prev)
		token = token->next;
	prev = i;
	cmdinfo = malloc(sizeof(t_cmdinfo));
	cmdinfo->envp = envp;
	split_cmd(token, cmdinfo, cnt);
	// cmd_exec(cmdinfo);
	pipe_exec(cmdinfo);
	free(cmdinfo->cmd);
	free(cmdinfo);
}

void	execute(t_cmdline *cmdline, char **envp)
{
	t_token	*token;
	int		i;

	i = 1;
	// int in = STDIN_FILENO;
	// int out = STDOUT_FILENO;
	while (cmdline)
	{
		token = cmdline->token;
		while (token)
		{
			if (!token->next)
			{
				exec_cmd(cmdline, i, envp);
				break ;
			}
			else if (token->next->pipe_flag)
				exec_cmd(cmdline, i, envp);
			token = token->next;
			i++;
		}
		cmdline = cmdline->next;
	}
}
