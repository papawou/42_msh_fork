/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:14:09 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/29 17:01:05 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include "libft.h"
#include "minishell.h"

/**
 * Return a new string trimmed of spaces.
 * It free source and allocate memory for the new string
 *
 * @param {char *} source
 * @return {char *} dst
 */
char	*trim_space(char *source)
{
	char	*dst;

	dst = ft_strtrim(source, "\t\n\v\f\r ");
	free(source);
	return (dst);
}
