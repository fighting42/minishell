/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:39:52 by yejinkim          #+#    #+#             */
/*   Updated: 2022/07/18 14:13:40 by yejinkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_len(char const *s, unsigned int start, size_t len)
{
	if (ft_strlen(s) - start < len)
		return (ft_strlen(s) - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*tmp;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen(s) <= start)
	{
		tmp = (char *)malloc(sizeof(char));
		if (!tmp)
			return (0);
		tmp[0] = '\0';
		return (tmp);
	}
	tmp = (char *)malloc(sizeof(char) * (check_len(s, start, len) + 1));
	if (!tmp)
		return (0);
	while (i < len && s[start + i])
	{
		tmp[i] = s[start + i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
