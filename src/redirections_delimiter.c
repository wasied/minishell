#include "minishell.h"

static void	eof_not_delim(char *delimiter, int i)
{
	char	*nbr_str;

	ft_putstr_fd(STDERR_FILENO, \
		"Supershell: warning: here-document ");
	nbr_str = ft_itoa(i);
	if (nbr_str)
	{
		ft_putstr_fd(STDERR_FILENO, "at line ");
		ft_putstr_fd(STDERR_FILENO, nbr_str);
		ft_putstr_fd(STDERR_FILENO, " ");
		free(nbr_str);
	}
	ft_putstr_fd(STDERR_FILENO, "delimited by end-of-file (wanted `");
	ft_putstr_fd(STDERR_FILENO, delimiter);
	ft_putstr_fd(STDERR_FILENO, "')\n");
}

static void	rd_delimiter_child(int fd, char *delimiter)
{
	char	*line;
	int	i;

	i = 0;
	line = readline("> ");
	if (!line)
		eof_not_delim(delimiter, i);
	while (ft_strncmp(delimiter, line, -1))
	{
		ft_putstr_fd(fd, line);
		write(fd, "\n", 1);
		i++;
		if (line)
			free(line);
		line = readline("> ");
		if (!line)
			eof_not_delim(delimiter, i);
	}
	if (line)
		free(line);
	exit(0);
}

int	rd_delimiter(char *delimiter)
{
	int	fd[2];

	if (pipe(fd) == -1)
		return (-1);
	g_pid = fork();
	if (g_pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (!g_pid)
		rd_delimiter_child(fd[1], delimiter);
	if (waitpid(g_pid, NULL, 0) == -1)
		return (-1); // PROTECT + SHOULD GET THE VALUE FOR ERRNO?
	close(fd[1]);
	return (fd[0]);
}
