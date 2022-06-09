/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:00:06 by kmendes           #+#    #+#             */
/*   Updated: 2022/06/08 00:00:11 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <termios.h>
#include <readline/readline.h>
#include <unistd.h>

/*
 * disable print of control characters
*/
void	configure_termios(void)
{
	static struct termios	term;

	tcgetattr(0, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &term);
}

/*
 * SIGINT parent handler
 * can lead to race conditions, see set_parent_signals
*/
static void	sigint_handler(int status)
{
	(void) status;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
 * SIGQUIT ignored 
 * SIGINT signaction, block all signals for prevent race conditions
 *  see sigint_handler
 * redudant function, SIGINT is the only who need to be restored
 * call it at parent's start and after execute_plan
*/
void	set_parent_signals(void)
{
	static struct sigaction	act_sigint = {.sa_handler = sigint_handler};

	signal(SIGQUIT, SIG_IGN);
	sigfillset(&act_sigint.sa_mask);
	sigaction(SIGINT, &act_sigint, NULL);
}

/*
 * SIGINT ignored, use it before fork
 * This prevent SIGINT being catch by parent during child's execution
 * call it before execute_plan
*/
void	unset_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
}

/*
 * Restore default state SIGQUIT, SIGINT for child's execution
 * call it after fork in child's process
*/
void	set_child_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
