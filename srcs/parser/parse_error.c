/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:32:20 by dapark            #+#    #+#             */
/*   Updated: 2023/05/10 14:22:44 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_quote(char *str)
{
	if (chk_whole_quote(str, 0) != 0)
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

void	pipe_the_end(char *str, t_parse *parse)
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
				parse->last_pipe = 1;
			return ;
		}
	}
	return ;
}

int	redirection_pipe_error(char *str, int i)
{
	int	flag;

	flag = 0;
	if (check_sep(str[i], "<") == 1)
	{
		if (check_sep(str[i + 1], "<") == 1)
			i = i + 1;
		i++;
		flag = 1;
	}
	if (check_sep(str[i], ">") == 1)
	{
		if (check_sep(str[i + 1], ">") == 1)
			i = i + 1;
		i++;
		flag = 1;
	}
	if (check_sep(str[i], "|") == 1)
		i++;
	while (check_sep(str[i], " ") == 1 && str[i] != '\0')
		i++;
	if (check_sep(str[i], "><") == 1 && flag == 1)
		return (-1);
	if (check_sep(str[i], "|") == 1 && flag == 0)
		return (-1);
	return (i);
}

int	error_case(char *str, t_parse *parse)
{
	int	i;
	int	ret;

	i = -1;
	count_pipe(str, parse);
	if (pipe_error(str) == 1)
		return (1);
	while (str[++i] != '\0')
	{
		while (check_sep(str[i], " ") == 1 && str[i] != '\0')
			i++;
		ret = redirection_pipe_error(str, i);
		if (ret == -1)
			return (1);
		else
			i = ret;
	}
	pipe_the_end(str, parse);
	return (0);
}
