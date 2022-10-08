/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor-utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 15:56:14 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/08 15:58:24 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int	clear_if_exec_fail(
		t_execution_plan *execution_plan,
		int **pipes,
		char *program_path,
		char **environ_as_arr
)
{
	int		exit_code;

	exit_code = execve_process_error(program_path, errno);
	destroy_pipes(execution_plan->number_of_commands, pipes);
	free(program_path);
	ft_lstclear(execution_plan->env, &destroy_environ_el);
	free_environ_char_2d(environ_as_arr);
	return (exit_code);
}

int	handle_builtins(t_execution_plan *execution_plan, t_command *command)
{
	int	builtin_result;

	builtin_result = execute_builtins(execution_plan->env, command);
	if (execution_plan->need_to_fork)
		exit(builtin_result);
	route_back_command_io(command);
	return (builtin_result);
}

char	*find_program_path(t_execution_plan *execution_plan, t_command *command)
{
	char	*program_path;

	if (!ft_strchr(command->bin, '/'))
	{
		program_path = get_program_path(*execution_plan->env, command);
		if (program_path == NULL)
		{
			print_custom_error(command->bin, NULL,
				"command not found");
			return (NULL);
		}
	}
	else
		program_path = ft_strdup(command->bin);
	return (program_path);
}
