/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 19:47:00 by yejinkim          #+#    #+#             */
/*   Updated: 2022/08/04 15:26:50 by yejinkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*tmp;

	i = 0;
	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!tmp)
		return (0);
	while (i < len1)
	{
		tmp[i] = s1[i];
		i++;
	}
	while (i - len1 < len2)
	{
		tmp[i] = s2[i - len1];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}
