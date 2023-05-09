/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:16:45 by dapark            #+#    #+#             */
/*   Updated: 2023/05/09 22:58:45 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	quote_status(char c, int quote)
{
	if (c == '\'')
	{
		if (quote == 1)
			return (0);
		else if (quote == 2)
			return (2);
		else
			return (1);
	}
	else if (c == '\"')
	{
		if (quote == 2)
			return (0);
		else if (quote == 1)
			return (1);
		else
			return (2);
	}
	return (quote);
}

int	chk_whole_quote(char *str, int k)
{
	int	i;
	int	quote;

	quote = 0;
	i = k;
	while (str[i] != '\0')
	{
		quote = quote_status(str[i], quote);
		i++;
	}
	if (quote == 1 || quote == 2)
		return (quote);
	return (0);
}

int	chk_str_len(char *str)
{
	int	i;
	int	quote;
	int	flag_q;
	int	cnt_q;

	i = -1;
	quote = 0;
	cnt_q = 0;
	while (str[++i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if (quote != 0)
			flag_q = 1;
		if (flag_q == 1 && quote == 0)
		{
			cnt_q++;
			flag_q = 0;
		}
	}
	return (cnt_q);
}

void	make_ret_str(char *str, char *ret)
{
	int	i;
	int	quote;
	int	curr_q;
	int	flag_q;
	int	j;

	i = -1;
	j = 0;
	flag_q = 0;
	quote = 0;
	while (str[++i] != '\0')
	{
		quote = quote_status(str[i], quote);
		if (curr_q == quote)
		{
			ret[j] = str[i];
			j++;
		}
		if (quote != 0)
		{
			flag_q = 1;
			curr_q = quote;
		}
		if (flag_q == 1 && quote == 0)
		{
			curr_q = quote;
			flag_q = 0;
		}
	}
	ret[j] = '\0';
}

char	*remove_quote(char *str)
{
	int		cnt_q;
	char	*ret;
	int		len;

	len = strlen(str);
	cnt_q = chk_str_len(str);
	if (cnt_q == 0)
		return (str);
	ret = (char *)malloc(sizeof(char) * (len - (2 * cnt_q) + 1));
	make_ret_str(str, ret);
	return (ret);
}
