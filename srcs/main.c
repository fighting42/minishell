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

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    char		*str;
	t_cmdline	cmdline;
	t_env		env;

	// 다팍씨 보세요
	// 1. 파싱할 때 envp말고 "env->value" 사용하기!
	// 2. $? 처리 추가하기! -> 전역변수 "g_status"
	// 3. cmdline 구조체에 token_cnt 필요 없어졌슴니다 히히 -> 지워도 됨!
	
	env.value = init_env(envp); 
    //while(1)
    {
        str = readline("minishell$ ");
		
		// 1순위는 달러처리(환경변수) -> envp에 있어
		// parse(str);
		//  return cmdline (token으로 연결, 명령어 세트로 짤라져있음)
		// exec(cmdline);

		cmdline = test_cmdline(); // test_cmdline() 자리에 parsing 함수 넣어주세용
		execute(&cmdline, &env);
		
		add_history(str);
        free(str);
    }
    return(0);
}
