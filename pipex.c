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

void	proc_fils(t_data *pip, char **env, int *pipe_fd)
{
	close (pipe_fd[0]);
	pip->true_path = get_access(pip, pip->argv1[0]);
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		perror("dup219");
	if (execve(pip->true_path, pip->argv1, env) == -1)
		perror("execve");
	close(pipe_fd[1]);
}

void	proc_pere(t_data *pip, char **env, int *pipe_fd)
{
	close (pipe_fd[1]);
	pip->true_path = get_access(pip, pip->argv2[0]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror("dup230");
	if (dup2(pip->fdout, STDOUT_FILENO) == -1)
		perror("dup232");
	else if (execve(pip->true_path, pip->argv2, env) == -1)
		perror("execve");
	close(pipe_fd[0]);
}

void	herewego(t_data *pip, char **env, int *pipe_fd)
{
	pip->true_path = NULL;
	pip->all_path = malloc(1000 * sizeof(char *) + 1);
	pip->all_path = find_path(pip, env);
	pip->pid = fork();
	if (pip->pid == -1)
	{
		perror("fork");
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
	pip.fdout = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0777);
	if ((pip.fdin = open(argv[1], O_TRUNC | O_WRONLY, 0777)) == -1)
	{
		perror("infile inexistant");
		exit (0);
	}
	pip.argv1 = ft_split2(argv[2], ' ', argv[1]);
	pip.argv2 = ft_split(argv[3], ' ');
	if (argc > 4)
		herewego(&pip, env, pipe_fd);
	else
		printf("Erreur = pas assez d'arguments\n");
	return (0);
}
