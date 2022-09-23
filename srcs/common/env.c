/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:13:27 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/23 14:25:26 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 *
 * Get env variable value
 *
 * @return {char **} paths
 */
char	*get_env_value(char *env)
{
	char	*result;

	result = getdup_environ_el_value(g_environ, env);
	if (result == NULL)
		result = ft_strdup("");
	return (result);
}
