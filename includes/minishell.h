/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:55:18 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/07 14:26:47 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define FILE_PERMISSION_IF_CREATED 0664

extern char	**environ;

typedef enum e_error_codes {
	ERR_ALLOCATING_MEMORY = 1,
	ERR_OPENING_FILE = 2,
	ERR_FORKING_PROCESS = 3,
}	t_error_codes;

typedef struct s_command {
	char	*in;
	char	*out;
	char	*bin;
	char	**argv;
	int		return_value;
	_Bool	out_in_append_mode;
}	t_command;

typedef struct s_execution_plan {
	t_command	**commands;
	int			number_of_commands;
}	t_execution_plan;

/* Utils */
char				*trim_space(char *source);
int					open_file(char *path, int flags);

/* Prompter */
void				print_welcome_message(void);
char				*prompt(char *line_read);

/* Parser */
t_execution_plan	*init_execution_plan(int number_of_commands);
void				destroy_execution_plan(t_execution_plan *execution_plan);

t_command			*init_command(void);
t_command			*init_command_argv(t_command *command, char **arguments);
void				destroy_command(t_command *command);

char				**get_io_from_beginning(char **arguments,
						t_command *command);
char				**get_io_from_end(char **arguments, t_command *command);

t_execution_plan	*parse_line(char *line);

/* Executor */
int					execute_plan(t_execution_plan *execution_plan);
void				execute_command(t_execution_plan *execution_plan,
						int **pipes, int index);

int					**create_pipes(int number_of_child_processes, int **pipes);
void				close_pipes_in_child_process(int **pipes,
						int number_of_child_processes, int index);
void				close_pipes_in_main_process(
						int **pipes, int number_of_child_processes);
void				destroy_pipes(int number_of_child_processes, int **pipes);

int					*create_processes(t_execution_plan *execution_plan,
						int *pids, int **pipes);
int					count_total_process(int number_of_child_processes);

/* Signals */
void				configure_termios(void);
void				set_parent_signals(void);
void				set_child_signals(void);
void				unset_parent_signals(void);

#endif