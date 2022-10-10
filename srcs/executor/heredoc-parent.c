/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc-parent.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmendes <kmendes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:17:43 by fvarrin           #+#    #+#             */
/*   Updated: 2022/10/10 18:27:08 by kmendes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "minishell.h"

/**
 *
 * Open the tmp file clear it and set the file descriptor, return false in case
 * of error
 *
 * @param {int}tmp_file_fd
 *
 * @return {_Bool`}
 */
_Bool	open_tmp_file(int *tmp_file_fd)
{
	*tmp_file_fd = open_file(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC);
	if (*tmp_file_fd < 1)
	{
		print_custom_error("open_tmp_file", "open_file", strerror(errno));
		return (false);
	}
	ft_printf_fd(*tmp_file_fd, "");
	return (true);
}

/**
 * @param {pid_t} pid_child
 */
int	heredoc_parent_wait(pid_t pid_child)
{
	int	wait_stat;
	int	exit_code;

	exit_code = 0;
	while (FOREVER)
	{
		if (waitpid(pid_child, &wait_stat, 0) == -1)
		{
			if (errno == ECHILD)
				break ;
			print_custom_error("heredoc_parent_wait",
				"waitpid", strerror(errno));
		}
		else if (WIFSIGNALED(wait_stat))
			exit_code = (128 + WTERMSIG(wait_stat));
		else if (WIFEXITED(wait_stat))
			exit_code = (WEXITSTATUS(wait_stat));
	}
	return (exit_code);
}

int	exec_heredoc_child(t_list_el *env, t_list_el *current_el, int tmp_file_fd)
{
	set_heredoc_signals();
	execute_heredoc(env, current_el->content, tmp_file_fd);
	close(tmp_file_fd);
	exit(0);
}

/**
 *
 * Prompt for each heredocs and write it to a tmp file
 *
 * @param {t_command *} command
 */
int	execute_heredocs(t_list_el *env, t_command *command)
{
	int			tmp_file_fd;
	t_list_el	*current_el;
	pid_t		pid_fork;
	int			exit_code;

	exit_code = 0;
	current_el = command->heredoc;
	while (current_el && exit_code == 0)
	{
		open_tmp_file(&tmp_file_fd);
		pid_fork = fork();
		if (pid_fork == -1)
		{
			close(tmp_file_fd);
			return (1);
		}
		else if (pid_fork == 0)
			exec_heredoc_child(env, current_el, tmp_file_fd);
		else
			exit_code = heredoc_parent_wait(pid_fork);
		current_el = current_el->next;
		close(tmp_file_fd);
	}
	return (exit_code != 0);
}
