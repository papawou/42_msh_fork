/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 06:09:03 by kmendes           #+#    #+#             */
/*   Updated: 2022/06/07 06:15:51 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

/*
	signal are sent to process groups
	
	signals set to SIG_IGN (ignored) in parent process stay ignored in childs
	signals not SIG_IGN are set to SIG_DFL (default) in childs
*/

void	set_parent_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
}

void	set_child_signals(void)
{
	signal(SIGQUIT, SIG_DFL);
}
