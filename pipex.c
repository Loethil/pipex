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
		free (pip->all_path[i++]);
	free (pip->all_path);
	i = 0;
	while (pip->argv1[i])
		free (pip->argv1[i++]);
	free (pip->argv1);
	i = 0;
	while (pip->argv2[i])
		free (pip->argv2[i++]);
	free (pip->argv2);
	free (pip->true_path);
}

void	proc_fils(t_data *pip, char **env, int *pipe_fd)
{
	close (pipe_fd[0]);
	pip->true_path = get_access(pip, pip->argv1[0]);
	if (dup2(pip->fdin, STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup2");
	close(pipe_fd[1]);
	if (execve(pip->true_path, pip->argv1, env) == -1)
	{
		oppenheimer(pip);
		perror("execve");
	}
}

void	proc_pere(t_data *pip, char **env, int *pipe_fd)
{
	close (pipe_fd[1]);
	pip->true_path = get_access(pip, pip->argv2[0]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror("dup2");
	if (dup2(pip->fdout, STDOUT_FILENO) == -1)
		perror("dup2");
	close(pipe_fd[0]);
	if (execve(pip->true_path, pip->argv2, env) == -1)
	{
		oppenheimer(pip);
		perror("execve");
	}
}

void	herewego(t_data *pip, char **env, int *pipe_fd)
{
	pip->true_path = NULL;
	pip->all_path = malloc(100 * sizeof(char *));
	pip->all_path = find_path(pip, env);
	pip->pid = fork();
	if (pip->pid == -1)
	{
		perror("fork");
		oppenheimer(pip);
		return ;
	}
	else if (pip->pid == 0)
		proc_fils(pip, env, pipe_fd);
	else
	{
		wait(NULL);
		proc_pere(pip, env, pipe_fd);
	}
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
	if ((pip.fdin = open(argv[1], O_TRUNC | O_RDONLY)) == -1)
	{
		perror("infile inexistant");
		exit (0);
	}
	pip.argv1 = ft_split(argv[2], ' ');
	pip.argv2 = ft_split(argv[3], ' ');
	if (argc > 4)
	{
		herewego(&pip, env, pipe_fd);
		oppenheimer(&pip);
	}
	else
		printf("Erreur = pas assez d'arguments\n");
	return (0);
}
