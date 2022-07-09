/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:10:49 by fvarrin           #+#    #+#             */
/*   Updated: 2022/07/09 17:23:58 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_space_delimiter(char **str, t_token *token)
{
	token->type = SPACE_DELIMITER;
	*str = &((*str)[1]);
}
