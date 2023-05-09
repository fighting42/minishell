/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:45:04 by dapark            #+#    #+#             */
/*   Updated: 2023/05/09 15:01:18 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	length_str(char *str, char *sep, int k, int flag)
{
	int	length;
	int	size;

	size = k;
	if (flag == 0)
	{
		while (str[size] != '\0' && check_sep(str[size], sep) == 0)
			size++;
	}
	else
	{
		while (str[size] != '\0' && check_sep(str[size], sep) == 1)
			size++;
	}
	length = size - k;
	return (length);
}

char	*make_str(char *str, char *sep, int k, int flag)
{
	char	*tmp;
	int		i;
	int		size;

	i = 0;
	size = length_str(str, sep, k, flag);
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
		if (str[i] != '\0')
			count++;
	}
	return (count);
}

char	**parse_split(char *str, int count)
{
	char	**tmp;
	int		i;
	int		k;

	i = 0;
	k = -1;
	tmp = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tmp)
		return (0);
	while (str[i] != '\0' && k < count)
	{
		while (str[i] != '\0' && check_sep(str[i], " |<>") == 1)
			i++;
		if (str[i] != '\0')
			tmp[++k] = make_str(str, " |<>", i, 0);
		while (str[i] != '\0' && check_sep(str[i], " |<>") == 0)
			i++;
		if (str[i] != '\0')
			tmp[++k] = make_str(str, " |<>", i, 1);
	}
	tmp[++k] = NULL;
	return (tmp);
}

int	is_not_ok_sep(char *str, char *sep)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (sep[j] != '\0')
		{
			if (str[i] == sep[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
