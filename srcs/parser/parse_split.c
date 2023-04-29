/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 11:45:04 by dapark            #+#    #+#             */
/*   Updated: 2023/04/29 18:02:42 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			tmp[k] = make_str(str, " |<>", i, 0);//구분자 아닌 애들
			k++;
		}
		while (str[i] != '\0' && check_sep(str[i], " |<>") == 0)
			i++;
		if (str[i] != '\0')
		{
			tmp[k] = make_str(str, " |<>", i, 1); //구분자인 애들
			k++;
		}
	}
	tmp[k] = NULL;
	return (tmp);
}
