/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 17:23:50 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/26 20:34:54 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdlib.h>

/**
 *
 * Get list of paths from environ
 *
 * @return {char **} paths
 */
static char	**get_env_paths(t_list_el *env)
{
	char	**paths;
	char	*path_value;

	path_value = get_env_value(env, "PATH");
	paths = ft_split(path_value, ':');
	free(path_value);
	return (paths);
}

/**
 *
 * Find the command full path with the PATH env variable.
 * Return null if doesn't exist
 *
 * @param {t_command *} command
 *
 * @return {char *} path
 */
static char	*get_path_if_exist(t_list_el *env, t_command *command)
{
	int		i;
	char	**paths;
	char	*bin;
	char	*bin_path;

	i = 0;
	paths = get_env_paths(env);
	bin = ft_strjoin("/", command->bin);
	while (paths[i])
	{
		bin_path = ft_strjoin(paths[i], bin);
		free(paths[i]);
		if (access(bin_path, X_OK) == F_OK)
			break ;
		else
		{
			free(bin_path);
			bin_path = NULL;
		}
		i++;
	}
	free(bin);
	free(paths);
	return (bin_path);
}

/**
 *
 * Try path for local directory otherwise try PATH variables
 *
 * @param {t_program *} command
 *
 * @return {char *} Program path
 */
char	*get_program_path(t_list_el *env, t_command *command)
{
	if (command->bin[0] == '/' || command->bin[0] == '.')
	{
		if (access(command->bin, X_OK) == F_OK)
			return (ft_strdup(command->bin));
		else
			return (NULL);
	}
	return (get_path_if_exist(env, command));
}
