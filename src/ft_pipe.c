#include "minishell.h"

static int	run_cmd_pipe(t_list **env, int pipefd[2], int tempfd, t_cmd_lst *cmd, t_cmd_lst *top_cmd)
{
	if (close(pipefd[0]) == -1)
		return (0);
	if (dup2(tempfd, STDIN_FILENO) == -1)
		return (0);
	if (cmd->next && dup2(pipefd[1], STDOUT_FILENO) == -1)
		return (0);
	if (close(pipefd[1]) == -1)
		return (0);
	run_command(env, cmd, top_cmd);
	exit(9);
}

static int	adjust_fd(t_cmd_lst *cmd, int pipefd[2], int *readfd)
{
	if (cmd->input_path)
	{
		if (close(*readfd) == -1)
			return (0);
		*readfd = rd_input(cmd->input_path);
		if (*readfd == -1)
			return (0);
	}
	if (cmd->output_path)
	{
		if (close(pipefd[1]) == -1)
			return (0);
		if (cmd->output_type == 'R') // R FOR REPLACE
			pipefd[1] = rd_output(cmd->output_path);
		else if (cmd->output_type == 'A') // A FOR APPEND
			pipefd[1] = rd_output_append(cmd->output_path);
		if (pipefd[1] == -1)
		{
			close(*readfd); // PROTECT?
			return (0);
		}
	}
	return (9);
}

int	ft_pipe(t_list **env, t_cmd_lst *cmd)
{
	int	pipefd[2];
	int	readfd;
	t_cmd_lst	*top_cmd;

	top_cmd = cmd;
	readfd = dup(STDIN_FILENO);
	while (cmd)
	{
		if (pipe(pipefd) == -1)
			return (0); // ENOUGH?
		if (!adjust_fd(cmd, pipefd, &readfd))
			return (0); // NEED TO CLOSE PIPEFDS BEFORE RETURNING, NOT YET READY
		g_pid = fork();
		if (!g_pid)
			run_cmd_pipe(env, pipefd, readfd, cmd, top_cmd);
		close(readfd);
		readfd = dup(pipefd[0]);
		close(pipefd[0]);
		close(pipefd[1]);
		waitpid(g_pid, NULL, 0);
		cmd = cmd->next;
	}
	close(readfd);
	return (9);
}
