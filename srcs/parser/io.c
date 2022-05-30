/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 17:02:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/30 16:06:08 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

char	**get_input_from_begining(char **arguments, t_command *command)
{
	int		i;
	int		args_begin;

	command->in = ft_strdup(arguments[1]);
	i = 2;
	args_begin = i;
	while (--i >= 0)
	{
		free(arguments[i]);
		arguments[i] = NULL;
	}
	return (&arguments[args_begin]);
}

char	**get_input_from_end(char **arguments, t_command *command)
{
	int		i;

	i = 0;
	while (arguments[i] && ft_strcmp(arguments[i], "<") != 0)
		i++;
	if (arguments[i] == NULL)
		return (arguments);
	command->in = ft_strdup(arguments[i + 1]);
	while (arguments[i])
	{
		free(arguments[i]);
		arguments[i] = NULL;
		i++;
	}
	return (arguments);
}

char	**get_io_for_command(char **arguments, t_command *command)
{
	if (ft_strcmp(arguments[0], "<") == 0)
		return (get_input_from_begining(arguments, command));
	return (get_input_from_end(arguments, command));
}
