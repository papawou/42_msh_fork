
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "minishell.h"

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

void heredoc_parent_wait(pid_t pid_child)
{
	int	wait_stat;

	while (1)
	{
		if (waitpid(pid_child, &wait_stat, 0) == -1)
		{
			if (errno == ECHILD)
				break;
			print_custom_error("heredoc_parent_wait", "waitpid", strerror(errno));
		}
		else if (WIFSIGNALED(wait_stat))
			env_exit = (128 + WTERMSIG(wait_stat));
		else if (WIFEXITED(wait_stat))
			env_exit = (WEXITSTATUS(wait_stat));
	}
}

/**
 *
 * Prompt for heredoc and write it to a tmp file
 *
 * @param {t_command *} command
 */
void	execute_heredocs(t_command *command)
{
	int			tmp_file_fd;
	t_list_el	*current_el;
	pid_t		pid_fork;
	
	current_el = command->heredoc;
	while (current_el)
	{
		open_tmp_file(&tmp_file_fd);
		pid_fork = fork();
		if (pid_fork == -1)
			print_custom_error("execute_heredocs", "fork", strerror(errno));
		else if (pid_fork == 0)
		{
			set_heredoc_signals();
			execute_heredoc(current_el->content, tmp_file_fd);
			close(tmp_file_fd);
			exit(0);
		}
		else
			heredoc_parent_wait(pid_fork);
		current_el = current_el->next;
		close(tmp_file_fd);
	}
}
