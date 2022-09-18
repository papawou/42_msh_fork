/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:13:27 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/18 14:40:49 by fvarrin          ###   ########.fr       */
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
	int		i;
	char 	*env_with_eq;
	char	*result;

	i = 0;
	result = NULL;
	env_with_eq = ft_strjoin(env, "=");
	while (result == NULL && environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], env_with_eq, ft_strlen(env_with_eq)) == 0)
			result = ft_strdup(environ[i] + ft_strlen(env_with_eq));
		else
			i++;
	}
	if (result == NULL)
		result = ft_strdup("");
	return (result);
}
