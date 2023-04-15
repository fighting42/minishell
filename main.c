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

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
    char *str;
	t_cmdline cmdline;

    while(1)
    {
        str = readline("minishell> ");
		
		// 1순위는 달러처리(환경변수) -> envp에 있어
		// parse(str);
		//  return cmdline (token으로 연결, 명령어 세트로 짤라져있음)
		// exec(cmdline); -> 실행!
        
		//exec test
		t_token t1, t2, t3, t4, t5, t6, t7;
		t1.value = "echo";
		t1.type = COMMAND;
		t1.pipe_flag = 0;
		t1.next = &t2;
		
		t2.value = "test";
		t2.type = COMMAND;
		t2.pipe_flag = 0;
		t2.next = &t3;
		
		t3.value = "ls";
		t3.type = COMMAND;
		t3.pipe_flag = 1;
		t3.next = &t7;

		t7.value = "in";
		t7.type = STDIN;
		t7.pipe_flag = 1;
		t7.next = &t4;

		t4.value = "grep";
		t4.type = COMMAND;
		t4.pipe_flag = 0;
		t4.next = &t5;

		t5.value = "a";
		t5.type = COMMAND;
		t5.pipe_flag = 0;
		t5.next = &t6;

		t6.value = "test/out";
		t6.type = STDOUT;
		t6.pipe_flag = 0;
		t6.next = NULL;
		
		cmdline.token = &t1;
		cmdline.token_cnt = 7;
		//exec test
		execute(&cmdline, envp);

        add_history(str);
        free(str);
    }
    return(0);
}
