/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:45:04 by dapark            #+#    #+#             */
/*   Updated: 2023/04/12 12:00:46 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../minishell.h"

int	check_sep(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i] != '\0')
	{
		if (sep[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	length_str(char *str, char *sep, int k)
{
	int	length;
	int	size;

	size = k;
	while (str[size] != '\0' && check_sep(str[size], sep) != 1)
		size++;
	length = size - k;
	return (length);
}

char	*make_str(char *str, char *sep, int k)
{
	char	*tmp;
	int		i;
	int		size;

	i = 0;
	size = length_str(str, sep, k);
	tmp = (char *)malloc(sizeof(char) * (size + 1));
	if (!tmp)
		return (0);
	while (i < size)
	{
		tmp[i] = str[k];
		i++;
		k++;
	}
	tmp[i] = '\0';
	return (tmp);
}

int	count_str(char *str, char *sep)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && check_sep(str[i], sep) == 1)
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && check_sep(str[i], sep) == 0)
			i++;
	}
	return (count);
}

char	**parse_split(char *str, int count, t_dollar *env_var)
{
	char	**tmp;
	int		i;
	int		k;

	i = 0;
	k = 0;
	tmp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tmp)
		return (0);
	while (str[i] != '\0' && k < count)
	{
		while (str[i] != '\0' && check_sep(str[i], " |<>") == 1)
			i++;
		if (str[i] != '\0')
		{
			tmp[k] = make_str(str, " |<>", i); //구분자도 같이 넣어야돼
			k++;
		}
		while (str[i] != '\0' && check_sep(str[i], " |<>") == 0)
			i++;
	}
	tmp[k] = 0;
	return (tmp);
}
