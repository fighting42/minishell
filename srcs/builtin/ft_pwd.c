/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:12:45 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/10 05:33:48 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(int fd)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	ft_putendl_fd(ret, fd);
	free(ret);
	return (0);
}
