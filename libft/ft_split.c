/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 20:56:43 by yejinkim          #+#    #+#             */
/*   Updated: 2022/07/20 11:13:12 by yejinkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(const char *str, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			cnt++;
		i++;
	}
	return (cnt);
}

static int	check_arr(char **arr, int idx)
{
	int	i;

	i = 0;
	if (!arr[idx])
	{
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
		free(arr);
		return (1);
	}
	else
		return (0);
}

static void	malloc_word(char **arr, char const *str, char c)
{
	int	idx;
	int	i;
	int	j;

	idx = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			i++;
		else
		{
			j = 1;
			while (str[i + j] != c && str[i + j])
				j++;
			arr[idx] = (char *)malloc(sizeof(char) * (j + 1));
			if (check_arr(arr, idx))
				return ;
			ft_strlcpy(arr[idx], &str[i], j + 1);
			idx++;
			i += j;
		}
	}
	arr[idx] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (0);
	arr = (char **)malloc(sizeof(char *) * (count_word(s, c) + 1));
	if (!arr)
		return (0);
	malloc_word(arr, s, c);
	return (arr);
}
