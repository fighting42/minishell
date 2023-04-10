/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 16:29:30 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/10 23:42:29 by yejinkim         ###   ########seoul.kr  */
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

void	cmd_exec(char *cmd_path, char **cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		printf("fork error\n");
	else if (pid == 0)
	{
		if (execve(cmd_path, cmd, envp) == -1)
			printf("command not found\n");
	}
	else
		waitpid(pid, &status, 0);
}

void	execute(t_cmdline *cmdline, char **envp)
{
	t_token	*token;
	char	**cmd;
	char	*cmd_path;

	while (cmdline) 
	{
		token = cmdline->token;
		if (token->type == COMMAND)
		{
			// test
			cmd = malloc(sizeof(char *) * 2);
			cmd[0] = token->value;
			cmd[1] = NULL;
			// test
			cmd_path = find_path(cmd, pars_envp(envp));
			cmd_exec(cmd_path, cmd, envp);
		}
		cmdline = cmdline->next;
	}
}