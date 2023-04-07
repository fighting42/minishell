/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:11:00 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/07 18:33:44 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// envp 알아서 응요하세요ㅕ
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
		print_error("path error", 1);
	path = ft_split(envp[i] + 5, ':');
	return (path);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
    char *str;

    while(1)
    {
        str = readline("minishell> ");
		
		// 1순위는 달러처리(환경변수) -> envp에 있어
		// parse(str);
		//  return cmdline (token으로 연결, 명령어 세트로 짤라져있음) 
		// exec(cmdline); -> 실행!
        
		if (str)
            printf("%s\n", str);
        else            break ;
        add_history(str);
        free(str);
    }
    return(0);
}
