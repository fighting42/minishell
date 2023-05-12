/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:32:20 by dapark            #+#    #+#             */
/*   Updated: 2023/05/12 17:44:40 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	error_quote(char *str)
{
	if (chk_whole_quote(str, 0) != 0)
		return (1);
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
		if (cnt == parse->num_pipe && parse->num_pipe != 0)
		{
			while (check_sep(str[i], " ") == 1 && str[i] != '\0')
				i++;
			if (str[i] == '\0')
				return (1);
			return (0);
		}
	}
	return (0);
}

int	consecutive_pipe_error(char *str, int i)
{
	if (check_sep(str[i], "|") == 1)
		i++;
	while (check_sep(str[i], " ") == 1 && str[i] != '\0')
		i++;
	if (check_sep(str[i], "|") == 1)
		return (-1);
	return (i);
}

int	redirection_error(char *str)
{
	int	i;
	int	flag;

	i = -1;
	flag = 0;
	while (str[++i] != '\0')
	{
		while (check_sep(str[i], " ") == 1 && str[i] != '\0')
			i++;
		if (check_sep(str[i], "><") == 1)
		{
			i++;
			if (check_sep(str[i], "><") == 1)
				i++;
			flag = 1;
		}
		while (check_sep(str[i], " ") == 1 && str[i] != '\0')
			i++;
		if ((str[i] == '\0' || str[i] == '|') && flag == 1)
			return (1);
		flag = 0;
	}
	return (0);
}
