/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:20:15 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/03 19:28:28 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

#include "libft.h"
#include "minishell.h"

/**
 * Allocate memory for a command
 *
 * @return {t_command *} command
 */
t_command	*init_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		exit(ERR_ALLOCATING_MEMORY);
	command->in = NULL;
	command->out = NULL;
	command->argv = NULL;
	command->heredoc = NULL;
	command->bin = NULL;
	command->return_value = 0;
	return (command);
}

/**
 * Free all command memory
 *
 * @param {t_command *} command
 * @return {t_command *}
 */
void	destroy_command(t_command *command)
{
	int		i;

	i = 0;
	if (command == NULL)
		return ;
	while (command->argv && command->argv[i])
		free(command->argv[i++]);
	if (command->tokens)
		ft_lstclear(&(command->tokens), destroy_token);
	free(command->argv);
	free(command->bin);
	if (command->heredoc)
		ft_lstclear(&command->heredoc, free);
	if (command->in)
		ft_lstclear(&command->in, destroy_file_redirect);
	if (command->out)
		ft_lstclear(&command->out, destroy_file_redirect);
	free(command);
}
