/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 21:24:32 by yejinkim          #+#    #+#             */
/*   Updated: 2022/07/16 18:40:56 by yejinkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(long n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*tmp;

	nb = n;
	len = intlen(nb);
	tmp = (char *)malloc(sizeof(char) * (len + 1));
	if (!tmp)
		return (0);
	if (nb < 0)
	{
		tmp[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		tmp[0] = '0';
	tmp[len--] = '\0';
	while (nb > 0)
	{
		tmp[len] = nb % 10 + '0';
		len--;
		nb /= 10;
	}
	return (tmp);
}
