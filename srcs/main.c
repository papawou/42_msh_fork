/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 12:36:29 by fvarrin           #+#    #+#             */
/*   Updated: 2022/09/24 20:24:06 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>

#include <termios.h>
#include <stdlib.h>

#include "libft.h"
#include "minishell.h"

void	print_usage(void)
{
	printf("%s only work in interactive mode without any arguments\n", BIN_NAME);
}

/**
 *
 * @param {char **} str
 * @param {t_token *} token
 */

void	run_prompt(void)
{
	t_execution_plan	*execution_plan;
	char				*line_read;
	t_list_el			*env;

	line_read = NULL;
	env = parse_environ();
	while (42)
	{
		line_read = prompt(line_read); //<- free line_read
		if (line_read == NULL) //<- real EOF received
			break ;
		line_read = trim_space(line_read);
		if (line_read == NULL || (line_read && line_read[0] == '\0' )) //<- keep running baby
			continue ;
		execution_plan = parse_line(env, line_read); //<- line_read is freed inside it whatever happens
		if (execution_plan == NULL)
		{
			line_read = NULL; //<- prevent double free, flow: parse_line -> prompt
			continue ;
		}
		execution_plan->env = &env;
		unset_parent_signals();
		execute_plan(execution_plan);
		set_parent_signals();
		destroy_execution_plan(execution_plan);
	}
	ft_lstclear(&env, &destroy_environ_el);
}

int	main(int argc, __attribute__((unused)) char **argv)
{
	if (argc != 1)
	{
		print_usage();
		return (-3);
	}
	configure_termios();
	set_parent_signals();
	print_welcome_message();
	run_prompt();
}
