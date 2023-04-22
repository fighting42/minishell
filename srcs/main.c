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

char	**init_env(char **envp)
{
	int		i;
	char	**tmp;

	i = 0;
	while (envp[i])
		i++;
	tmp = malloc(sizeof(char *) * i);
	i = -1;
	while (envp[++i])
		tmp[i] = ft_strdup(envp[i]);
	tmp[i] = NULL;
	return (tmp);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    char		*str;
	t_cmdline	cmdline;
	t_env		env;

	env.value = init_env(envp); // 파싱할 때  env->value 사용하기!
    //while(1)
    {
        str = readline("minishell$ ");
		
		// 1순위는 달러처리(환경변수) -> envp에 있어
		// parse(str);
		//  return cmdline (token으로 연결, 명령어 세트로 짤라져있음)
		// exec(cmdline); -> 실행!
        
		// $? 처리 추가 ! -> g_exit_status

		cmdline = test_cmdline(); // cmdline test!
		execute(&cmdline, &env);
		
		add_history(str);
        free(str);
    }
    return(0);
}
