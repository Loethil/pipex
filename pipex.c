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

void	proc_1(t_data *pip, char **env, char **argv, int *pipe_fd)
{
	pip->fdin = open(argv[1], O_RDONLY);
	if (pip->fdin == -1)
		error("Error file\n", pip);
	close(pipe_fd[0]);
	pip->true_path = get_access(pip, pip->argv1[0]);
	if (dup2(pip->fdin, STDIN_FILENO) == -1)
		error("Error dup2\n", pip);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		error("Error dup2\n", pip);
	close(pipe_fd[1]);
	if (execve(pip->true_path, pip->argv1, env) == -1)
		error("Error execve\n", pip);
}

void	proc_2(t_data *pip, char **env, char **argv, int *pipe_fd)
{
	pip->fdout = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (pip->fdout == -1)
		error("Error file\n", pip);
	close(pipe_fd[1]);
	pip->true_path = get_access(pip, pip->argv2[0]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		error("Error dup2\n", pip);
	if (dup2(pip->fdout, STDOUT_FILENO) == -1)
		error("Error dup2\n", pip);
	close(pipe_fd[0]);
	if (execve(pip->true_path, pip->argv2, env) == -1)
		error("Error execve\n", pip);
}

void	herewego(t_data *pip, char **env, char **argv, int *pipe_fd)
{
	int	status;

	pip->true_path = NULL;
	find_path(pip, env);
	pip->pid = fork();
	if (pip->pid == -1)
		error("Error pid\n", pip);
	else if (pip->pid == 0)
		proc_1(pip, env, argv, pipe_fd);
	else
		waitpid(pip->pid, &status, 0);
	pip->pid2 = fork();
	if (pip->pid2 == -1)
		error("Error pid\n", pip);
	else if (pip->pid2 == 0)
		proc_2(pip, env, argv, pipe_fd);
	else
		waitpid(pip->pid, &status, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	pip;
	int		pipe_fd[2];

	if (argc == 5)
	{
		if (pipe(pipe_fd) == -1)
			error("Error pipe\n", &pip);
		if (ft_strncmp(argv[1], RDM, ft_strlen(RDM)) == 0)
			return (0);
		if ((ft_strlen(argv[2]) && ft_strlen(argv[3])) <= 0)
		{
			write(1, "missing arguments\n", 18);
			return (0);
		}
		pip.argv1 = ft_split(argv[2], ' ');
		pip.argv2 = ft_split(argv[3], ' ');
		herewego(&pip, env, argv, pipe_fd);
		error("", &pip);
	}
	else
		write(1, "Error arguments\n", 16);
	return (0);
}
