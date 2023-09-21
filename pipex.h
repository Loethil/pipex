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

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft/libft.h"


typedef	struct s_data
{
	char	**all_path;
	char	**argv1;
	char	**argv2;
	char	*true_path;
	pid_t	pid;
	int	fdin;
	int	fdout;
}		t_data;

char	**add_slash(char **all_path);
char	**find_path(t_data *pip, char **env);
char	**ft_split2(char const *s, char c, char *argv);
char	*theword(int *i, const char *s, char c);
int	countword(char const *s, char c);
char	*get_access(t_data *pip, char *argv);

#endif