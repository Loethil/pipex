/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatteux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:15:37 by mbatteux          #+#    #+#             */
/*   Updated: 2023/09/20 18:15:39 by mbatteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

void	error(int c, t_data *pip)
{
	int	i;

	free_argv(pip);
	if (c == 1)
		write (1, "error\n", 6);
	if (c == 0)
	{
		i = 0;
		while (pip->all_path[i])
			free(pip->all_path[i++]);
	}
	free(pip->all_path);
	exit(0);
}

char	**find_path(t_data *pip, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			break ;
		i++;
	}
	pip->all_path = ft_split(env[i] + 5, ':');
	i = 0;
	while (pip->all_path[i])
	{
		pip->all_path[i] = ft_strjoin(pip->all_path[i], "/");
		i++;
	}
	return (pip->all_path);
}

void	get_access(t_data *pip, char *argv)
{
	int	i;

	i = 0;
	while (pip->all_path[i])
	{
		pip->true_path = ft_strjoin(pip->all_path[i], argv);
		if (access(pip->true_path, X_OK) == 0)
			return ;
		free(pip->true_path);
		i++;
	}
	error(1, pip);
}

void	free_argv(t_data *pip)
{
	int	i;

	i = 0;
	while (pip->argv1[i])
		free(pip->argv1[i++]);
	i = 0;
	free(pip->argv1);
	while (pip->argv2[i])
		free(pip->argv2[i++]);
	free(pip->argv2);
}
