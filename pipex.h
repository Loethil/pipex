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
	/* data */
}		t_data;

char	**add_slash(char **all_path);
char	**find_path(char **env, char **all_path);
char	*get_access(char *tab, char **all_path, char *argv);

#endif