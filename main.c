/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:11:00 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/10 23:11:20 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
        
		//exec
		t_cmdline cmdline;
		cmdline.cmd = ft_split(str, ' ');
		cmdline.type = COMMAND;
		cmdline.next = NULL;
		execute(&cmdline, envp);

        add_history(str);
        free(str);
    }
    return(0);
}
