/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:11:00 by yejinkim          #+#    #+#             */
/*   Updated: 2023/04/03 16:35:35 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

# include <readline/readline.h>
# include <readline/history.h>

# include <stdio.h>
# include <stdlib.h>

int main(void)
{
    char *str;
    while(1)
    {
        str = readline("minishell$ ");
        if (str)
            printf("%s\n", str);
        else
            break ;

        add_history(str);
        free(str);
    }
    return(0);
}