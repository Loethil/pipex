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

char	**add_slash(char **all_path)
{
	int	i;

	i = 0;
	while (all_path[i])
	{
		all_path[i] = ft_strjoin(all_path[i], "/");
		i++;
	}
	return (all_path);
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
	pip->all_path = add_slash(pip->all_path);
	return (pip->all_path);
}

char	*get_access(t_data *pip, char *argv)
{
	int	i;

	i = 0;
	while (pip->all_path[i])
	{
		pip->true_path = ft_strjoin(pip->all_path[i], argv);
		if (access(pip->true_path, X_OK) == 0)
			break ;
		else if (access(pip->true_path, X_OK) == -1)
			pip->true_path = NULL;
		i++;
	}
	return (pip->true_path);
}
