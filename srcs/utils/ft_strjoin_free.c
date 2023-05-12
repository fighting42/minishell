/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapark <dapark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 23:17:00 by dapark            #+#    #+#             */
/*   Updated: 2023/05/12 18:59:01 by dapark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_free_all(char *s1, char *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*tmp;

	i = -1;
	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!tmp)
		return (0);
	while (++i < len1)
		tmp[i] = s1[i];
	while (i - len1 < len2)
	{
		tmp[i] = s2[i - len1];
		i++;
	}
	tmp[i] = '\0';
	free(s1);
	free(s2);
	return (tmp);
}

char	*ft_strjoin_free_front(char *s1, char *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*tmp;

	i = -1;
	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!tmp)
		return (0);
	while (++i < len1)
		tmp[i] = s1[i];
	while (i - len1 < len2)
	{
		tmp[i] = s2[i - len1];
		i++;
	}
	tmp[i] = '\0';
	free(s1);
	return (tmp);
}

char	*ft_strjoin_free_back(char *s1, char *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*tmp;

	i = -1;
	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	tmp = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!tmp)
		return (0);
	while (++i < len1)
		tmp[i] = s1[i];
	while (i - len1 < len2)
	{
		tmp[i] = s2[i - len1];
		i++;
	}
	tmp[i] = '\0';
	free(s2);
	return (tmp);
}
