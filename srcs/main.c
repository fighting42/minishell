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

void	test_leaks(void)
{
	system("leaks minishell");
}

int main(int argc, char **argv, char **envp)
{
    char		*str;
	t_cmdline	*cmdline;
	t_env		env;

	// atexit(test_leaks); // leaks test !
	(void)argc;
	(void)argv;
	env.value = init_env(envp);
	init_signal();
	while(1)
    {
        str = readline("minishell$ ");
		if (!str)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}
		else if (!ft_strncmp(str, "", 1))
			continue ;
		else
		{
			cmdline = parsing(str, &env);
			execute(cmdline, &env);
			add_history(str);
			free(str);
		}
	}
	free_env(&env);
    return(0);
}
