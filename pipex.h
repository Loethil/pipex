/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:12:39 by mbatteux          #+#    #+#             */
/*   Updated: 2023/09/20 18:12:41 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define RDM "/dev/urandom"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"

typedef struct s_data
{
	char	**all_path;
	char	**argv1;
	char	**argv2;
	char	*true_path;
	pid_t	pid;
	pid_t	pid2;
	int		fdin;
	int		fdout;
}		t_data;

void	find_path(t_data *pip, char **env);
void	free_tabs(char **tab);
char	*theword(int *i, const char *s, char c);
char	*get_access(t_data *pip, char *argv);
int		countword(char const *s, char c);
void	oppenheimer(t_data *pip);
void	error(char *err, t_data *pip);
void	herewego(t_data *pip, char **env, char **argv, int *pipe_fd);
void	proc_1(t_data *pip, char **env, char **argv, int *pipe_fd);
void	proc_2(t_data *pip, char **env, char **argv, int *pipe_fd);
void	free_argv(t_data *pip);

#endif
