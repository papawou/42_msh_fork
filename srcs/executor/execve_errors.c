#include "minishell.h"
#include "libft.h"
#include <errno.h>

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define F_NEXISTS 0
#define F_EXISTS 1<<0
#define F_DIRECTORY 1<<1
#define F_EXEC 1<<2
#define F_READ 1<<3

static int code_print_custom_error(char *prefix, char *attribute, char *message, int code)
{
	print_custom_error(prefix, attribute, message);
	return (code);
}

int exit_print_format_(char *path, int ft_errno, int exit_code)
{
	errno = ft_errno;
	perror(path);
	return (exit_code);
}

int	file_status(char *file)
{
	struct stat	f_info;
	int	r;

	r = F_NEXISTS;
	if (stat(file, &f_info) < 0)
		return (r);
	r |= F_EXISTS;
	if (S_ISDIR(f_info.st_mode))
		r |= F_DIRECTORY;
	if (access(file, X_OK) == 0)
		r |= F_EXEC;
	if (access(file, R_OK) == 0)
		r |= F_READ;
	return (r);
}

int execve_process_error(char *command, int execve_errno)
{
	int		exit_code;
	int		f_status;
	
	f_status = file_status(command);
	exit_code = 126;
	if (execve_errno != ENOEXEC)
	{
		if (execve_errno == ENOENT)
			exit_code = 127;
		if (f_status & F_DIRECTORY)
			return (code_print_custom_error(command, NULL, strerror(EISDIR), exit_code));
		else if (!((f_status & F_EXEC) && !(f_status & F_DIRECTORY)))
			return (code_print_custom_error(command, NULL, strerror(execve_errno), exit_code));
		else if (execve_errno == E2BIG || execve_errno == ENOMEM)
			return (code_print_custom_error(command, NULL, strerror(execve_errno), 2));
		else if (execve_errno == ENOENT)
		{
			errno = execve_errno;
			return (code_print_custom_error(command, "cannot execute", "required file not found", exit_code));
		}
	}
	return (code_print_custom_error(command, NULL, strerror(execve_errno), exit_code));
}
