/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:45:20 by dapark            #+#    #+#             */
/*   Updated: 2023/04/15 21:13:16 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *remove_quote(char *str)
{
	int	i;
	int	j;
	int	len;
	int	cnt;
	int chk_cnt;
	char *ret;

	i = 0;
	j = 0;
	cnt = 0;
	chk_cnt = 0;
	len = strlen(str);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			cnt++;
	}
	if (cnt == 0)
		return (str);
	ret = (char *)malloc(sizeof(char) * (len - 1));
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			chk_cnt++;
			if (chk_cnt != 1 || chk_cnt != cnt)
				ret[j] = str[i];
		}
		ret[j] = str[i];
		j++;
		i++;
	}
	return (ret);
}

char	*