/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:29:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/15 22:54:38 by yejinkim         ###   ########seoul.kr  */
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

void	split_cmd(t_cmdline *cmdline, int i, char **envp)
{
	static int	prev;
	t_token		*token;
	t_cmdinfo	cmdinfo;
	t_redirect	*redirect;
	int			j;
	int			cnt;

	j = 0;
	token = cmdline->token;
	cnt = i - prev;
	while ((j++ < i - cnt) && prev)
		token = token->next;
	prev = i;
	cmdinfo.cmd = malloc(sizeof(char *) * (cnt + 1));
	j = 0;
	cmdinfo.redirect = NULL;
	while (j < cnt)
	{
		if (token->type != COMMAND)
		{
			redirect = malloc(sizeof(t_redirect));
			redirect->token = token;
			redirect->next = NULL;
			if (!cmdinfo.redirect)
				cmdinfo.redirect = redirect;
			else
			{
				t_redirect *tmp = cmdinfo.redirect;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = redirect;
			}
			cnt--; // 이게 문제인듯
			continue ;
		}
		cmdinfo.cmd[j] = token->value;
		token = token->next;
		j++;
	}
	cmdinfo.cmd[j] = NULL;
	cmdinfo.path = find_path(cmdinfo.cmd, pars_envp(envp));
	if (cmdinfo.redirect)
		printf("%s, redirect: %s\n", cmdinfo.cmd[0], cmdinfo.redirect->token->value);
	else
		printf("%s\n", cmdinfo.cmd[0]);
	//cmd_exec(&cmdinfo, envp);
	free(cmdinfo.cmd);
}

void	execute(t_cmdline *cmdline, char **envp)
{
	t_token	*token;
	int		i;

	i = 1;
	while (cmdline)
	{
		token = cmdline->token;
		while (token)
		{
			if (!token->next)
			{
				split_cmd(cmdline, i, envp);
				break ;
			}
			else if (token->next->pipe_flag)
				split_cmd(cmdline, i, envp);
			token = token->next;
			i++;
		}
		cmdline = cmdline->next;
	}
}
