/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:32:20 by dapark            #+#    #+#             */
/*   Updated: 2023/05/09 22:59:56 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_quote(char *str)
{
	if (chk_whole_quote(str, 0) == 1)
	{
		printf("%s", "ERROR: quote error\n");
		return (1);
	}
	return (0);
}

int	pipe_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		while (check_sep(str[i], " ") == 1)
			i++;
		if (str[i] == '|')
			return (1);
		else
			break ;
	}
	return (0);
}

int	pipe_the_end(char *str, t_parse *parse)
{
	int	i;
	int	quote;
	int	cnt;

	i = 0;
	cnt = 0;
	quote = 0;
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if (str[i] == '|' && quote == 0)
			cnt++;
		i++;
		if (cnt == parse->num_pipe)
		{
			while (check_sep(str[i], " ") == 1 && str[i] != '\0')
				i++;
			if (str[i] == '\0')
			{
				parse->last_pipe = 1;
				return (0);
			}
			return (0);
		}
	}
	return (0);
}

// int	command_error(char *str, t_parse *parse)
// {
	
// }

int	error_case(char *str, t_parse *parse)
{
	int	i;

	i = 0;
	count_pipe(str, parse);
	if (pipe_error(str) == 1)
		return (1);
	// 2. 말도 안되는 명령어들 -> 에러
	while (str[i] != '\0')
	{
		while (check_sep(str[i], " ") == 1 && str[i] != '\0')
			i++;
		if (check_sep(str[i], "<") == 1)
		{
			if (check_sep(str[i + 1], "<") == 1)
				i = i + 1;
			i++;
			while (check_sep(str[i], " ") == 1 && str[i] != '\0')
				i++;
			if (check_sep(str[i], "><|") == 1)
				return (1);
		}
		if (check_sep(str[i], ">") == 1)
		{
			if (check_sep(str[i + 1], ">") == 1)
				i = i + 1;
			i++;
			while (check_sep(str[i], " ") == 1 && str[i] != '\0')
				i++;
			if (check_sep(str[i], "><|") == 1)
				return (1);
		}
		if (check_sep(str[i], "|") == 1)
		{
			i++;
			while (check_sep(str[i], " ") == 1 && str[i] != '\0')
				i++;
			if (check_sep(str[i], "><|") == 1)
				return (1);
		}
		i++;
	}
	if (pipe_the_end(str, parse) == 0)
		return (0);
	// 4. echo $aa -> 이럴 때만 개행임 나머지는 그냥 무시
	// i = 0;
	// while (str[i] != '\0')
	// {
	// }
	return (0);
}
