/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:55:18 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/29 17:01:24 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_PROMPT_NAME "minishell> "

typedef enum e_error_codes {
	ERR_ALLOCATING_MEMORY = 1,
	ERR_OPENING_FILE = 2,
	ERR_FORKING_PROCESS = 3,
}	t_error_codes;

typedef struct s_command {
	char	*in;
	char	*out;
	char	*path;
	char	**argv;
	int		return_value;
}	t_command;

typedef struct s_execution_plan {
	t_command	**commands;
	int			number_of_commands;
}	t_execution_plan;

/* Utils */
char					*trim_space(char *source);

/* Parser */
t_execution_plan		*init_execution_plan(int number_of_commands);
t_execution_plan		*destroy_execution_plan(
							t_execution_plan *execution_plan);

t_command				*init_command(void);
t_command				*init_command_argv(
							t_command *command, char **arguments);
t_command				*destroy_command(t_command *command);

t_execution_plan		*parse_line(char *line);

#endif