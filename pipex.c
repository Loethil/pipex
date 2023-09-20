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

int	main(int argc, char **argv, char **env)
{
	// t_data	*pip;
	char	**all_path;
	char	**argv1;
	char	**argv2;
	char	*tab;
	pid_t	pid;
	int	pipe_fd[2];
	int	fd;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return 1;
	}
	argv1 = ft_split(argv[2], ' ');
	argv2 = ft_split(argv[3], ' ');
	fd = open("outfile", O_CREAT | O_TRUNC | O_WRONLY);
	if (argc > 1)
	{
		tab = NULL;
		all_path = malloc(1000 * sizeof(char *) + 1);
		all_path = find_path(env, all_path);
		if ((pid = fork()) == -1)
		{
			perror("fork");
			return 1;
		}
		else if (pid == 0) //proc fils
		{
			close (pipe_fd[0]);
			tab = get_access(tab, all_path,argv1[0]);
			if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				perror("dup2");
			else if (execve(tab, argv1, env) == -1)
				perror("execve");
			close(pipe_fd[1]);
		}
		else
		{
			wait(NULL);
			close (pipe_fd[1]);
			tab = get_access(tab, all_path, argv2[0]);
			if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
				perror("dup2");
			if (dup2(fd, STDOUT_FILENO) == -1)
				perror("dup2");
			else if (execve(tab, argv2, env) == -1)
				perror("execve");
			close(pipe_fd[0]);
		}
	}
	return (0);
}

