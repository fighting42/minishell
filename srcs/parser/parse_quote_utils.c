/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:50:12 by daheepark         #+#    #+#             */
/*   Updated: 2023/05/09 23:51:10 by daheepark        ###   ########.fr       */
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
