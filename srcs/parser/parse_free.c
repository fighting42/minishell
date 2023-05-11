/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daheepark <daheepark@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:55:56 by daheepark         #+#    #+#             */
/*   Updated: 2023/05/11 12:00:10 by daheepark        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void   free_parse(t_parse *parse)
{
    int i;

    i = -1;
    while (parse->tmp[++i])
        free(parse->tmp[i]);
    free(parse->tmp);
    
}