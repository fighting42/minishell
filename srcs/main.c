/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:11:00 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/15 22:51:02 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_status = 0;

void	parsing_execute(t_cmdline *cmdline, char *line, t_env *env)
{
	cmdline = parsing(line, env);
	if (cmdline)
		execute(cmdline, env);
	add_history(line);
	free(line);
	if (cmdline != NULL)
		free_cmdline(cmdline);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_cmdline	*cmdline;
	t_env		env;

	(void)argc;
	(void)argv;
	env.value = init_env(envp);
	init_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			signal_ctrl_d();
		else if (!ft_strncmp(line, "", 1))
		{
			free(line);
			continue ;
		}
		else
			parsing_execute(cmdline, line, &env);
	}
	free_env(&env);
	return (0);
}
