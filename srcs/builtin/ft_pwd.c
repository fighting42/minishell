/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yejinkim <yejinkim@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 16:12:45 by yejinkim          #+#    #+#             */
/*   Updated: 2023/05/03 17:38:58 by yejinkim         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*ret;

	ret = getcwd(NULL, 0);
	printf("%s\n", ret);
	free(ret);
	return (0);
}
