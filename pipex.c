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

void	proc_1(t_data *pip, char **env, int *pipe_fd)
{
	close(pipe_fd[0]);
	get_access(pip, pip->argv1[0]);
	if (dup2(pip->fdin, STDIN_FILENO) == -1)
		error(1, pip);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error(1, pip);
	close(pipe_fd[1]);
	if (execve(pip->true_path, pip->argv1, env) == -1)
		error(1, pip);
}

void	proc_2(t_data *pip, char **env, int *pipe_fd)
{
	close(pipe_fd[1]);
	get_access(pip, pip->argv2[0]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		error(1, pip);
	if (dup2(pip->fdout, STDOUT_FILENO) == -1)
		error(1, pip);
	close(pipe_fd[0]);
	if (execve(pip->true_path, pip->argv2, env) == -1)
		error(1, pip);
}

void	herewego(t_data *pip, char **env, int *pipe_fd)
{
	pip->true_path = NULL;
	pip->all_path = find_path(pip, env);
	pip->pid = fork();
	if (pip->pid == -1)
		error(1, pip);
	else if (pip->pid == 0)
		proc_1(pip, env, pipe_fd);
	pip->payd2 = fork();
	if (pip->pid == -1)
		error(1, pip);
	else if (pip->payd2 == 0)
		proc_2(pip, env, pipe_fd);
	else
		wait(NULL);
}

int	main(int argc, char **argv, char **env)
{
	t_data	pip;
	int		pipe_fd[2];

	if (argc == 5)
	{
		if (pipe(pipe_fd) == -1)
			error(1, &pip);
		pip.fdout = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		pip.fdin = open(argv[1], O_TRUNC | O_RDONLY);
		if (pip.fdin == -1 || pip.fdout == -1)
		{
			write(1, "Error file\n", 11);
			return (0);
		}
		pip.argv1 = ft_split(argv[2], ' ');
		pip.argv2 = ft_split(argv[3], ' ');
		herewego(&pip, env, pipe_fd);
		error(0, &pip);
	}
	else
		write(1, "Error arguments\n", 16);
	return (0);
}
