/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:17:19 by mbatteux          #+#    #+#             */
/*   Updated: 2023/09/12 14:17:20 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	oppenheimer(t_data *pip)
{
	int	i;

	i = 0;
	while (pip->all_path[i])
		free(pip->all_path[i++]);
	free(pip->all_path);
	free(pip->true_path);
}

void	proc_1(t_data *pip, char **env, int *pipe_fd)
{
	close(pipe_fd[0]);
	pip->true_path = get_access(pip, pip->argv1[0]);
	if (dup2(pip->fdin, STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup2");
	close(pipe_fd[1]);
	if (execve(pip->true_path, pip->argv1, env) == -1)
		perror("execve");
}

void	proc_2(t_data *pip, char **env, int *pipe_fd)
{
	close(pipe_fd[1]);
	pip->true_path = get_access(pip, pip->argv2[0]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(pip->fdout, STDOUT_FILENO) == -1)
		perror("dup2");
	close(pipe_fd[0]);
	if (execve(pip->true_path, pip->argv2, env) == -1)
		perror("execve");
}

void	herewego(t_data *pip, char **env, int *pipe_fd)
{
	pip->true_path = NULL;
	pip->all_path = find_path(pip, env);
	pip->pid = fork();
	if (pip->pid == -1)
	{
		perror("fork");
		oppenheimer(pip);
		return ;
	}
	else if (pip->pid == 0)
		proc_1(pip, env, pipe_fd);
	pip->payd2 = fork();
	if (pip->pid == -1)
	{
		perror("fork");
		oppenheimer(pip);
		return ;
	}
	else if (pip->payd2 == 0)
		proc_2(pip, env, pipe_fd);
	else
		wait(NULL);
	oppenheimer(pip);
}

int	main(int argc, char **argv, char **env)
{
	t_data	pip;
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	pip.fdout = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	pip.fdin = open(argv[1], O_TRUNC | O_RDONLY);
	if (pip.fdin == -1 || pip.fdout == -1)
		strerror(EBADF);
	pip.argv1 = ft_split(argv[2], ' ');
	pip.argv2 = ft_split(argv[3], ' ');
	if (argc == 5)
		herewego(&pip, env, pipe_fd);
	else
		write(1, "Arguments\n", 10);
	free_argv(&pip);
	return (0);
}
