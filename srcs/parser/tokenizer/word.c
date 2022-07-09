/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 16:15:21 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/09 17:26:47 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_simple_word(char **str, t_token *token)
{
	int		i;

	i = 0;
	token->type = WORLD_WITH_ENV_EXPANSION;
	while ((*str)[i] && (*str)[i] != ' ')
		i++;
	token->value = ft_strndup(*str, i);
	*str = &((*str)[i]);
}
